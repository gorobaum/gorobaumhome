% %[o,menino,comeu,o,bolo]
% s(sn(d(o),n(menino)),sv(v(comeu),sn(d(o),n(bolo))))
sentenca( s( SN, SV ) ) -->
	sintagma_nominal( SN ),
	sintagma_verbal( SV ).

sintagma_nominal( sn( D, N ) ) -->
	determinante( D, Gen ),
	nome( N, Gen ).

sintagma_verbal( sv( V, SN ) ) -->
	verbo_transitivo( V ),
	sintagma_nominal( SN ).

determinante( d( X ), Gen ) --> [X], {det(X,Gen)}.

det( a, fem ).
det( o, masc ).
det( um, masc ).
det( uma, fem ).

verbo_transitivo( vt( V) ) --> [V],{vt(V)}.

vt( comeu ).

nome( n( N ), Gen ) --> [N],{nome(N,Gen)}.

nome( menino, masc ).
nome( bolo, masc ).

imprime_arvore( A ) :-
	imprime_arvore( A, 0 ).

imprime_arvore( A, N ) :-
	A =.. [ X | As ],
	tab( N ),
	write( X ),
	nl,
	N1 is N+2,
	imprime_lista( As, N1 ).

imprime_lista( [], _ ).
imprime_lista( [ A | As ], N ) :-
	imprime_arvore( A, N ),
	imprime_lista( As, N ).

