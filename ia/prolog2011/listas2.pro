contem_inteiro( [ X | _ ] ) :-
	integer( X ).
contem_inteiro( [ _ | Xs ] ) :-
	contem_inteiro( Xs ).

todos_inteiros( [] ).
todos_inteiros( [ X | Xs ] ) :-
	integer( X ),
	todos_inteiros( Xs ).

vogal( a ).
vogal( e ).
vogal( i ).
vogal( o ).
vogal( u ).

sem_consoantes( [] ).
sem_consoantes([ X | Xs ]) :-
	vogal( X ),
	sem_consoantes( Xs ).


%% Primeira Versão: usar um contador
enesimo_elemento( N, Xs, X ) :-
	enesimo( 1, N, Xs, X ).

enesimo( N, N, [ X | _ ], X ).
enesimo( M, N, [ _ | Xs ], X ) :-
	Mmais1 is M+1,
	enesimo( Mmais1, N, Xs, X ).

%% Segunda versão: decrementa N
enesimo( 1, [ X | _ ], X ).
enesimo( N, [_|Xs], X ) :-
	N>1,
	Nmenos1 is N-1,
	enesimo( Nmenos1, Xs, X ).

%% fat1
fat1( 0, 1 ).
fat1( N, F ) :-
	N > 0,
	N1 is N-1,
	fat1( N1, F1 ),
	F is F1*N.

fat2( N, F ) :-
	fat2( N, 1, F ).

fat2( 0, F, F ).
fat2( N, Acc, F ) :-
	N>0,
	N1 is N-1,
	Acc1 is Acc*N,
	fat2( N1, Acc1, F ).

/* Exercicios:
   proximo: proximo( a, [b,r,a,s,i,l], X ) ===> X = s
   del1: del1(a, [b,a,n,a,n,a], Xs ) ===> Xs = [b,n,a,n,a]
   det_todos: del_todos(a, [b,a,n,a,n,a], Xs ) ===> Xs = [b,n,n] (usar \= )
   somatoria: somatoria([1,34,-5], X ) ===> X=30
   fibonacci: fib( 5, F ) ==> F = 5 
*/