module Day03
    ( day03
    ) where

import Text.Megaparsec
import Text.Megaparsec.Char
import qualified Text.Megaparsec.Char.Lexer as L
import Control.Monad.State
import Data.Either
import Data.Void
import Lazy

type Parser = Parsec Void String


type Mul = (Int, Int)

mulParser :: Parser Mul
mulParser = do
    void (string "mul(")
    l <- L.decimal
    void (string ",")
    r <- L.decimal
    void (string ")")
    return (l,r)

day03 :: String -> (String, String)
day03 s = (show $ doMuls s, show $ doMuls2 True s)
    where
        (l,r) = p s

doMuls s@(h:xs) = (l*r) + doMuls xs
    where
        (l,r) = p s
doMuls [] = 0


doMuls2 _ ('d':'o':'(':')':xs) = doMuls2 True xs
doMuls2 _ ('d':'o':'n':'\'':'t':'(':')':xs) = doMuls2 False xs
doMuls2 b s@(h:xs) = (if b then l*r else 0) + doMuls2 b xs
    where
        (l,r) = p s
doMuls2 _ [] = 0

p s = fromRight (0,0) $ runParser mulParser "" s
