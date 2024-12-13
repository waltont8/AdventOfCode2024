module Day13
    ( day13
    ) where

import Lazy

import Text.Megaparsec
import Text.Megaparsec.Char
import Text.Megaparsec.Char.Lexer

import Data.List
import Data.Either
import Data.Void
type Parser = Parsec Void String

data Machine = Machine
  { ax :: Int
  ,  ay :: Int
  ,  bx :: Int
  ,  by :: Int
  ,  px :: Int
  ,  py :: Int
  } deriving Show

-- Parse
parseMachine :: Parser Machine
parseMachine = do
    ax <- string "Button A: X+" *> decimal
    ay <- string ", Y+" *> decimal <* space1
    bx <- string "Button B: X+" *> decimal
    by <- string ", Y+" *> decimal <* space1
    px <- string "Prize: X=" *> decimal
    py <- string ", Y=" *> decimal
    return Machine
      {   ax = ax
      ,   ay = ay
      ,   bx = bx
      ,   by = by
      ,   px = px
      ,   py = py
      }

parseMachines :: Parser [Machine]
parseMachines = sepEndBy1 parseMachine space1

day13 :: String -> (String, String)
day13 = parse' >>> part1 &&& part2 >>> tidy

parse' :: String -> [Machine]
parse' s = case parse parseMachines "" s of
         Left bundle -> trace (errorBundlePretty bundle) $ []
         Right xs -> xs

part1 :: [Machine] -> Int
part1 m = foldl (\t (a,b) -> t+(a*3+b*1)) 0 wins
    where
        wins = map (canWin 0) m


part2 :: [Machine] -> Int
part2 m = foldl (\t (a,b) -> t+(a*3+b*1)) 0 wins
    where
        wins = map (canWin 10000000000000) m 

tidy :: (Int, Int) -> (String, String)
tidy (a,b) = (show a, show b)

canWin :: Int -> Machine -> (Int,Int)
canWin p (Machine ax ay bx by px py) = if af == fromIntegral ai && bf == fromIntegral bi then (ai, bi) else (0,0)
    where
        axf = (fromIntegral ax) :: Double
        ayf = (fromIntegral ay) :: Double
        bxf = (fromIntegral bx) :: Double
        byf = (fromIntegral by) :: Double
        pxf = (fromIntegral (px + p)) :: Double
        pyf = (fromIntegral (py + p)) :: Double
        af = (byf * pxf - bxf * pyf) / (byf * axf - bxf * ayf)  :: Double
        bf = (pxf - axf * af) / bxf
        ai = round af :: Int
        bi = round bf :: Int