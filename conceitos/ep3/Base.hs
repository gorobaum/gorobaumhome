
module Laziness (isPrime, primes, buildList, buildTable, lcsLength, mkTree, mancala, prune, minimax, level) where

import Game

isPrime :: Integer -> Bool

primes :: [Integer]

--------------------------

buildList :: Int -> (Int -> a) -> [a]

buildTable :: Int -> Int -> (Int -> Int -> a) -> [[a]]

lcsLength :: String -> String -> Int

--------------------------

-- This is the GameTree datatype you should define.
data GameTree = ...

-- mkTree s yields the complete GameTree whose root has state s
mkTree :: State -> GameTree

-- mancala is the entire game of mancala as a GameTree.  Note that PlayerA
-- goes first.
mancala :: GameTree

-- prune n gt such that n > 0 yields a GameTree equivalent to gt of depth n.
-- Note: prune 0 gt is nonsense; do not provide an equation for prune 0 gt.
prune :: Int -> GameTree -> GameTree

-- minimax gt yields the minimaxed gameValue of the given GameTree.  Keep in
-- mind that PlayerA always wants to maximize the gameValue and PlayerB wants
-- to minimize it.
minimax :: GameTree -> GameValue

-- level n simulates a game of mancala such that PlayerA (who goes first) is
-- controlled by your minimax AI, with n levels of lookahead.  We have written
-- this one for you.
level :: Int -> IO ()
level n = simulateAIGame (minimax . (prune n) . mkTree)

