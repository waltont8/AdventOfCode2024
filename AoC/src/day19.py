import sys
from functools import cache

input = sys.stdin.read().strip().split('\n')

towels = input[0].split(', ')
patterns = input[2:]

@cache
def part1(s):
    if s == "":
        return 1

    count = 0
    for t in towels:
        if s.startswith(t):
            count += part1(s[len(t):])
    return count

ans1 = 0
ans2 = 0

for s in patterns:
    p = part1(s)
    if p != 0:
        ans1 = ans1 + 1
    ans2 = ans2 + p

print(ans1)
print(ans2)
