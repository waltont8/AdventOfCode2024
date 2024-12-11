from functools import cache

input = (510613,358,84,40702,4373582,2,0,1584)

@cache
def rule(num):
    if num == 0:
        return (1,)

    numstr = str(num)
    l = len(numstr)
    if l % 2 == 0:
        h = l//2
        return (int(numstr[:h]),
            int(numstr[h:]))
        
    return (num * 2024,)

@cache
def part1(input, n):

    if n == 0:
        return len(input)

    return sum(part1(rule(i), n - 1) for i in input)

print(part1(input, 25))
print(part1(input, 75))
