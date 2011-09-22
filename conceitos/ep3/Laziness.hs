module Laziness (isPrime, primes, buildList, buildTable, lcsLength) where

isPrime :: Integer -> Bool

isPrime 0 = False
isPrime 1 = False
isPrime n = (takeWhile (\y -> mod n y /= 0) auxprime ) == auxprime
    where auxprime = (takeWhile (\x -> x*x <= n) primes)
	
primes :: [Integer]

primes = 2:[ x | x <- [3,5..], isPrime x == True]

--------------------------
buildList :: Int -> (Int -> a) -> [a]

buildList n f = [ (f x) | x <-[0..(n-1)]]

buildTable :: Int -> Int -> ( Int -> Int -> a) -> [[a]]

buildTable n m f = [buildList m (f x) | x <- [0..(n-1)]] 

lcsLength :: String -> String -> Int

lcsLength s1 s2
    |   length s1 == 0 = 0
    |   length s2 == 0 = 0
    |   ( s1 !! i ) == ( s2 !! j ) = (lcsLength (take i s1) (take j s2)) + 1
    |   otherwise = max (lcsLength (take i s1) s2) (lcsLength s1 (take j s2))
    where   i = ((length s1)-1) 
            j = ((length s2)-1)
