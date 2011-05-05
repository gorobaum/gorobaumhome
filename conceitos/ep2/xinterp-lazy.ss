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
            (env Env?)]
  [exprV (expr CFAE?) (env Env?)]))

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
        (if (equal? (first (first table)) op)
            (second (first table))
            (searchbinop op (rest table))))

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
            (lists (cdr in) (cons (parse (second (first in))) out))
            (lists '() (cons (parse (second in)) out)))))

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
                            (error 'parse "Entrada invalida para o parser no if0."))]
                [(fun)  (if (= (length sexp) 3) 
                            (fun (listsymanager (second sexp) '())
                                 (parse (last sexp)))
                            (error 'parse "Entrada invalida para o parser no fun."))]     
                [(with) (if (= (length sexp) 3)
                                (app (fun (listf (second sexp) '()) 
                                          (parse (third sexp)))   
                                     (lists (second sexp) '()))
                                (error 'parse "Entrada invalida para o parser no with."))]
                [(+ - * /)
                    (if (= (length sexp) 3)
                            (binop (searchbinop (first sexp) table)
                                   (parse (second sexp))
                                   (parse (third sexp)))
                            (error 'parse "Entrada invalida para o parser no binop."))]
                [else (app (parse (first sexp)) (applist (rest sexp) '()))])]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Funcoes Auxiliares do Interp ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; strict : CFAE/L-Value → CFAE/L-Value [excluding exprV]
(define (strict e)
    (type-case CFAE/L-Value e
        [exprV (expr env)
            (strict (interp expr env))]
        [else e]))


;;  binoperation : binop number number -> number
;;  Consome uma operacao binaria e dois numeros e devolve o resultado da operacao
;;  aplicada aos dois numeros.
(define (binoperation op l r )
    (if (equal? op /)
        (if (= (numV-n r) 0)
            (error 'binoperation "Tentativa de Divisao por zero!.")
            (numV (op (numV-n l) (numV-n r) )))
        (numV (op (numV-n l) (numV-n r) ))))

;;  lookup : symbol env -> CFAE-value
;;  Consome um symbol e um env e devolve um CFAE-value
(define (lookup id envir)
    (type-case Env envir
        [mtEnv () (error 'lookup "Id nao definido")]
        [anEnv (name value env) (if (equal? id name)
                        (anEnv-value envir)
                        (lookup id (anEnv-env envir)))]))

;;  envmanager  :   symbol CFAE envin envout-> Env
;;  Recebe uma lista de symbols e CFAE e devolve o Env deles.
(define (envmanager symbols CFAEs envin)
    (if (empty? symbols)
        (if (empty? CFAEs)
            envin
            (error 'envmanager "Entrada errada de funcao."))
        (if (empty? CFAEs)
            (error 'envmanager "Entrada errada de funcao.")
            (anEnv  (car symbols)
                    (rinterp (car CFAEs) envin)
                    (envmanager (cdr symbols) 
                                (cdr CFAEs) 
                                 envin))))) 

;;  argmanager
;;
(define (argmanager args out)
    

;;  if0manager : c t e env -> CFAE
;;  Recebe uma condicao a ser comparada com zero e dois valores, que serao devol
;;  vidos dependendo do resultado da comparacao,
(define (if0manager c t e env)
    (if (equal? (numV-n (rinterp c env)) 0)
        (rinterp t env)
        (rinterp e env)))
        
        
;;  rinterp : WAE DefrdSub -> number
;;  Consome uma WAE e um DerfdSub e devolve seu valor numerico.
(define (rinterp expr env)
    (type-case CFAE expr
        [num (n) (numV n)]
        [binop (op l r) (binoperation op (rinterp l env) (rinterp r env))]
        [id (v) (lookup v env)]
        [if0 (c t e) (if0manager c t e env)]
        [fun (fun-arg fun-body) (closureV fun-arg fun-body env)]
        [app (app-f app-args)
            (local ([define fun-val (strict (rinterp app-f env))])
                (rinterp    (closureV-body fun-val)
                            (envmanager (closureV-params fun-val)
                                        (argmanager app-args '()) 
                                        (closureV-env fun-val))))]))


;;;;;;;;;;;;;
;; Interp  ;;
;;;;;;;;;;;;;

;;  interp : WAE -> number
;;  Consome uma WAE e devolve seu valor numerico.
(define (interp expr ) (rinterp expr (mtEnv)))

;;;;;;;;;;;;;
;; Testes  ;;
;;;;;;;;;;;;;

( test (interp (parse '{ with {{x 5}{y 10}} {with { z { + y 42 } } { - { + { * x y } {/ 20 10 } } z } } })) (numV 0))
( test (interp (parse '{if0 0 10 20})) (numV 10))
( test (interp (parse '{{fun {x y} {* x y}} 2 3})) (numV 6))
( test (interp (parse '{if0 {{fun {x y} {* x y}} 2 3} 10 20})) (numV 20))

(test/exn (interp(parse '{/ 3 0})) "Tentativa de Divisao por zero!.")
(test/exn (interp(parse '{+ { with {x 5} {with {y 6} { + x y } } } x } )) "Id nao definido")
(test/exn (interp(parse '{{fun {x x} {* x x}} 2 3})) "Simbolo ja em uso")
(test/exn (interp(parse '{{fun {x y} {* x y}} 2})) "Entrada errada de funcao")
(test/exn (interp(parse '{{fun {x} {* x x}} 2 3})) "Entrada errada de funcao")
(test/exn (interp (parse '{= 3 4})) "Id nao definido")
(test/exn (parse '{fun{x}}) "Entrada invalida para o parser")
(test/exn (parse '{+ 5}) "Entrada invalida para o parser")
(test/exn (parse '{if0 3}) "Entrada invalida para o parser")
(test/exn (parse '{with {x 3}}) "Entrada invalida para o parser")
(test/exn (parse '{with {3} 3}) "Definicao do simbolo do With errada")
(test/exn (parse '{with {3 3} 3}) "O with precisa de um simbolo para ser definido")
(test/exn (parse '{with {{3 3}} 3}) "O with precisa de um simbolo no primeiro elemeneto de cada par")
(test/exn (parse '{with {{0}{y 3}} 3}) "Cada substituicao do with tem que ter duas partes, o simbolo e sua definicao")
(test/exn (parse '{with {{0}{y 3 4}} 3}) "Cada substituicao do with tem que ter duas partes, o simbolo e sua definicao")
(test/exn (parse '{with {{x 3}{x 5}} {+ x x}}) "Identificador repitido dentro de with")

(interp (parse(read)))
