%list2set( +Xs, ?XS )
list2set( [], [] ).
list2set( [ X | Xs ], [ X | YS ] ) :-
	del_todos( X, Xs, X1s ),
	list2set( X1s, YS ).

del_todos( _, [], [] ).
del_todos( X, [X|Xs], Ys ) :-
	del_todos(X,Xs,Ys).
del_todos( X, [Y|Xs], [Y|Ys] ) :-
	X \= Y,
	del_todos(X,Xs,Ys).

%union( +XS, +YS, ?ZS )
% ZS = XS U YS
uniao( [], YS, YS ) :- !.
uniao( [ X | XS ], YS, ZS ) :-
	member( X, YS ),
	!,
	uniao( XS, YS, ZS ).
uniao( [ X | XS ], YS, [ X | ZS ] ) :-
	!,
%	\+ member( X, YS ),
	uniao( XS, YS, ZS ).

%inter( +XS, +YS, ?ZS )
% ZS = XS inter YSinter
inter( [], _, [] ) :- !.
inter( [ X | XS ], YS, [ X | ZS ] ) :-
	member( X, YS ),
%	!,
	inter( XS, YS, ZS ).
inter( [ X | XS ], YS, ZS ) :-
	\+ member( X, YS ),
%	!,
	inter( XS, YS, ZS ).

%Ordena uma lista de números pelo merge sort
merge_sort( [], [] ).
merge_sort( [X], [X] ).
merge_sort( [X1,X2|Xs], Ys ) :-
	racha( [X1,X2|Xs], X1s, X2s ),
	merge_sort( X1s, Y1s ),
	merge_sort( X2s, Y2s ),
	intercala( Y1s, Y2s, Ys ).

racha( [], [], [] ).
racha( [X], [X], [] ).
racha( [ X1, X2 | Xs ], [ X1 | X1s ], [ X2 | X2s ] ) :-
	racha( Xs, X1s, X2s ).

intercala( [], Ys, Ys ).
intercala( Xs, [], Xs ).
intercala( [X|Xs], [Y|Ys], [X|Zs] ) :-
	X < Y,
	intercala( Xs, [Y|Ys], Zs ).
intercala( [X|Xs], [Y|Ys], [Y|Zs] ) :-
	X >= Y,
	intercala( [X|Xs], Ys, Zs ).
