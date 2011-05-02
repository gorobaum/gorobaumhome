#lang plai
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  Nome : Thiago de Gouveia Nunes                      ;;
;;  NUSP : 6797289                                      ;;
;;  Data : 08/04/2011                                   ;;
;;  MAC0316 - Conceitos de Linguagens de Programacao    ;;
;;  Prof : Francisco Reverbel                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(require racket/trace)

;;;;;;;;;;;;;;;;;;
;;  Definicoes  ;;
;;;;;;;;;;;;;;;;;;

(define-type CFAE
  [num (n number?)]
  [binop (op procedure?) (lhs CFAE?) (rhs CFAE?)]
  [id (name symbol?)]
  [if0 (c CFAE?) (t CFAE?) (e CFAE?)]
  [fun (args (listof symbol?)) (body CFAE?)]
  [app (f CFAE?) (args (listof CFAE?))])

(define-type Env
  [mtEnv]
  [anEnv (name symbol?) (value CFAE-Value?) (env Env?)])

(define-type CFAE-Value
  [numV (n number?)]
  [closureV (params (listof symbol?))
            (body CFAE?)
            (env Env?)])

;;  Definicoes das binops usadas pelo programa.
(define table (list (list '+ + ) (list '- -) (list '* *) (list '/ /)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Funcoes Auxiliares do parse ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;  listsymanager : symbol list -> symbol
;;  Recebe uma lista de simbolos e verifica se ela é correta.
( define (listsymanager in out)
        (if (= (length in) 0) 
            (reverse out)
            (if (isthere (first in) out)
                (error 'listsymanager "Simbolo ja em uso.")
                (listsymanager (cdr in) (cons (first in) out)))))

;;  searchbinop: symbol table -> binop
;;  Consume um symbol e uma lista e devolve um binop.
(define (searchbinop op table)
    (if (= (length table) 0 )
        op
        (if (equal? (first (first table)) op)
            (second (first table))
            (searchbinop op (rest table)))))

;;  isthere : symbol lob -> boolean
;;  Verifica se ja existe um item dentro de uma lista.
(define (isthere item listin)
        (if (empty? listin ) #f
            (if (equal? (first listin) item ) #t
                (isthere item (rest listin) ))))

;;  listf: list -> list
;;  Recebe uma lista de pares e devolve uma lista com somente os primeiros items
;;  de cada par.
(define (listf in out)
    (if (= (length in) 0) 
        out
        (if (list? (first in))
            (if (= (length (first in) ) 2 )
                (if (symbol? (first (first in)))
                    (if (isthere (first (first in)) out)
                        (error 'listf "Identificador repitido dentro de with.")
                        (listf (cdr in) (cons (first (first in)) out)))
                    (error 'listf "O with precisa de um simbolo no primeiro elemeneto de cada par."))
                (error 'listf "Cada substituicao do with tem que ter duas partes, o simbolo e sua definicao."))
            (if (= (length in) 2)                
                (if (symbol? (first in))
                    (listf '() (cons (first in) out))
                    (error 'listf "O with precisa de um simbolo para ser definido."))
                (error 'listf "Definicao do simbolo do With errada.")))))

;;  lists: list -> list
;;  Recebe uma lista de pares e devolve uma lista com somente os segundos items
;;  de cada par.
(define (lists in out)
    (if (= (length in) 0) 
        out
        (if (list? (first in))
            (if (= (length (first in) ) 2 )
                (if (isthere (first (first in)) out)
                    (error 'lists "Identificador repitido dentro de with.")
                    (lists (cdr in) (cons (parse (second (first in))) out)))
                (error 'lists "Cada substituicao do with tem que ter duas partes, o simbolo e sua definicao."))
            (if (= (length in) 2)                
                (lists '() (cons (parse (second in)) out))
                (error 'lists "Definicao do simbolo do With errada.")))))

;;  applist
;;
(define (applist in out)
    (if (= (length in) 0)
        out
        (applist (cdr in) (cons (parse (first in)) out))))

;;;;;;;;;;;;
;; Parser ;;
;;;;;;;;;;;;

;; parse : expression -> CFAE
;; This procedure parses an expression into a CFAE
(define (parse sexp)
    (cond
        [(number? sexp) (num sexp)]
        [(symbol? sexp) (id sexp)]
        [(list? sexp)
            (case (first sexp)
                [(if0)  (if (= (length sexp) 4)
                            (if0 (parse (second sexp))
						        (parse (third sexp))
						        (parse (last sexp)))
                            (error 'parse "if0 faltando coisa."))]
                [(fun)  (if (= (length sexp) 3) 
                            (fun (listsymanager (second sexp) '())
                                 (parse (last sexp)))
                            (error 'parse "fun faltando coisa."))]     
                [(with) (if (= (length sexp) 3)
                                (app (fun (listf (second sexp) '()) 
                                          (parse (third sexp)))   
                                     (lists (second sexp) '()))
                                (error 'parse "with faltando coisa."))]
                [(isthere((first sexp) table)) 
                    (if (= (length sexp) 3)
                            (error 'parse "binop faltando coisa.")
                            (binop (searchbinop (first sexp) table)
                                   (parse (second sexp))
                                   (parse (third sexp))))]
                [else (app (parse (first sexp)) (applist (rest sexp) '()))])]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Funcoes Auxiliares do Interp ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;  binoperation : binop number number -> number
;;  Consome uma operacao binaria e dois numeros e devolve o resultado da operacao
;;  aplicada aos dois numeros.
(define (binoperation op l r )
    (if (equal? op /)
        (if (= r 0)
            (error 'binoperation "Tentativa de Divisao por zero!.")
            ( op l r ))
        ( op l r )))

;;  lookup : symbol env -> CFAE-value
;;  Consome um symbol e um env e devolve um CFAE-value
(define (lookup id envir)
    (if (equal? (anEnv-env envir) mtEnv)
        (error 'lookup "Nao definido")
        (if (equal? id (anEnv-name envir))
            (anEnv-value envir)
            (lookup id (anEnv-env envir)))))

;;  rinterp : WAE DefrdSub -> number
;;  Consome uma WAE e um DerfdSub e devolve seu valor numerico.
(define (rinterp expr env)
    (type-case CFAE expr
        [num (n) n]
        [binop (op l r) (binoperation op (rinterp l env) (rinterp r env))]
        [id (v) (lookup v env)]
        [if0 (c t e) (if (= c 0) t e)]
        [fun (fun-arg fun-body) (closureV fun-arg fun-body env)]
        [app (app-f app-args)
            (local ([define fun-val (rinterp app-f env)])
                (interp (closureV-body fun-val)
                    (anEnv (closureV-params fun-val)
                    (interp app-args env)
                    (closureV-env fun-val) )))]))


;;;;;;;;;;;;;
;; Interp  ;;
;;;;;;;;;;;;;

;;  interp : WAE -> number
;;  Consome uma WAE e devolve seu valor numerico.
(define (interp expr ) (rinterp expr (mtEnv)))

;;;;;;;;;;;;
;; Testes ;;
;;;;;;;;;;;;

(trace parse)
(trace listf)
(trace isthere)
(trace interp)
(trace rinterp)
(trace isthere)

(interp (parse(read)))
