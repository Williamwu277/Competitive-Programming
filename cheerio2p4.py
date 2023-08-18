import sys
import math

a, b, c, d = map(int, sys.stdin.readline().split())
assert(a <= 1e12 and b <= 1e12)

gcdd = math.gcd(a-b, c-d)
ans = []
for i in range(1, int(math.sqrt(gcdd))+1):
    if gcdd % i == 0:
        if gcdd / i == i:
            ans.append(i)
        else:
            ans.append(gcdd / i)
            ans.append(i)
ans = sorted([int(i) for i in ans if i > max(b, d)])
for nxt in ans:
    print(nxt)

# https://dmoj.ca/problem/cheerio2p4