module Laziness (isPrime, primes) where	

isPrime :: Integer -> Bool

isPrime n = isPrimeAux n primes
	
isPrimeAux :: Integer -> [Integer] -> Bool

isPrimeAux a primes
	|	a <= 1 = False
	|	hp == a = True
	|	(mod a hp) == 0 = False
	|	otherwise = isPrimeAux a (tail primes)
	where hp = head primes

primes :: [Integer]

primes = 2:[ x | x <- [3..], mountPrimes x 2 == True]

mountPrimes :: Integer -> Integer -> Bool

mountPrimes a b
	| 	b == a = True
	| 	mod a b == 0 = False
	|	otherwise = mountPrimes a (b+1)
