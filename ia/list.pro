
% listas!

gruda( [], Xs, Xs ).
gruda( [ X | Xs ], Ys, [ X | Zs ] ) :-
    gruda( Xs, Ys, Zs ).

%split( Xs, Y, Zs )
split( [], [], [] ).
split( [X], [X], [] ).
split( [X,Y|Xs], [X|Ys], [Y|Zs] ) :-
    split( Xs, Ys, Zs ).

%merge( Xs, Ys, Zs ) : assume que Xs e Ys estão ordenados.
merge( [], Xs, Xs ).
merge( Xs, [], Xs ).
merge( [X|Xs], [Y|Ys], [X|Zs] ) :-
    X =< Y,
    merge( Xs, [Y|Ys], Zs ).
merge( [X|Xs], [Y|Ys], [Y|Zs] ) :-
    X > Y,
    merge( [X|Xs], Ys, Zs ).

%mergesort
mergesort( [], [] ).
mergesort( [X], [X] ).
mergesort( [X,Y|Xs], Xords ) :-
    split([X,Y|Xs], Ys, Zs),
    mergesort( Ys, Yords ),
    mergesort( Zs, Zords ),
    merge( Yords, Zords, Xords ).


