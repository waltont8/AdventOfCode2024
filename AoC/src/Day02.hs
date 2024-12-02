module Day02
    ( day02
    ) where

import Lazy


day02 :: String -> (String, String)
day02 = lines >>> parse >>> part1 &&& part2 >>> tidy

parse :: [String] -> [[Int]]
parse s = map (map read) $ map (splitOn " ") s

part1 :: [[Int]] -> Int
part1 (h:xs) = score + part1 xs
    where
        score = if increases h || decreases h then 1 else 0
part1 [] = 0


part2 :: [[Int]] -> Int
part2 s = sum $ map safetyCheck s

safetyCheck :: [Int] -> Int
safetyCheck h = if total > 0 then 1 else 0
    where
        a = allMissing [] h
        vals = map (\x -> if increases x || decreases x then 1 else 0) a
        total = sum vals

tidy :: (Int, Int) -> (String, String)
tidy (a,b) = (show a, show b)

increases :: [Int] -> Bool
increases (h:n:xs) = if h < n && (n-h < 4) then increases (n:xs) else False
increases [] = True
increases [a] = True

decreases :: [Int] -> Bool
decreases (h:n:xs) = if h > n && (h-n < 4) then decreases (n:xs) else False
decreases [] = True
decreases [a] = True

allMissing :: [Int] -> [Int] -> [[Int]]
allMissing h1 (h:xs) = (h1++xs) : (h1++(h:xs)) : allMissing (h1++[h]) xs
allMissing h [] = [h]