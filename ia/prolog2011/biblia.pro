pai( abraao, isac ).
pai( isac, jaco ).
%pai( isac, esau ).
%pai( jaco, jose ).

mae( x, y ) :- fail.
%mae( sara, isac ).
%mae( rebeca, jaco ).
%mae( rebeca, esau ).
%mae( raquel, jose ).

avo( X, Y ) :-
	pai( X, Z ),
	pai( Z, Y ).

progenitor( X, Y ) :- pai( X, Y ).
progenitor( X, Y ) :- mae( X, Y ).

irmao( X, Y ) :-
	progenitor( Z, X ),
	progenitor( Z, Y ),
	X @< Y.

ancestral( X, Y ) :- progenitor( X, Y ).
ancestral( X, Y ) :-
	progenitor( X, Z ),
	ancestral( Z, Y ).

anc( A, B ) :-
	progenitor( A, B ).
anc( A, B ) :-
	anc( A, C ),
	progenitor( C, B ).

todos_ancestrais :-
	ancestral( X, Y ),
	write( X ),
	write( ', ' ),
	write( Y ),
	nl,
	fail.

todos_anc :-
	anc( X, Y ),
	write( X ),
	write( ', ' ),
	write( Y ),
	nl,
	fail.