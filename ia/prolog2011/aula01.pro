pai( abraao, isac ).
pai( isac, jaco ).
pai( isac, esau ).
pai( jaco, jose ).
%pai( jaco, levi ).
%pai( jaco, 'Rubem' ).
%pai( jose,  efraim ).
%pai( jose, manasses ).

d( X, Y ) :- pai( X, Y ).
d( X, Y ) :-
    pai( X, Z ),
    d( Z, Y ).

neto( Avo, Neto ) :-
    pai( Avo, X ),
    pai( X, Neto ).

mae( sara, isac ).
mae( rebeca, jaco ).
mae( rebeca, esau ).
mae( raquel, jose ).

% avo, avó, progenitor, filho, filha, ancestral, irmão, primo

progenitor( P, F ) :- pai( P, F ).
progenitor( P, F ) :- mae( P, F ).

descendente( X, Y ) :-
    progenitor( X, Z ),
    descendente( Z, Y ).
descendente( X, Y ) :-
    progenitor( X, Y ).

% Irmão: o ingênuo
irmao( X, Y ) :-
    progenitor( Z, X ),
    progenitor( Z, Y ),
    X @< Y.

primo( A, B ) :-
    progenitor( PA, A ),
    progenitor( PB, B ),
    irmao( PA, PB ).