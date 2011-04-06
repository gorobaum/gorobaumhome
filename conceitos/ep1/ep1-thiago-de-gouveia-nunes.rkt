#lang plai
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  Nome : Thiago de Gouveia Nunes                      ;;
;;  NUSP : 6797289                                      ;;
;;  Data : 08/04/2011                                   ;;
;;  MAC0316 - Conceitos de Linguagens de Programacao    ;;
;;  Prof : Francisco Reverbel                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(require racket/trace)

;;  Definicoes  ;;

(define-type Binding
  [binding (name symbol?) (named-expr WAE?)])

(define-type WAE
  [num (n number?)]
  [binop (op procedure?) (lhs WAE?) (rhs WAE?)]
  [with (lob (listof Binding?)) (body WAE?)]
  [id (name symbol?)])

(define-type DefrdSub
    [mtSub]
    [aSub (name symbol?)(value number?)(ds DefrdSub?)])

;;  lobmanager : WAE list -> binding
;;  Consumes a list of WAE and a empty list (out) and generates a list of binding.
(define (lobmanager in out)
        (if (= (length in) 0 ) out
            (if (symbol? (first in))
                (lobmanager '() (cons (binding (first in) (parse (second in))) out))
                (if (= (length (first in) ) 2 )
                    (if (symbol? (first (first in) ) )
                        (lobmanager (cdr in) (cons (binding (first (first in)) (parse (second (first in)))) out))
                        (error 'lobmanager "O with precisa de um simbolo no primeiro elemeneto de cada par.") )
                    (error 'lobmanager "Cada substituicao do with tem que ter duas partes, o simbolo e sua definicao.")))))

;; Definitions of the binop's used in the language.
(define table (list (list '+ + ) (list '- -) (list '* *) (list '/ /)))

;; Funcoes Auxiliares

;;  searchbinop: symbol table -> binop
;;  Consumes a symbol and a table and generates the binop which refers to the symbol.
(define (searchbinop op table)
    (if (= (length table) 0 )
        (error 'searchbinop "Operacao binaria nao definida." )
        (if (equal? (first (first table)) op)
            (second (first table))
            (searchbinop op (rest table)))))


;;  lookup : symbol DefrSub -> WAE
;;  Consome um symbol e um DefrSub e devolve uma WAE
(define (lookup name ds)
    (type-case DefrdSub ds
        [mtSub () (error 'lookup "no binding for identifier")]
        [aSub (bound-name bound-value rest-ds)
            (if (symbol=? bound-name name)
                bound-value
                (lookup name rest-ds))]))

(define (binoperation op l r )
    (if (equal? op /)
        (if (= r 0)
            (error 'binoperation "Tentativa de Divisao por zero!.")
            ( op l r ))
        ( op l r )))

(define (mount-aSub lob ds)
            (cond
                [(empty? lob) ds]
                [else (mount-aSub 
                            (rest lob)
                            (aSub (binding-name (first lob))
                                (rinterp (binding-named-expr (first lob))
                                ds)
                            ds))]))

(define (rinterp expr ds)
    (type-case WAE expr
        [num (n) n]
        [binop (op l r) (binoperation op (rinterp l ds) (rinterp r ds ))]
        [with (lob body) (rinterp body (mount-aSub lob ds))]
        [id (v) (lookup v ds)]))

;; Parse e Interp

;;  parse : s-exp -> WAE
;;  Consumes an s-expression and generates the corresponding WAE
(define (parse sexp)
    (cond
        [(number? sexp) (num sexp)]
        [(symbol? sexp) (id sexp)]
        [(list? sexp)
            (if (= (length sexp) 3)
                (case (first sexp)
                    [(with) ( with  ( lobmanager (second sexp) '() )
                                    ( parse (third sexp) ) ) ]
                    [else ( binop   (searchbinop (first sexp) table)
                                    (parse (second sexp))
                                    (parse (third sexp)))])
            (error 'parse "Numero dos parametros para '+ '- ou with errado.") ) ]
        [else ( error 'parse "Entrada invalida para o parser." ) ] ) )

;;

(define (interp expr ) (rinterp expr (mtSub)))

(trace mount-aSub)
(trace rinterp)
(trace searchbinop)
(trace parse)
(trace lobmanager)

(interp(parse(read)))
