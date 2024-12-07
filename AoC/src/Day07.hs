module Day07
    ( day07
    ) where

import Lazy


day07 :: String -> (String, String)
day07 = lines >>> map parse >>> part1 &&& part2 >>> tidy

parse :: String -> (Int, [Int])
parse s = (test, nums)
    where
     [test_s,nums_s] = splitOn ": " s
     test = read test_s
     nums = map read $ splitOn " " nums_s 

part1 :: [(Int, [Int])] -> Int
part1 p = sum $ map wrap p
    where
        wrap (t,(h:xs)) = womble t h xs

part2 :: [(Int, [Int])] -> Int
part2 p = sum $ map wrap p
    where
        wrap (t,(h:xs)) = womble2 t h xs

womble :: Int -> Int -> [Int] -> Int
womble t r (h:xs) = if a > 0 then a else b
    where
        a = womble t (r+h) xs
        b = womble t (r*h) xs
womble t r [] = if t == r then t else 0

womble2 :: Int -> Int -> [Int] -> Int
womble2 t r (h:xs) | a > 0 = a
                   | b > 0 = b
                   | c > 0 = c
                   | otherwise = 0
    where
        a = womble2 t (r+h) xs
        b = womble2 t (r*h) xs
        c = womble2 t (read ((show r) ++ (show h))) xs
womble2 t r [] = if t == r then t else 0

tidy :: (Int, Int) -> (String, String)
tidy (a,b) = (show a, show b)
