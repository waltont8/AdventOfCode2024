module Day25
    ( day25
    ) where

import Lazy


day25 :: String -> (String, String)
day25 = lines >>> head >>> parse >>> part1 &&& part2 >>> tidy

parse :: String -> [String]
parse = splitOn ","

part1 :: [String] -> Int
part1 s = sum $ map read s


part2 :: [String] -> Int
part2 s = sum $ map read s

tidy :: (Int, Int) -> (String, String)
tidy (a,b) = (show a, show b)
