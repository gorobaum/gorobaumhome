% atom/1, integer/1, atomic/1
% achata( LLs, Ls).
% Ex:  achata( [[1,a], 3.5, [6, [7, b],[]]], [1,a,3.5,6,7,b] ).

achata( [], [] ).
achata( [ Xs | Ys ], Zs ) :-
    achata( Xs, X1s ),
    achata( Ys, Y1s ),
    append( X1s, Y1s, Zs ).
achata( X, [X] ) :-
    X \= [],
    atomic( X ).

esmaga( Xs, Ys ) :-
    esm( Xs, Ys - [] ).

esm( [], Zs - Zs ).
esm( [ Xs | Ys ], Zs - Ws ) :-
    esm( Xs, Zs - Us ),
    esm( Ys, Us - Ws ).
esm( X, [ X | Xs ] - Xs ) :-
    X \= [],
    atomic(X).

%Termo =.. Lista
% f(a,b,c) =..  Xs.
% T =.. [+,1,2].
% T =.. [+,1,Y].
numeric( X ) :-
    atomic( X ),
    not( atom( X ) ).
    
incrementa( X, Y ) :-
    numeric( X ),
    Y is X + 1.
incrementa( X, Y ) :-
    var( X ), numeric( Y ),
    X is Y - 1.

map_incrementa( [], [] ).
map_incrementa( [ X | Xs ], [ Y | Ys ] ) :-
    incrementa( X, Y ),
    map_incrementa( Xs, Ys ).

%map_lista( Xs, PredBinario, Ys ).
map_lista( [], _, [] ).
map_lista( [ X | Xs ], PredBinario, [ Y | Ys ] ) :-
    T =.. [ PredBinario, X, Y ],
    T,
    map_lista( Xs, PredBinario, Ys ).

primo( X ) :-
    prim( X, 2 ).

prim( X, Cont ) :-
    Cont*Cont > X, !.
prim( X, Cont ) :-
%    Cont*Cont =< X,
    Resto is X mod Cont,
    Resto \= 0,
    C1 is Cont + 1,
    prim( X, C1 ).

%filtra_primos( Numeros, Primos, Nao-primos )
filtra_primos( [], [], [] ) :- !.
filtra_primos( [ N | Ns ], [ N | Ps ], NPs ) :-
    primo( N ),
    !,
    filtra_primos( Ns , Ps, NPs ).
filtra_primos( [ N | Ns ], Ps, [ N | NPs] ) :-
    %\+ primo( N ),
    !,
    filtra_primos( Ns , Ps, NPs ).

feio(a).

bonito(X) :- \+ feio(X).
%q(a)
%q(b)
%q( X ). !!!!

%Cuts

if_then_else( C, Then, _ ) :-
    C,
    !,
    Then.
if_then_else( _, _, Else ) :-
    Else.