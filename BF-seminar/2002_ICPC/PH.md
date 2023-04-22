# Silly Sort

[Link](https://vjudge.net/contest/538106#problem/H)

## Description

Given an array $a$ with size $n$. Each number is unique.

The cost of swapping two numbers is their sum.

Find the minimum cost to sort the array in acsending order.

## Input Format 

$n > 1$

$1 \le a_i < 1000$

## Output Format

An integer represents the cost to sort $a$.

## Solution

For each number, we build an edge to its correct position.

Then we'll get a graph composed of many cycles.

For any sequence of operations that sorts the array successfully, we call the operation $(a, b)$ critical if it's the last operation that returns $a$ to its correct position while $a>b$ and call $b$ the partner of $a$ ($b$ returns $a$ to its correct position).

One can see the best situation is that the partner of each element is the global minimum number.

However, for each cycle, if each operation involved is critical, then the best way to returns each elements to their correct position is to swap them with the minimum number in the cycle. Hence, the partner of each element is the local minimum number in this case.

On the other hand, if there's any operation involved with the cycle is not critical, then the best situation is there's only one and it is to swap the local minimum number with the global minimum number. One can see after such operation, the partner of each element in this cycle becomes the best one, global minimum number.

Hence, for each cycle, compare the two case and choose the better one, then sum them up and we are done.

As for time complexity, finding each cycle takes $O(n\log{n} + n)$ time and comparing takes $O(n)$ time for all cycles.

Hence $O(n\log{n})$ in total.

Or one can use bucket sort and the time complexity will become $O(n+1000)$.

## AC code

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
#define F first
#define S second
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;
const double pi = acos(-1);

int n;
vector<int> v;
int pos[1009];
bool vis[1009];
vector<vector<int>> z;

void Dfs(int i) {
	vis[i] = true;
	z.back().push_back(v[i]);
	if (!vis[pos[v[i]]]) Dfs(pos[v[i]]);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t = 1;
	while (cin >> n && n) {
		v.resize(n);
		for (auto &i : v) cin >> i;
		fill(vis, vis + n, false);
		
		auto u = v;
		sort(u.begin(), u.end());
		for (int i = 0; i < n; ++ i) pos[u[i]] = i;
		
		z.clear();
		for (int i = 0; i < n; ++ i) if (!vis[i]) {
			z.push_back(vector<int>());
			Dfs(i);
		}
		
		int mn = *min_element(v.begin(), v.end());
		int ans = 0;
		for (auto &i : z) if ((int)i.size() > 1) {
			int x = *min_element(i.begin(), i.end());
			int ret = accumulate(i.begin(), i.end(), 0, plus<int>());
			int l = (int)i.size();
			ans += min(ret + (l - 2) * x, ret + mn + (l - 1) * mn + mn + x);
		}
		
		cout << "Case " << t << ": " << ans << "\n\n";
		t += 1;
	}
}
```