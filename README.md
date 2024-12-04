# AdventOfCode2024
Advent of Code 2024

## --- Day 1: Historian Hysteria ---
That felt quite fiddly for day 1. Working on columns, having to do lookups against sparse data, multiple spaces between the input numbers "41226   69190
" - all things that make it a bit tricky. Unless you're going to cheat, which anyone doing 9 seconds for parts 1 surely is. How much of the leaderboard is ml?

Day 1 code is  [here](AoC/src/Day01.hs)

## --- Day 2: Red-Nosed Reports ---
I was super short on time for this one because I have a train to catch so it's not clever. For part 2, removing one digit from a list effectively makes the list valid, the trick is to decide which one to remove. I just generated all possible strings and checked them all. I'm just fingers crossed that Haskell's Lazy evaluation means it doesn't actually generate all possible strings with missing characters and just does enough to fail the function. Be interesting to profile it and see what it's actually doing.

Day 2 code is  [here](AoC/src/Day02.hs)
## --- Day 3: Mull It Over ---
If I hadn't just gotten out of bed, I'm pretty sure I could have done this entire thing with megaparsec, but I'm not awake enough to remember how it works. With Advent of Code you really don't have time to read the docs, you can only use stuff that's already in your head. Anyhow, sticking a loop around the basic parser worked and it meant I didn't have to stop typing.
Day 3 code is  [here](AoC/src/Day03.hs)

## --- Day 4: Ceres Search ---
I can't think of a really clever way of doing this one, it's just check all the letters. I was expecting part 2 to be some horribe twist but it's just 'do the first part again but different'. I strongly suspect the bit about flipping the xword to read the instructions on the back is there to trip up llm and I bet it trips up a few people as well. 
Day 4 code is  [here](AoC/src/Day04.hs)
