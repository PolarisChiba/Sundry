# Light Bulbs

[Link](https://vjudge.net/contest/546122#problem/B)

## Description

There's $n$ bulbs and switches.

Each bulbs is either on or off. You're given the initial state of the bulbs.

$i$-th switch changes the state of the $i-1$-th, $i$-th, $i+1$-th bulbs if there's one (the $1$-the and $n$-th one controls two bulbs only).

Given the final state of the bulbs. Find the minimum number of switches need to be triggered or report it is impossible.

## Input Format

$n\le 100\times\log_2{10}$

## Output Format

Output the minimum number of switches needed to be triggered or report it is impossible.

## Solution

After determing whether to trigger the first switch or not, we can find the answer by simple greedy algorithm. 

Hence we just check the two cases.

Time complexity: $O(n)$.

Actually, the state are encoded to decimal number. We need $O(\log{n})$ to decode it. The same holds for the output.

## AC code

```python3
def calc(s, t):
    v = [0] * len(s)
    # print(s, t)
    for i in range(1, len(s)):
        if s[i - 1] != t[i - 1]:
            v[i] = 1
            for k in range(i - 1, i + 2):
                if k == len(s): break
                s[k] = 1 - s[k]
    # print(s, t, v)
    return ((s == t), v)

def bny(s):
    res = 0
    for i in range(0, len(s)):
        res = res * 2 + s[i]
    return str(res)

T = 1
while True:
    a, b = input().split()
    a = int(a)
    b = int(b)
    if a == 0 and b == 0: break
    if a + b == 1:
        if T != 1: print()
        print("Case Number " + str(T) + ": 1")
        T = T + 1
        continue
    if a == 1 and b == 1:
        if T != 1: print()
        print("Case Number " + str(T) + ": 0")
        T = T + 1
        continue
    s = []
    t = []
    while a:
        s.append(a % 2)
        a = a // 2
    while b:
        t.append(b % 2)
        b = b // 2
    while len(s) < len(t):
        s.append(0)
    while len(t) < len(s):
        t.append(0)

    x = calc(s[:], t[:])
    s[0] = 1 - s[0]
    s[1] = 1 - s[1]
    y = calc(s[:], t[:])
    y[1][0] = 1

    x[1].reverse()
    y[1].reverse()
    
    ans = []
    if T != 1: print()
    if x[0] == False and y[0] == False:
        print("Case Number " + str(T) + ": impossible")
    elif x[0] == False:
        print("Case Number " + str(T) + ": " + bny(y[1]))
    elif y[0] == False:
        print("Case Number " + str(T) + ": " + bny(x[1]))
    elif (sum(x[1]) < sum(y[1])) or (sum(x[1]) == sum(y[1]) and str(x[1]) < str(y[1])):
        print("Case Number " + str(T) + ": " + bny(x[1]))
    else:
        print("Case Number " + str(T) + ": " + bny(y[1]))
    T = T + 1
```