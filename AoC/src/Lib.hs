module Lib
    ( advent
    ) where

import Lazy
import Day01
import Day02
import Day03
import Day04
import Day05
import Day06
import Day07
import Day08
import Day09
import Day10
import Day11
import Day12
import Day13
import Day14
import Day15
import Day16
import Day17
import Day18
import Day19
import Day20
import Day21
import Day22
import Day23
import Day24
import Day25

getDay :: Int -> (String -> (String,String))
getDay  1 = day01
getDay  2 = day02
getDay  3 = day03
getDay  4 = day04
getDay  5 = day05
getDay  6 = day06
getDay  7 = day07
getDay  8 = day08
getDay  9 = day09
getDay 10 = day10
getDay 11 = day11
getDay 12 = day12
getDay 13 = day13
getDay 14 = day14
getDay 15 = day15
getDay 16 = day16
getDay 17 = day17
getDay 18 = day18
getDay 19 = day19
getDay 20 = day20
getDay 21 = day21
getDay 22 = day22
getDay 23 = day23
getDay 24 = day24
getDay 25 = day25

getDay _ = day01

advent :: IO ()
advent = do
           args <- getArgs
           input <- readFile ("Inputs/input_" ++ head args ++ ".txt")
           mapM_ (print . run input) [read (head args)]


run :: String -> Int -> (String, String)
run s day = (pt1, pt2)
    where
        (pt1,pt2) = (getDay day) s
