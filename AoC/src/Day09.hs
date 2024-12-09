module Day09
    ( day09
    ) where

import Lazy


day09 :: String -> (String, String)
day09 = parse >>> part1 &&& part2 >>> tidy

parse :: String -> [(Int,Int)]
parse = zip [0..]

part1 :: [String] -> Int
part1 s = sum $ map read s


part2 :: [String] -> Int
part2 s = sum $ map read s

tidy :: (Int, Int) -> (String, String)
tidy (a,b) = (show a, show b)
