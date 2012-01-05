ama( X, mae(X) ).
ama( X, filha( Y ) ) :-
    interesseiro( X ),
    rico( Y ).

interesseiro( ze ).
rico( mane ).

membro( X, [ X | _ ] ).
membro( X, [ _ | Xs ] ) :-
    membro( X, Xs ).

gruda( [], Xs, Xs ).
gruda( [ X | Xs ], Ys, [ X | Zs ] ) :-
    gruda( Xs, Ys, Zs ).

%split( Xs, Ys, Zs )
split( [], [], [] ).
split( [X], [X], [] ).
split( [X,Y|Xs], [X|Ys], [Y|Zs] ) :-
    split( Xs, Ys, Zs ).

% merge( Xs, Ys, Zs ) : assume que Xs e Ys estão ordenadas
merge( [], Xs, Xs ).
merge( Xs, [], Xs ).
merge( [X|Xs], [Y|Ys], [X|Zs] ) :-
    X =< Y,
    merge( Xs, [Y|Ys], Zs ).
merge( [X|Xs], [Y|Ys], [Y|Zs] ) :-
    X > Y,
    merge( [X|Xs], Ys, Zs ).

mergesort( [], [] ).
mergesort( [X], [X] ).
mergesort( [X, Y | Xs], Xordenadas ) :-
    split( [X, Y| Xs], Ys, Zs ),
    mergesort( Ys, YOs ),
    mergesort( Zs, ZOs ),
    merge( YOs, ZOs, Xordenadas ).
