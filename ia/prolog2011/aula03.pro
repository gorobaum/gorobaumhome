subordenacao( [], _ ).
subordenacao( [ X | Xs ], [ X | Ys ] ) :-
    subordenacao( Xs, Ys ).
subordenacao( Xs, [ _| Ys ] ) :-
    subordenacao( Xs, Ys ).


todas_subordenacoes( _, _ ) :-
    retractall( registro(_) ),
    assert( [] ),
    fail.
todas_subordenacoes( Xs , _ ) :- 
    subordenacao( Ys, Xs ),
    registra( Ys ),
    fail.
todas_subordenacoes( _, ListadeSubOrdXs ) :-
    todos_registros( ListadeSubOrdXs ).

registra( Xs ) :-
    registro( Ys ),
    member( Xs, Ys ),
    !.
registra( Xs ) :-
    retract( registro( Ys ) ),
    assert( registro( [ Xs | Ys ] ) ).

todos_registros(  Ls ) :-
    retract( registro( Ls ) ).
