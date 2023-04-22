# A Spy in the Metro 

[Link](https://vjudge.net/contest/546122#problem/H)

## Description

There are $n$ station on a straight line.

You are at the first station and your goal is to be at the $n$-th stations at specific moment $T$.

There will be $M_1$ trains traveling from first station to the $n$-th one and departuring at $d_i$ moment.

There will be $M_2$ trains traveling from the $n$-th station to the first one departuring at $e_i$ moment.

The time for each station go from $i$-th station to $i+1$ one or vice versa is $t_i$.

You can only move by trains and you spend no time getting on or off the train.

Find the minimum time that you're not moving (that is, waiting) while being at the $n$-th station at $T$ moment or report it's impossible to arrive in time.

## Input Format

$2\le n\le 50$

$0\le T\le 200$

$1\le t_i \le 20$

$1\le M_1\le 50$

$0\le d_i\le 250$ and $d_i < d_{i+1}$

$1\le M_2\le 50$

$0\le e_i\le 250$ and $e_i < e_{i+1}$

## Output Format

Output the minimum time that you're not moving (that is, waiting) while being at the $n$-th station at $T$ moment or report it's impossible to arrive in time.

## Solutioin

### sol 1

Let $(i, j)$ be the minimum waiting time such that you are at $i$-th station at $j$-th moment.

Let these states be vertices. Build edges by trains or waiting.

One can see the weight of the edges is either 1 or 0.

Hence running a 01 BFS algorithm will do.

Complexity: $O(n\times (T + M_1 + M_2))$.

### sol 2

Sol 1 is equivalent to dynamic programming since the graph is clearly DAG.

Complexity: $O(n\times (T + M_1 + M_2))$.

## AC code

### sol 1

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

int n;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int _ = 1;
	while (cin >> n && n) {
		int T, m1, m2;
		cin >> T;
		vector<int> t(n - 1);
		for (auto &i : t) cin >> i;
		cin >> m1;
		vector<int> d(m1);
		for (auto &i : d) cin >> i;
		cin >> m2;
		vector<int> e(m2);
		for (auto &i : e) cin >> i;

		auto id = [&](int i, int j) -> int { // i station, time j
			return i * (T + 1) + j;
		};

		vector<vector<pair<int, int>>> v((T + 1) * n);
		for (int i = 0; i < m1; ++ i) {
			int pre = d[i];
			for (int j = 0; j < n - 1; ++ j) {
				if (pre + t[j] <= T)
					v[id(j, pre)].push_back({id(j + 1, pre + t[j]), 0});
				pre += t[j];
			}
		}
		for (int i = 0; i < m2; ++ i) {
			int pre = e[i];
			for (int j = n - 2; j >= 0; -- j) {
				if (pre + t[j] <= T)
					v[id(j + 1, pre)].push_back({id(j, pre + t[j]), 0});
				pre += t[j];
			}
		}
		for (int i = 0; i <= n - 1; ++ i)
			for (int j = 0; j < T; ++ j)
				v[id(i, j)].push_back({id(i, j + 1), 1});
		
		vector<int> dis((T + 1) * n, 1e9);
		dis[id(0, 0)] = 0;
		deque<int> deq{id(0, 0)};
		while (!deq.empty()) {
			auto p = deq.front();
			deq.pop_front();
			for (auto [a, b] : v[p]) {
				if (dis[a] == 1e9) {
					dis[a] = dis[p] + b;
					if (b == 0) deq.push_front(a);
					else deq.push_back(a);
				}
			}
		}

		int ans = dis[id(n - 1, T)];

		cout << "Case Number " << _ ++ << ": ";
		if (ans == 1e9) cout << "impossible" << endl;
		else cout << ans << endl;
	}
}
```

### sol 2

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

int n;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int _ = 1;
	while (cin >> n && n) {
		int T, m1, m2;
		cin >> T;
		vector<int> t(n - 1);
		for (auto &i : t) cin >> i;
		cin >> m1;
		vector<int> d(m1);
		for (auto &i : d) cin >> i;
		cin >> m2;
		vector<int> e(m2);
		for (auto &i : e) cin >> i;

		auto id = [&](int i, int j) -> int { // i station, time j
			return i * (T + 1) + j;
		};

		vector<vector<pair<int, int>>> v((T + 1) * n);
		for (int i = 0; i < m1; ++ i) {
			int pre = d[i];
			for (int j = 0; j < n - 1; ++ j) {
				if (pre + t[j] <= T)
					v[id(j, pre)].push_back({id(j + 1, pre + t[j]), 0});
				pre += t[j];
			}
		}
		for (int i = 0; i < m2; ++ i) {
			int pre = e[i];
			for (int j = n - 2; j >= 0; -- j) {
				if (pre + t[j] <= T)
					v[id(j + 1, pre)].push_back({id(j, pre + t[j]), 0});
				pre += t[j];
			}
		}
		for (int i = 0; i <= n - 1; ++ i)
			for (int j = 0; j < T; ++ j)
				v[id(i, j)].push_back({id(i, j + 1), 1});
		
		vector<int> dis((T + 1) * n, 1e9);
		dis[id(n - 1, T)] = 0;
		for (int j = T; j >= 0; -- j) {
			for (int i = n - 1; i >= 0; -- i) {
				for (auto [a, b] : v[id(i, j)])
					dis[id(i, j)] = min(dis[id(i, j)], dis[a] + b);
			}
		}
		/*
		dis[id(0, 0)] = 0;
		deque<int> deq{id(0, 0)};
		while (!deq.empty()) {
			auto p = deq.front();
			deq.pop_front();
			for (auto [a, b] : v[p]) {
				if (dis[p] + b < dis[a]) {
					dis[a] = dis[p] + b;
					if (b == 0) deq.push_front(a);
					else deq.push_back(a);
				}
			}
		}
		*/

		int ans = dis[id(0, 0)];

		// if (_ != 1) cout << "\n";
		cout << "Case Number " << _ ++ << ": ";
		if (ans == 1e9) cout << "impossible" << endl;
		else cout << ans << endl;
	}
}
```