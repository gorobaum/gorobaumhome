module Laziness (isPrime, primes, buildList, buildTable) where	

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

primes = [ x | x <- [2..], mountPrimes x 2 == True]

mountPrimes :: Integer -> Integer -> Bool

mountPrimes a b
	| 	b == a = True
	| 	mod a b == 0 = False
	|	otherwise = mountPrimes a (b+1)
	
--------------------------

unity :: a -> a

unity a = a

buildList :: Int -> (Int -> a) -> [a]

buildList 0 f = []
buildList n f = (f (n-1)):(buildList (n-1) f)

buildTable :: Int -> Int -> (Int -> Int -> a) -> [[a]]

buildTable n m f
    |   m == 0 = []
    |   n == 0 = []
    |   otherwise = (f (n-1) (m-1)):(buildTable n (m-1) f)
