#lang plai

(define-type Binding
  [binding (name symbol?) (named-expr WAE?)])

(define-type WAE
  [num (n number?)]
  [binop (op procedure?) (lhs WAE?) (rhs WAE?)]
  [with (lob (listof Binding?)) (body WAE?)]
  [id (name symbol?)])

;; parse : s-exp -> WAE
;; Consumes an s-expression and generates the corresponding WAE
(define (parse sexp)
    (cond
        [(number? sexp) (num sexp)]
        [(symbol? sexp) (id sexp)]
        [(list? sexp)
            ( case (first sexp)
                [(+) ( binop + ( parse (second sexp) ) ( parse (third sexp) ) ) ]
                [(-) ( binop - ( parse (second sexp) ) ( parse (third sexp) ) ) ]
                [(with) ( with ( parse (second sexp) ) ( parse (third sexp) ) ) ]
            )
        ]
    )
)

(parse(read))
