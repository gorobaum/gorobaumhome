%fatorial ingênuo
fatorial(0, 1 ).
fatorial( N, F ) :-
    N1 is N - 1,
    fatorial( N1, F1 ),
    F is F1 * N.

% fatorial smart
fat( N, F ) :- fat( N, 1, F ).

fat( 0, F, F ).
fat( N, Ret, F ) :-
    N > 0,
    N1 is N - 1,
    Ret1 is Ret * N,
    fat( N1, Ret1, F ).

fiburro( 1, 1 ).
fiburro( 2, 1 ).
fiburro( N, F ) :-
    N > 2,
    N1 is N - 1,
    N2 is N - 2,
    fiburro( N1, F1 ),
    fiburro( N2, F2 ),
    F is F1 + F2.

%Fibonacci esperto
fibonacci( N, F ) :-
    fib( N, 1, 1, F ).

fib( 1, _, F, F ).
fib( 2, F, _, F ).
fib( N, FibNmenos1, FibNmenos2, F ) :-
    N > 2,
    N1 is N-1,
    Fib is FibNmenos1 + FibNmenos2,
    fib( N1, Fib, FibNmenos1, F ).
