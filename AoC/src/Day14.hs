module Day14
    ( day14
    ) where

import Lazy

import Data.Char (isDigit)

day14 :: String -> (String, String)
day14 = lines >>> parse >>> part1 &&& part2 >>> tidy

parse :: [String] -> [((Int,Int),(Int,Int))]
parse s = map tupleIfy ints
    where
        ints = map getInts s
        tupleIfy [a,b,c,d] = ((a,b),(c,d))

part1 :: [((Int,Int),(Int,Int))] -> Int
part1 s = q1*q2*q3*q4
    where
        f = map (advance 100) s
        (q1,q2,q3,q4) = quad (0,0,0,0) f

quad (a,b,c,d) ((x,y):xs) 
        | x < 50 && y < 51 = quad (a+1,b,c,d) xs
        | x > 50 && y < 51 = quad (a,b+1,c,d) xs
        | x < 50 && y > 51 = quad (a,b,c+1,d) xs
        | x > 50 && y > 51 = quad (a,b,c,d+1) xs
        | otherwise = quad (a,b,c,d) xs
quad (a,b,c,d) [] = (a,b,c,d)

advance :: Int -> ((Int,Int),(Int,Int)) -> (Int,Int)
advance 0 ((x,y),(vx,vy)) = (x,y)
advance c ((x,y),(vx,vy)) = advance (c-1) ((cx,cy),( vx,vy))
    where
        nx = (x + vx) `mod` 101
        ny = (y + vy) `mod` 103
        cx = if nx < 0 then nx+ 102 else nx
        cy = if ny < 0 then ny+ 104 else ny

part2 :: [((Int,Int),(Int,Int))] -> Int
part2 s = 0

tidy :: (Int, Int) -> (String, String)
tidy (a,b) = (show a, show b)
