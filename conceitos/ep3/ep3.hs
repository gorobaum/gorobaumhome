module Laziness (isPrime, primes, buildList, buildTable, lcsLength) where

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
buildList :: Int -> (Int -> a) -> [a]

buildList n f = [ (f x) | x <-[0..], x < n]

buildTable :: Int -> Int -> ( Int -> Int -> a) -> [[a]]

buildTable 0 m f = []
buildTable n m f = [(f n y)| y <-[0..m]]:buildTable (n-1) m f

lcsLength :: String -> String -> Int

lcsLength s1 s2
    |   length s1 == 0 = 0
    |   length s2 == 0 = 0
    |   ( s1 !! i ) == ( s2 !! j ) = (lcsLength (take i s1) (take j s2)) + 1
    |   otherwise = max (lcsLength (take i s1) s2) (lcsLength s1 (take j s2))
    where   i = ((length s1)-1) 
            j = ((length s2)-1)
