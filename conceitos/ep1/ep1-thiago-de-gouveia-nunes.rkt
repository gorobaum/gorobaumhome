#lang plai

(require racket/trace)

(define-type Binding
  [binding (name symbol?) (named-expr WAE?)])

(define-type WAE
  [num (n number?)]
  [binop (op procedure?) (lhs WAE?) (rhs WAE?)]
  [with (lob (listof Binding?)) (body WAE?)]
  [id (name symbol?)])

(define (lobmanager in out)
        (if (= (length in) 0 ) out
            (if (= (length (first in) ) 2 ) 
                (if (symbol? (first (first in) ) )
                    (lobmanager (cdr in) (cons (binding (cons (first (first in)) (parse (second (first in)))))))
                    (error 'lobmanager "O with precisa de um simbolo no primeiro elemeneto de cada par.") )
                (error 'lobmanager "Cada substituicao do with tem que ter duas partes, o simbolo e sua definicao."))))  

;; parse : s-exp -> WAE
;; Consumes an s-expression and generates the corresponding WAE
(define (parse sexp)
    (cond
        [(number? sexp) (num sexp)]
        [(symbol? sexp) (id sexp)]
        [(list? sexp)
            (case (first sexp)
                [(+) ( binop +  ( parse (second sexp) ) 
                                ( parse (third sexp) ) ) ]
                [(-) ( binop -  ( parse (second sexp) ) 
                                ( parse (third sexp) ) ) ]
                [(with) ( with  ( parse (second sexp) )
                                ( parse (third sexp) ) ) ]
                [(id) ( lobmanager( parse (second sexp) '())
                                ( parse (third sexp) ) ) ] 
                [else ( error 'parse "Esperado '+ '- ou with." ) ] ) ]
        [else ( error 'parse "Entrada invalida para o parser." ) ] ) )

(trace parse)

(parse(read))
