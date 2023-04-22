# Crossing the Desert 

[Link](https://vjudge.net/contest/538106#problem/C)

## Description

There's a desert with $n$ oases.

You are now at the first oase and you want to got the the $n$-th oase.

However, it takes you one unit of food and one unit of water to walk one unit of distance ( the consuming is continuous ).

You have a bag with $C$ units of capacity. One unit of water or food take the same space.

There's a store in the first oase. You can buy food there.

On the other hand, you can get unlimited water in every oases as long as it doesn't exceed the capacity of your bag.

You can get nothing elsewhere.

It's allowed to go to some oase, store some food there, go back to first oase and go on the next trip.

Your task is to find the minimum units of food needed to reach $n$-th oase.

## Remark

If you can reach the goal, it's guaranteed the food needed is less then one million.

## Input Format

$2\le n\le 20$

The coordinates of the oases are givin in integer.

## Output Format

If it's possible to reach the goal, print the minimum food needed in integer.

Otherwise, report impossible.

## Solution (?)

For each oase, we calculate the minimum food needed to get to the $n$-th oase from this oase.

Do the dijkstra dp backwards.

If we want to use $u$ to relax $v$, just calculate how much food is needed such that after we take them from $v$ to $u$, there will be $dp[u]$ ( the answer for $u$ ) left.

However, there may be the case such that we want to transfer food from $a$ to $b$, but the best rount is $a\rightarrow c\rightarrow b$ and then come back to $a$ directly from $b$.

Hence, I can't show the correctness of these solution while it passes the test.

## Time complexity

Dijkstra $O(V^2)=O(n^2)$.

## AC code (?)

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
double w;
pair<int, int> v[20];
double f[20];
double d[20][20];
bool vis[20];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t = 1;
	while (cin >> n >> w && n) {
		for (int i = 0; i < n; ++ i) cin >> v[i].F >> v[i].S;
		
		for (int i = 0; i < n; ++ i) {
			for (int j = i + 1; j < n; ++ j)
				d[i][j] = d[j][i] = sqrt((v[i].F - v[j].F) * (v[i].F - v[j].F) + (v[i].S - v[j].S) * (v[i].S - v[j].S));
		}
		
		fill(f, f + n, MOD);
		fill(vis, vis + n, false);
		f[n - 1] = 0;
		
		for (int _ = 0; _ < n; ++ _) {
			int mn = -1;
			for (int i = 0; i < n; ++ i) {
				if (vis[i] == false && (mn == -1 || f[i] < f[mn]))
					mn = i;
			}
			vis[mn] = true;
			
			for (int i = 0; i < n; ++ i) if (vis[i] == false) {
				if (f[mn] <= w - d[i][mn] * 2) {
					f[i] = min(f[i], f[mn] + d[i][mn]);
				} else if (d[i][mn] * 3 < w) {
					double tmp = f[mn] - (w - d[i][mn] * 2);
					double buf = ceil(tmp / (w - 3 * d[i][mn])) * 2 * d[i][mn];
					f[i] = min(f[i], f[mn] + buf + d[i][mn]);
				}
			}
		}
		
		cout << "Trial " << t << ": ";
		t += 1;
		
		if (f[0] > 1000000) cout << "Impossible\n\n";
		else cout << ceil(f[0]) << " units of food\n\n";
	}
}
```