module Day04
    ( day04
    ) where

import Lazy

type Xword = (Int, Int, String)

day04 :: String -> (String, String)
day04 = lines >>> parse >>> part1 &&& part2 >>> tidy

parse :: [String] -> Xword
parse s = (length (head s) , length s, flatten s)

part1 :: Xword -> Int
part1 xw@(w,h,s) = sum $ map (findXmas xw) ac
    where
        ac = [(x,y) | x <- [0..w], y <- [0..h]]

part2 :: Xword -> Int
part2 xw@(w,h,s) = sum $ map (findXmas2 xw) ac
    where
        ac = [(x,y) | x <- [0..w], y <- [0..h]]

tidy :: (Int, Int) -> (String, String)
tidy (a,b) = (show a, show b)

findXmas :: Xword -> (Int,Int) -> Int
findXmas xw@(w,h,s) (x,y) = sum [fup(x,y,xw),fdown(x,y,xw),fleft(x,y,xw),fright(x,y,xw),fupright(x,y,xw),fdownright(x,y,xw),fdownleft(x,y,xw),fupleft(x,y,xw)]

fup (x,y,xw) = if p(xw,x,y) == 'X' && p(xw,x,y-1) == 'M' && p(xw,x,y-2) == 'A' && p(xw,x,y-3) == 'S' then 1 else 0
fdown (x,y,xw) = if p(xw,x,y) == 'X' && p(xw,x,y+1) == 'M' && p(xw,x,y+2) == 'A' && p(xw,x,y+3) == 'S' then 1 else 0
fleft (x,y,xw) = if p(xw,x,y) == 'X' && p(xw,x-1,y) == 'M' && p(xw,x-2,y) == 'A' && p(xw,x-3,y) == 'S' then 1 else 0
fright (x,y,xw) = if p(xw,x,y) == 'X' && p(xw,x+1,y) == 'M' && p(xw,x+2,y) == 'A' && p(xw,x+3,y) == 'S' then 1 else 0
fupright (x,y,xw) = if p(xw,x,y) == 'X' && p(xw,x+1,y-1) == 'M' && p(xw,x+2,y-2) == 'A' && p(xw,x+3,y-3) == 'S' then 1 else 0
fdownright (x,y,xw) = if p(xw,x,y) == 'X' && p(xw,x+1,y+1) == 'M' && p(xw,x+2,y+2) == 'A' && p(xw,x+3,y+3) == 'S' then 1 else 0
fdownleft (x,y,xw) = if p(xw,x,y) == 'X' && p(xw,x-1,y+1) == 'M' && p(xw,x-2,y+2) == 'A' && p(xw,x-3,y+3) == 'S' then 1 else 0
fupleft (x,y,xw) = if p(xw,x,y) == 'X' && p(xw,x-1,y-1) == 'M' && p(xw,x-2,y-2) == 'A' && p(xw,x-3,y-3) == 'S' then 1 else 0

findXmas2 :: Xword -> (Int,Int) -> Int
findXmas2 xw (x,y) = if r then 1 else 0
    where
        r = p(xw,x,y) == 'A' && 
         (  (p(xw,x-1,y-1) == 'M' && p(xw,x+1,y+1) == 'S' && p(xw,x+1,y-1) == 'M' && p(xw,x-1,y+1) == 'S')
             || (p(xw,x-1,y-1) == 'M' && p(xw,x+1,y+1) == 'S' && p(xw,x+1,y-1) == 'S' && p(xw,x-1,y+1) == 'M')
             || (p(xw,x-1,y-1) == 'S' && p(xw,x+1,y+1) == 'M' && p(xw,x+1,y-1) == 'M' && p(xw,x-1,y+1) == 'S')
             || (p(xw,x-1,y-1) == 'S' && p(xw,x+1,y+1) == 'M' && p(xw,x+1,y-1) == 'S' && p(xw,x-1,y+1) == 'M')
         )

p ((w,h,s),x,y) = if (x <w) && (x>=0) && (y >=0 ) && (y<h) then s!!(y*w+x) else '!'