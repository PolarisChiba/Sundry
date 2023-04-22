# Undecodable Codes

[Link](https://vjudge.net/contest/538106#problem/B)

## Description

Given $m$ 0-1 strings.

Your task is to find the least lexicographical string under the condition that its length is minimum such that it has two different partition composed of given strings.

## Remark

It's guaranteed the answer exists.

## Input Format

$1\le m\le 20$

$1\le \text{size of each string}\le 20$

## Output Format

The satified string.

## Example

$n = 5$

$S_1 = 0110$

$S_2 = 00$

$S_3 = 111$

$S_4 = 001100$

$S_5 = 110$

Ans: $001100110$ ($S4+S5=S2+S_5+S_1$)

## Solution

We first see how to construct the answer of the example.

Let the two partitions be $A$ and $B$. They are empty initially.

We start from $S_2$, so we put $S_2$ to $B$.

* $\emptyset$
* $S_2 = 00$

---

Put $S_4$ to $A$.

* $S_4=001100$
* $S_2=00$

However, the common prefix $00$ is no longer needed to be considered. Just ignore it.

We use "suffix $x$ of $S_i$  to be the suffix of $S_i$ with size $x$.

* $\text{Suffix 4 of } S_4 = 1100$
* $\emptyset$

---

Put $S_5$ to $B$.

* $\text{Suffix 4 of } S_4 = 1100$
* $S_5=110$

Remove the common prefix.

* $\text{Suffix 1 of } S_4 = 0$
* $\emptyset$

---

Put $S_1$ to $B$.

* $\text{Suffix 1 of } S_4 = 0$
* $S_1 = 0110$

Remove the common prefix.

* $\emptyset$
* $\text{Suffix 3 of } S_1 = 110$

---

Put $S_5$ to $A$.

* $S_5 = 110$
* $\text{Suffix 3 of } S_1 = 110$

Remove the common prefix.

* $\emptyset$
* $\emptyset$

Now we are done.

One can see after ignoring the common prefix, there will be at least one partition be empty.

If there's some suffix in one partition, we put some given string into another partition and remove the common prefix, finally we get another suffix in one of the partition (or empty set) and leave another empty.

Hence, we can see each suffix as vertex.

Puting some given string into another partition and removing the common prefix can be considered to be a directed edge (from one suffix to another suffix).

Be cautious of the case that we can't put $S_i$ into one partition while the suffix in another one is $S_i$ itself. We have to avoid this case while building the edges.

For convenience, we build a source node linking to nodes which represents given strings.

Hence, any path from source to empty set will be a valid answer to the problem.

As for optimal answer, we just add proper length to each edge and run a shortest path algorithm.

We can define the "shortest" to be the minimum distance or the least lexicographical order while the distance is the same. Hence a proper compare function is needed.

## Time complexity

For each suffix of given strings ($O(nl)$), we have to iterate each given string ($O(n)$) to bulid the edge (checking $O(l)$) while we use $i\times 20 + j$ to label the vertices ($O(1)$ to get the vertex number).

That is, $(n^2 l^2)$ for preprocessing.

The graph contains $O(nl)$ nodes and $O(n^2 l)$ edges.

The compare function of the heap used in Dijkstra takes $O(nl)$ time.

Dijkstra takes $O(nl\times (V+E)\log{E})=O(n^3l^2\log{n^2 l})$。(or $O(n^3l^2\log{nl})$ if process properly.)

Total complexity is $O(n^3 l^2\log{nl})$。

## AC code

```cpp
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
#define F first
#define S second
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

int n;
string v[21];
int s[21];
vector<pair<int, string>> g[420];
string d[420];

bool Check(int i, int j, int k) {
	int a = (int)v[i].size(), b = (int)v[k].size();
	for (int l = 0; l < min(a - j, b); ++ l) {
		if (v[i][j + l] != v[k][l])
			return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t = 1;
	while (cin >> n && n) {
		for (int i = 1; i <= n; ++ i) cin >> v[i];
		for (int i = 1; i <= n; ++ i) s[i] = (int)v[i].size() + s[i - 1];
		for (int i = 0; i <= s[n] + 1; ++ i) g[i].clear();
		
		for (int i = 1; i <= n; ++ i) g[s[n]].push_back({s[i - 1] + 0, v[i]});
		for (int i = 1; i <= n; ++ i) {
			for (int j = 0; j < (int)v[i].size(); ++ j) {
				for (int k = 1; k <= n; ++ k) {
					if (i == k && j == 0) continue;
					if (Check(i, j, k)) {
						int a = (int)v[i].size(), b = (int)v[k].size();
						
						if (a - j == b) {
							g[s[i - 1] + j].push_back({s[n] + 1, ""});
						} else if (a - j < b) {
							string res = v[k].substr(a - j, b - (a - j));
							g[s[i - 1] + j].push_back({s[k - 1] + a - j, res});
						} else {
							g[s[i - 1] + j].push_back({s[i - 1] + j + b, ""});
						}
					}
				}
			}
		}
		
		fill(d, d + s[n] + 2, "2");
		d[s[n]] = "";
		auto cmp = [](pair<string, int> a, pair<string, int> b) {
			return (a.F.size() < b.F.size()) || (a.F.size() == b.F.size() && a.F < b.F);
		};
		priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);
		pq.push({d[s[n]], s[n]});
		
		while (!pq.empty()) {
			auto [a, b] = pq.top();
			pq.pop();
			if (d[b] != a) continue;
			
			for (auto &[x, y] : g[b]) {
				string res = a + y;
				if (d[x] == "2" || res.size() < d[x].size() || (res.size() == d[x].size() && res < d[x])) {
					d[x] = res;
					pq.push({d[x], x});
				}
			}
		}
		
		cout << "Code " << t << ": " << (int)d[s[n] + 1].size() << " bits\n";
		for (int i = 0; i < (int)d[s[n] + 1].size(); ++ i) {
			cout << d[s[n] + 1][i];
			if ((i + 1) % 20 == 0 || i == (int)d[s[n] + 1].size() - 1)
				cout << "\n";
		}
		cout << "\n";
		
		t += 1;
	}
}
```