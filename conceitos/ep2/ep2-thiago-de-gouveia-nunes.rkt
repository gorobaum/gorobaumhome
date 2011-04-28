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

;;  listsyisthere : symbol list -> boolean
;;  Verifica se um simbolo ja foi definido.
(define (listsyisthere id listsy)
        (if (empty? listsy ) 
            #f
            (if (equal? (first listsy) id ) 
                #t
                (listsyisthere id (rest listsy)))))

;;  listsymanager : symbol list -> symbol
;;  Recebe uma lista de simbolos e verifica se ela é correta.
( define (listsymanager in out)
        (if (= (length in) 0) 
            (reverse out)
            (if (listsyisthere (first in) out)
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
            (if (= (length sexp) 4)
                (case (first sexp)
                    [(if0) (if0 (parse (second sexp))
								(parse (third sexp))
								(parse (last sexp)))]
					[else (error 'parse "Estrutura do if0 errada.")])
				(if (= (length sexp) 3)
                    (case (first sexp)
                        [(fun)(fun  (listsymanager (second sexp) '())
                                    (parse (last sexp)))]
                        [(with) (app (fun (listf (second sexp) '()) 
                                          (parse (third sexp)))   
                                     (lists (second sexp) '()))]
                        [else   (binop  (searchbinop (first sexp) table)
                                        (parse (second sexp))
                                        (parse (third sexp)))])
                    (error 'parse "Entrada invalida para o parser.")))]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Funcoes Auxiliares do rinterp ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;  binoperation : binop number number -> number
;;  Consome uma operacao binaria e dois numeros e devolve o resultado da operacao
;;  aplicada aos dois numeros.
(define (binoperation op l r )
    (if (equal? op /)
        (if (= r 0)
            (error 'binoperation "Tentativa de Divisao por zero!.")
            ( op l r ))
        ( op l r )))

;;;;;;;;;;;;;;;;;;;;;
;; Parse e Interp  ;;
;;;;;;;;;;;;;;;;;;;;;

;;  interp : WAE -> number
;;  Consome uma WAE e devolve seu valor numerico.

;;;;;;;;;;;;
;; Testes ;;
;;;;;;;;;;;;

(trace parse)
(trace listf)
(trace isthere)

(parse(read))
