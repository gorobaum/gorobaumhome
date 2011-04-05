#lang plai
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  Nome : Thiago de Gouveia Nunes                      ;;
;;  NUSP : 6797289                                      ;;
;;  Data : 08/04/2011                                   ;;
;;  MAC0316 - Conceitos de Linguagens de Programacao    ;;
;;  Prof : Francisco Reverbel                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(require racket/trace)

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


;;  searchbinop: symbol table -> binop
;;  Consumes a symbol and a table and generates the binop which refers to the symbol.
(define (searchbinop op table)
    (if (= (length table) 0 )
        (error 'searchbinop "Operacao binaria nao definida." )
        (if (equal? (first (first table)))
            (second (first table))
            (searchbinop op (rest table)))))
    

;;  parse : s-exp -> WAE
;;  Consumes an s-expression and generates the corresponding WAE
(define (parse sexp)
    (cond
        [(number? sexp) (num sexp)]
        [(symbol? sexp) (id sexp)]
        [(list? sexp)
            (if (= (length sexp) 3)
                (case (first sexp)
                    [(+) ( binop +  ( parse (second sexp) ) 
                                    ( parse (third sexp) ) ) ]
                    [(-) ( binop -  ( parse (second sexp) ) 
                                    ( parse (third sexp) ) ) ]
                    [(*) ( binop *  ( parse (second sexp) ) 
                                    ( parse (third sexp) ) ) ]
                    [(/) ( binop /  ( parse (second sexp) ) 
                                    ( parse (third sexp) ) ) ]
                    [(with) ( with  ( lobmanager (second sexp) '() )
                                    ( parse (third sexp) ) ) ]
                    [else ( error 'parse "Esperado um operador binario ou with." ) ] )
            (error 'parse "Numero dos parametros para '+ '- ou with errado.") ) ]
        [else ( error 'parse "Entrada invalida para o parser." ) ] ) )


(define (interp expr ) (rinterp expr (mtSub)))

(trace rinterp)
(trace searchbinop)
(trace parse)
(trace lobmanager)

(parse(read))
