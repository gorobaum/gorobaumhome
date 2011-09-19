
% fatos da bíblia
pai( abrao, isac ).
pai( isac, jaco ).
pai( isac, esau ).
pai( jaco, jose ).
pai( jaco, levi ).
pai( jaco, rubem ).
pai( jose, efraim ).
pai( jose, manasses ).

neto( Avo, Neto ) :-
    pai( Avo, X ),
    pai( X, Neto ).


mae( sara, isaac ).
mae( rebeca, jaco ).
mae( rebeca, esau ).
mae( raquel, jose ).

% avo, avó, progenitor, filho, filha, ancestral, irmão, primo

progenitor( P, F ) :- pai( P, F ).
progenitor( P, F ) :- mae( P, F ).

d( X, Y ) :- progenitor(X, Y).
d( X, Y ) :-
    progenitor( Z, Y ),
    d( X, Z ).

irmao( X, Y ) :-
    progenitor( P, X ),
    progenitor( P, Y ),
    X @< Y.

primo( X, Y ) :-
    progenitor( P1, X ),
    progenitor( P2, Y ),
    irmao( P1, P2 ).

%%% aula prolog 2

ama( X, mae( X ) ).
ama( X, filha( Y ) ) :-
    interesseiro( X ),
    rico( Y ).

interesseiro( ze ).
rico( mane ).














