module Day25
    ( day25
    ) where

import Lazy


day25 :: String -> (String, String)
day25 = lines >>> parse >>> part1 >>> tidy

parse :: [String] -> ([[String]], [[String]])
parse =  listSplit (==[]) >>>  (isKey >>> map transpose) &&& (isLock >>> map transpose)
    where
        isKey = filter (\x -> last (head x) == '.')
        isLock = filter (\x -> head (head x) == '#')

part1 :: ([[String]], [[String]]) -> Int
part1 (a,b) = length $ filter unlocks [ (x,y) | x <- a, y <- b ]
    where
        unlocks (l,k) = all ((<8) . count '#') (zipWith (++) l k)

count :: Eq a => a -> [a] -> Int
count x = length . filter (x==)


tidy :: Int -> (String, String)
tidy a = (show a, "No part 2")
