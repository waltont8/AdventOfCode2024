module Day05
    ( day05
    ) where

import qualified Data.Map as M

import Lazy

type Rules = M.Map Int [Int]

day05 :: String -> (String, String)
day05 = lines >>> parse >>> part1 &&& part2 >>> tidy

parse :: [String] -> (Rules, [[Int]])
parse s = (rules, candidates)
    where
        v = listSplit (==[]) s
        rules = getRules $ head v
        candidates = map (map read) $ map (splitOn ",") (v!!1)

getRules :: [String] -> Rules
getRules = foldl addRule M.empty

addRule :: Rules -> String ->  Rules
addRule rules row = M.insert f l rules
    where
        l = s:lookupRule rules f
        (f,s) = ((\[f,s] -> (read f, read s)) . splitOn "|") row

middle :: [a] -> a
middle zs = go zs zs
  where go (_:_:xs) ~(_:ys) = go xs ys
        go _ (y:_) = y

isSorted :: Rules -> [Int] -> Bool
isSorted r l = l == s
    where
        s = sortBy (sortRules r) l

sortRules :: Rules -> Int -> Int -> Ordering
sortRules r a b = if b `elem` lookupRule r a then LT else GT

lookupRule :: Rules -> Int -> [Int]
lookupRule r i = fromMaybe [] $ M.lookup i r

part1 :: (Rules, [[Int]]) -> Int
part1 (rules, candidates) = sum $ map middle $ filter (isSorted rules) candidates

part2 :: (Rules, [[Int]]) -> Int
part2 (rules, candidates) = sum $ map (middle . sortBy (sortRules rules)) (filter (not . isSorted rules) candidates)

tidy :: (Int, Int) -> (String, String)
tidy (a,b) = (show a, show b)
