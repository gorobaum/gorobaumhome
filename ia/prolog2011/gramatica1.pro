% %[o,menino,comeu,o,bolo]
% s(sn(d(o),n(menino)),sv(v(comeu),sn(d(o),n(bolo))))
sentenca( S ) :-
	sintagma_nominal( SN ),
	sintagma_verbal( SV ),
	append( SN, SV, S ).

sintagma_nominal( SN ) :-
	determinante( D ),
	nome( N ),
	append( D, N, SN ).

sintagma_verbal( SV ) :-
	verbo_transitivo( VT ),
	sintagma_nominal( SN ),
	append( VT, SN, SV ).

determinante( [uma] ).
determinante( [um]).
determinante( [a] ).
determinante( [o] ).

verbo_transitivo( [comeu] ).

nome( [menino] ).
nome( [bolo] ).
