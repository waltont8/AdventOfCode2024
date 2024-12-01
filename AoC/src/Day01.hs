module Day01
    ( day01
    ) where

import Lazy
import qualified Data.Map as M


day01 :: String -> (String, String)
day01 = lines >>> parse >>> part1 &&& part2 >>> tidy

parse :: [String] -> [[Int]]
parse p = transpose $ map (splitOn " " >>> filter (/= "") >>> map read ) p

part1 :: [[Int]]-> Int
part1 s = sum $ (\[a,b] -> zipWith (dist) b a) $ map sort s


part2 :: [[Int]] -> Int
part2 s = sum $ map (\x -> x * ( if M.member x right then right M.! x else 0)) left
    where
        inOrder = map sort s
        left = inOrder!!0
        right = M.fromList $ zip (map head $ group $ sort $ inOrder!!1) (map length $ group $ sort $ inOrder!!1)

tidy :: (Int, Int) -> (String, String)
tidy (a,b) = (show a, show b)

dist a b = abs $ a - b
