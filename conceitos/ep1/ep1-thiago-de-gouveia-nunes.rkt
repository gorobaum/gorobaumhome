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

;;  Definicoes das binops usadas pelo programa.
(define table (list (list '+ + ) (list '- -) (list '* *) (list '/ /)))

;;;;;;;;;;;;;;;;;;;;;;;
;;  Lista de Testes  ;;
;;;;;;;;;;;;;;;;;;;;;;;

;; Testes para o parser.
(define testes ( list   (list '{ + 5 5 } 10 )
                        (list '{ - 5 5 } 0  )
                        (list '{ * 5 5 } 25 )
                        (list '{ / 5 5 } 1  )
                        (list '{ with {x 5} { + x x }} 10 )))

;;;;;;;;;;;;;;;;;;;;;;;;;
;; Funcoes Auxiliares  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;

;;  lobisthere : symbol lob -> boolean
;;  Verifica se um simbolo ja foi definido dentro de um with.
(define (lobisthere id lob)
        (if (empty? lob ) #f
            (if (equal? (binding-name (first lob)) id ) #t
                (lobisthere id (rest lob) ))))

;;  lobmanager : WAE list -> binding
;;  Consome uma lista de WAE e uma lista vazia e gera uma lista de binding.
(define (lobmanager in out)
        (if (= (length in) 0 ) (reverse out)
            (if (list? (first in))
                (if (= (length (first in) ) 2 )
                    (if (symbol? (first (first in)))
                        (if (lobisthere (first (first in)) out)
                            (error 'lobmanager "Identificador repitido dentro de with.")
                            (lobmanager (cdr in) (cons (binding (first (first in)) (parse (second (first in)))) out)))
                        (error 'lobmanager "O with precisa de um simbolo no primeiro elemeneto de cada par.") )
                    (error 'lobmanager "Cada substituicao do with tem que ter duas partes, o simbolo e sua definicao."))
                (if (= (length in) 2)                
                    (if (symbol? (first in))
                        (lobmanager '() (cons (binding (first in) (parse (second in))) out))
                        (error 'lobmanager "O with precisa de um simbolo para ser definido."))
                    (error 'lobmanager "Definicao do simbolo do With errda.")))))

;;  searchbinop: symbol table -> binop
;;  Consume um symbol e uma lista e devolve um binop.
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

;;  binoperation : binop number number -> number
;;  Consome uma operacao binaria e dois numeros e devolve o resultado da operacao
;;  aplicada aos dois numeros.
(define (binoperation op l r )
    (if (equal? op /)
        (if (= r 0)
            (error 'binoperation "Tentativa de Divisao por zero!.")
            ( op l r ))
        ( op l r )))

;;  mount-aSub : lob DefrdSub -> DefrdSub
;;  Consome um lob e um DefrdSub e devolve um DefrdSub com as informacoes do lob.
(define (mount-aSub lob ds)
            (cond
                [(empty? lob) ds]
                [else (mount-aSub 
                            (rest lob)
                            (aSub (binding-name (first lob))
                                (rinterp (binding-named-expr (first lob))
                                ds)
                            ds))]))

;;  rinterp : WAE DefrdSub -> number
;;  Comsome uma WAE e um DerfdSub e devolve seu valor numerico.
(define (rinterp expr ds)
    (type-case WAE expr
        [num (n) n]
        [binop (op l r) (binoperation op (rinterp l ds) (rinterp r ds ))]
        [with (lob body) (rinterp body (mount-aSub lob ds))]
        [id (v) (lookup v ds)]))

;;;;;;;;;;;;;;;;;;;;;
;; Parse e Interp  ;;
;;;;;;;;;;;;;;;;;;;;;

;;  parse : s-exp -> WAE
;;  Consome s-expression e gera a expressao WAE correspondente.
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
            (error 'parse "Entrada invalida para o parser.") ) ]
        [else ( error 'parse "Entrada invalida para o parser." ) ] ) )

;;  interp : WAE -> number
;;  Consome uma WAE e devolve seu valor numerico.
(define (interp expr ) (rinterp expr (mtSub)))

;;;;;;;;;;;;
;; Testes ;;
;;;;;;;;;;;;

;; Teste do Parse.
(test (parse '{ with {{x 5}{y 10}} {with { z { + y 42 } } { - { + { * x y } {/ 20 10 } } z } } })
                (with (list (binding 'x (num 5)) (binding 'y (num 10)))
                    (with (list (binding 'z (binop + (id 'y) (num 42))))
                         (binop - (binop + (binop * (id 'x) (id 'y)) (binop / (num 20) (num 10))) (id 'z )))))
(test/exn (parse '{with {x 5}}) "Entrada invalida para o parser.")
(test/exn (parse '{rashubirubida}) "Entrada invalida para o parser.")

;;  Testes das funcoes auxiliares do parse.

;;  lobmanager
(test (lobmanager '{y 5} '() ) (list (binding 'y (num 5 ))))
(test/exn (lobmanager '{{y 5}{y 6}} '() ) "Identificador repitido dentro de with.")
(test/exn (lobmanager '{{y 5}{6 6}} '() ) "O with precisa de um simbolo no primeiro elemeneto de cada par.")
(test/exn (lobmanager '{{y 5}{y 6 7}} '() ) "Cada substituicao do with tem que ter duas partes, o simbolo e sua definicao.")
(test/exn (lobmanager '{y 5 6} '() ) "Definicao do simbolo do With errda.")
(test/exn (lobmanager '{6} '() ) "Definicao do simbolo do With errda.")
(test/exn (lobmanager '{6 6} '()) "O with precisa de um simbolo para ser definido.")

;;  lobisthere
(test (lobisthere 'x (list (binding 'x (num 5 )))) #t)
(test (lobisthere 'y (list (binding 'x (num 5 )))) #f)

;;  searchbinop
(test (searchbinop '+ table) + )
(test/exn (searchbinop '% table) "Operacao binaria nao definida.")

(trace mount-aSub)
(trace rinterp)
(trace searchbinop)
(trace parse)
(trace lobmanager)

(interp(parse(read)))
