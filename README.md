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

## --- Day 5: Print Queue ---
I spent quite a long time puzzling over how to do this. I suspected you'd have to repair the broken sequences for part2 so I wrote that first and then used it to do part1.  I used sortBy with a custom comparator that used the ordering rules. Then sorted every sequence, everything that was unchanged by the sort operation was in part1.

Day 5 code is  [here](AoC/src/Day05.hs)

## --- Day 6: Guard Gallivant ---
Grids that need updating are a pain to do quickly in haskell, as is anything that involves moving around in an unpredictable way, like a security guard walking around a puzzle. You can do it and it's bomb proof when you do, but you need to spend a good amount of time thinking really hard about it, which is not easy early in the morning and not really compatible with AoC's "do it really fast" thing. So I just used C. I can do anything in C, super fast, and it'll always work for my one test case. It's super dangerous and would explode in production, but I have to remember this is AoC and sometimes C is the right tool for the job.

Day 6 code is  [here](AoC/src/day06.c)

## --- Day 7: Bridge Repair ---
This one was pretty easy. Just throw it at haskell and let the lazy evaluation deal with it. I might do this in C just to compare.

Day 7 code is  [here](AoC/src/Day07.hs)

## --- Day 8: Resonant Collinearity ---
I did this one in c++ (So I could use Map). I do feel slightly sad about that, a haskell solution would have been more robust, but that's just not the goal here. I can't decide whether I suck at haskell or whether it's just really clunky to deal with grids and maps. If this thing is on next year, I'm going to make a new language for it.

Day 8 code is  [here](AoC/src/day08.cpp)

## --- Day 9: Disk Fragmenter ---
Another easy one today. Rather than try to do anything fast with lists of tuples in haskell I used C (despite the file extension) and just inflated the disk image and then actually defragged it. If I still had spare time in my life, this would really benefit from a dos style defrag visualization.

Day 9 code is  [here](AoC/src/day09.cpp)

## --- Day 10: Hoof It ---
Well that was just confusing. I never actually got to a point where I understood the question, I just guessed what seemed likely for part2 and did that.

Day 10 code is  [here](AoC/src/day10.c)

## --- Day 11: Plutonian Pebbles ---
This was obviously going to be another part2 is a huge number one, so I used python which gave me access to functools cache, which is magic. Feels like cheating.

Day 11 code is  [here](AoC/src/day11.py)

## --- Day 12: Garden Groups ---
Another cpp entry. Floodfill over a garden to find the size of different areas and then two ways of counting the perimeter. For part2 I found an edge and then counted left and right (or up and down) to find the ends of that edge, that was messy and took ages so I'm rewriting it to pattern match corners instead. I nearly ran out of time on this one. I only have about 20 minutes to get this stuff finished and I get interrupted a lot.

Day 12 code is  [here](AoC/src/day12.cpp)

## --- Day 13: Claw Contraption ---
Deployed megaparsec, which was nice. I'd almost forgotten how to use it! Part1 and Part2 are the same because again, it was fairly obvious that part2 was just going to be a big O check on part1. Remembering how megaparsec worked took a while and I am really running short on time now. I suspect the problems will stop fitting into my morning by next week. 

Day 13 code is  [here](AoC/src/Day13.hs)
