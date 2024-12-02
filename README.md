# AdventOfCode2024
Advent of Code 2024

## --- Day 1: Historian Hysteria ---
That felt quite fiddly for day 1. Working on columns, having to do lookups against sparse data, multiple spaces between the input numbers "41226   69190
" - all things that make it a bit tricky. Unless you're going to cheat, which anyone doing 9 seconds for parts 1 surely is. How much of the leaderboard is ml?

Day 1 code is  [here](AoC/src/Day01.hs)

## --- Day 2: Red-Nosed Reports ---
I was super short on time for this one because I have a train to catch so it's not clever. For part 2, removing one digit from a list effectively makes the list valid, the trick is to decide which one to remove. I just generated all possible strings and checked them all. I'm just fingers crossed that Haskell's Lazy evaluation means it doesn't actually generate all possible strings with missing characters and just does enough to fail the function. Be interesting to profile it and see what it's actually doing.

Day 2 code is  [here](AoC/src/Day02.hs)
