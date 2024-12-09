module Day08
    ( day08
    ) where

import Lazy

-- You did this one in C, file in same folder.

day08 :: String -> (String, String)
day08 = lines >>> parse >>> part1 &&& part2 >>> tidy

parse :: [String] -> [String]
parse l = l

part1 :: [String] -> Int
part1 s = sum $ map read s


part2 :: [String] -> Int
part2 s = sum $ map read s

tidy :: (Int, Int) -> (String, String)
tidy (a,b) = (show a, show b)
