% %[o,menino,comeu,o,bolo]
% s(sn(d(o),n(menino)),sv(v(comeu),sn(d(o),n(bolo))))
sentenca( s( SN, SV ) ) -->
	sintagma_nominal( SN ),
	sintagma_verbal( SV ).

sintagma_nominal( sn( D, N ) ) -->
	determinante( D ),
	nome( N ).

sintagma_verbal( sv( V, SN ) ) -->
	verbo_transitivo( V ),
	sintagma_nominal( SN ).

determinante( d( o ) ) --> [o].
determinante( d( a ) ) --> [a].
determinante( d( um ) ) --> [um].
determinante( d( uma ) ) --> [uma].

verbo_transitivo( vt( comeu ) ) --> [comeu].

nome( n( menino ) ) --> [menino].
nome( n( bolo ) ) --> [bolo].

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

