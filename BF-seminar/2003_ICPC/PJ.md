# Toll 

[Link](https://vjudge.net/contest/546122#problem/J)

## Description

Given a graph with $n$ vertices. Vertices are of two kinds, town or village.

Your goal is to transport $p$ items from $s$ to $t$.

However, whenever entering a town, you have to pay one item.

Whenever entering a village, if the number of items you have is $n$, you have to pay $\lceil\frac{n}{20}\rceil$ items.

On the other hand, you pay nothing whenever leaving a town or village.

Find the least number of items you have to carry at $s$ so that there's still $p$ items left when you reach $t$.

## Input Format

Number of towns $\le 26$

Number of village $\le 26$

$0 < p\le 1000$

## Output Format

An integer representing the least number of items you have to carry at $s$.

## Solution

For each vertex $x$, we calculate the least number of items required so that we reach $t$ with $p$ items. Let it be $d(x)$.

The number of items needed for $t$ itself is $p$ clearly.

Then we can do dijkstra from $t$ to get the answer for other vertices.

### Time complexity

Building the graph takes $O(n)$ time.

Dijkstra takse $O(V^2 + E)$ time.

$V\le 52$、$E = n$

Hence the total complexity is $O(52^2 + n)$.

## AC code

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

int main() {
	int n, T = 0;
	while (cin >> n && ~n) {
		auto Trans = [](char a) -> int {
			if ('a' <= a && a <= 'z') return a - 'a';
			else return a - 'A' + 26;
		};

		vector<vector<int>> v(52);
		for (int i = 0; i < n; ++ i) {
			char a, b;
			cin >> a >> b;
			v[Trans(a)].push_back(Trans(b));
			v[Trans(b)].push_back(Trans(a));
		}
		int p;
		char s, t;
		cin >> p >> s >> t;
		
		vector<int> d(52, MOD);
		vector<bool> vis(52, false);
		d[Trans(t)] = p;
		for (int _ = 0; _ < 52; ++ _) {
			int mn = -1;
			for (int i = 0; i < 52; ++ i)
				if (vis[i] == false && (mn == -1 || d[i] < d[mn]))
					mn = i;
			
			if (mn == -1) break;
			vis[mn] = true;

			for (auto i : v[mn]) {
				if (mn < 26) {
					d[i] = min(d[i], d[mn] + 1);
				} else {
					if (d[mn] % 19 == 0) d[i] = min(d[i], d[mn] / 19 * 20);
					d[i] = min(d[i], d[mn] / 19 * 20 + d[mn] % 19 + 1);
				}
			}
		}

		cout << "Case " << ++ T << ": " << d[Trans(s)] << "\n";
	}
}
```