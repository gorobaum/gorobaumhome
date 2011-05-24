module Laziness (isPrime, primes, buildList, buildTable, lcsLength) where	

isPrime :: Integer -> Bool

primes :: [Integer]

--------------------------

buildList :: Int -> (Int -> a) -> [a]

buildTable :: Int -> Int -> (Int -> Int -> a) -> [[a]]

lcsLength :: String -> String -> Int
