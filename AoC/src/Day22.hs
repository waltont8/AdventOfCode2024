module Day22
    ( day22
    ) where

import Lazy
import Data.Bits

day22 :: String -> (String, String)
day22 = lines >>> parse >>> part1 &&& part2 >>> tidy

parse :: [String] -> [Integer]
parse = map read

part1 :: [Integer] -> Integer
part1 i = sum b
    where
        a = map process2k i
        b = map last a


part2 :: [Integer] -> Int
part2 i = c
    where
        a = map process2k i
        b = map p2Data a
        allLists = flatten b
        allWindows = getWindows allLists
        f = trace (show $ length allWindows) $ reverse $ map head $ sortOn length $ group $ sort allWindows
        c = trace (show $ length f) $ findBest b f 0

getWindows :: [(a, b)] -> [((a, b), (a, b), (a, b), (a, b))]
getWindows ((i1,v1):(i2,v2):(i3,v3):(i4,v4):xs) = ((i1,v1),(i2,v2),(i3,v3),(i4,v4)) : getWindows ((i2,v2):(i3,v3):(i4,v4):xs)
getWindows _ = []


tidy :: (Integer, Int) -> (String, String)
tidy (a,b) = (show a, show b)

mix :: Integer -> Integer -> Integer
mix a b = a `xor` b

prune :: Integer -> Integer
prune a = a `mod` 16777216

step :: Integer -> Integer
step i = s9
    where
        s1 = i * 64
        s2 = mix s1 i
        s3 = prune s2
        s4 = s3 `div` 32
        s5 = mix s4 s3
        s6 = prune s5
        s7 = s6 * 2048
        s8 = mix s7 s6
        s9 = prune s8

process2k :: Integer -> [Integer]
process2k i = i : take 2000 (process i)

process :: Integer -> [Integer]
process i = n : process n
    where
        n = step i

lastNums :: [Integer] -> [Int]
lastNums = map show >>> map last >>> map readChar

getDiffs :: [Int] -> [Int]
getDiffs i = 0 : zipWith (-) (tail i) i


p2Data :: [Integer] -> [(Int,Int)]
p2Data i = zip ln ds
    where
        ln = lastNums i
        ds = getDiffs ln


findBest :: [[(Int,Int)]] -> [((Int,Int),(Int,Int),(Int,Int),(Int,Int))] -> Int -> Int
findBest allNums (((i1,v1),(i2,v2),(i3,v3),(i4,v4)):xs) best = trace (show best ++ " " ++ show (length xs)) $ if v > best then findBest allNums xs v else findBest allNums xs best
    where
        t = getVals allNums (v1,v2,v3,v4)
        v = sum t
findBest _ _ b = b

getVals :: [[(Int, Int)]] -> (Int, Int, Int, Int) -> [Int]
getVals (h : xs) (a,b,c,d) = t : getVals xs (a,b,c,d)
    where
        t = getVal h (a,b,c,d)
getVals[] _ = []

getVal :: [(Int,Int)] -> (Int,Int,Int,Int) -> Int
getVal ((i1,v1):(i2,v2):(i3,v3):(i4,v4):xs) (a,b,c,d) = if v1 == a && v2 == b && v3 == c && v4 == d then i4 else getVal ((i2,v2):(i3,v3):(i4,v4):xs) (a,b,c,d)
getVal _ _ = 0
