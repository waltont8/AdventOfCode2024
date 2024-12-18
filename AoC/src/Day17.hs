module Day17
    ( day17
    ) where

import Lazy
{--
import Data.Bits
import Debug.Trace

list = [2,4,1,1,7,5,1,5,4,3,5,5,0,3,3,0]
flatten :: [[a]] -> [a]         
flatten xs = (\z n -> foldr (\x y -> foldr z y x) n xs) (:) []
someFunc :: IO ()
someFunc = putStrLn $ flatten $ map show $ grind list 0 164278899142333 0 0

comboVal p a b c
  | p == 4 = a
  | p == 5 = b
  | p == 6 = c
  | otherwise = p

grind :: [Int] -> Int -> Int -> Int -> Int -> [Int]
grind p ip a b c
         | ((ip >= length p - 1)) = []
{--adv--}| p!!ip == 0 = grind p (ip+2) (a `div` (2^combo)) b c
{--bxl--}| p!!ip == 1 = grind p (ip+2) a (b `xor` oper) c
{--bst--}| p!!ip == 2 = grind p (ip+2) a (combo `mod` 8) c
{--jnz--}| p!!ip == 3 && a > 0 = grind p oper a b c
{--jnz--}| p!!ip == 3 && a == 0 = grind p (ip+2) a b c
{--bxc--}| p!!ip == 4 = grind p (ip+2) a (b `xor` c) c
{--out--}| p!!ip == 5 = (combo `mod` 8) : grind p (ip+2) a b c
{--bdv--}| p!!ip == 6 = grind p (ip+2) a (a `div` (2^combo)) c
{--cdv--}| p!!ip == 7 = grind p (ip+2) a b (a `div` (2^combo))
         | otherwise = [(-1)]
         where
            combo = comboVal (p!!(ip+1)) a b c
            oper = (p!!(ip+1))
            state = " ip:" ++ show ip ++ " A:" ++ show a ++ " B:" ++ show b ++ " C:" ++ show c ++ " operand:" ++ show oper ++ " combo:" ++ show combo

            
{--
grind :: [Int] -> Int -> Int -> Int -> Int -> [Int]
grind p ip a b c
         | ((ip >= length p - 1)) = []
{--adv--}| p!!ip == 0 = trace ("adv" ++ state )$ grind p (ip+2) (a `div` (2^combo)) b c
{--bxl--}| p!!ip == 1 = trace ("bxl" ++ state)  $ grind p (ip+2) a (b `xor` oper) c
{--bst--}| p!!ip == 2 = trace ("bst" ++ state ) $ grind p (ip+2) a (combo `mod` 8) c
{--jnz--}| p!!ip == 3 && a > 0 = trace ("jnz" ++ state ) $ grind p oper a b c
{--jnz--}| p!!ip == 3 && a == 0 = trace ("jnz" ++ state)  $ grind p (ip+2) a b c
{--bxc--}| p!!ip == 4 = trace ("bxc"  ++ state) $ grind p (ip+2) a (b `xor` c) c
{--out--}| p!!ip == 5 = trace ("out"  ++ state) $ (combo `mod` 8) : grind p (ip+2) a b c
{--bdv--}| p!!ip == 6 =trace ("bdv" ++ state ) $ grind p (ip+2) a (a `div` (2^combo)) c
{--cdv--}| p!!ip == 7 =trace ("cdv" ++ state)  $ grind p (ip+2) a b (a `div` (2^combo))
         | otherwise = [(-1)]
         where
            combo = comboVal (p!!(ip+1)) a b c
            oper = (p!!(ip+1))
            state = " ip:" ++ show ip ++ " A:" ++ show a ++ " B:" ++ show b ++ " C:" ++ show c ++ " operand:" ++ show oper ++ " combo:" ++ show combo
--}
--}
day17 :: String -> (String, String)
day17 = lines >>> head >>> parse >>> part1 &&& part2 >>> tidy

parse :: String -> [String]
parse = splitOn ","

part1 :: [String] -> Int
part1 s = sum $ map read s


part2 :: [String] -> Int
part2 s = sum $ map read s

tidy :: (Int, Int) -> (String, String)
tidy (a,b) = (show a, show b)
