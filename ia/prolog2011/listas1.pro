membro( X, [ X | _ ] ).
membro( X, [ _ | Xs ] ) :-
	membro( X, Xs ).

gruda( [], Ys, Ys ).
gruda( [X|Xs], Ys, [X|Zs] ) :-
	gruda( Xs, Ys, Zs ).

prefixo( [], _ ).   % A lista vazia é prefixo de qqer lista
prefixo( [X|Xs], [X|Ys] ) :-
	prefixo( Xs, Ys ).

sufixo( Xs, Xs ).
sufixo( Xs, [_|Ys] ) :-
	sufixo( Xs, Ys ).

sublista1( Xs, Ys ) :-
	prefixo( Zs, Ys ),
	sufixo( Xs, Zs ).

sublista2( Xs, Ys ) :-
	sufixo( Zs, Ys ),
	prefixo( Xs, Zs ).

inverte1( [], [] ).
inverte1( [X|Xs], Ys ) :-
	append( Y1s, [X], Ys ),
	inverte( Xs, Y1s ).

inverte( Xs, Ys ) :-
	inverte( Xs, [], Ys ).

inverte( [], Auxs, Auxs ).
inverte( [X|Xs], Auxs, Ys ) :-
	inverte( Xs, [X|Auxs], Ys ).
