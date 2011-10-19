% %[o,menino,comeu,o,bolo]
% s(sn(d(o),n(menino)),sv(v(comeu),sn(d(o),n(bolo))))
sentenca( S, S0 ) :-
	sintagma_nominal( S, S1 ),
	sintagma_verbal( S1,S0 ).

sintagma_nominal( SN, SN0 ) :-
	determinante( SN, SN1 ),
	nome( SN1, SN0 ).

sintagma_verbal( SV, SV0 ) :-
	verbo_transitivo( SV, SV1 ),
	sintagma_nominal( SV1, SV0 ).

determinante( [o | Resto], Resto ).
determinante( [a | Resto], Resto ).
determinante( [um | Resto], Resto ).
determinante( [uma | Resto], Resto ).

verbo_transitivo( [comeu | Resto], Resto ).

nome( [menino | Resto], Resto ).
nome( [bolo | Resto], Resto ).

