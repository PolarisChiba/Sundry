# Balloons in a Box

[Link](https://vjudge.net/contest/538106#problem/A)

## Description

Given a 3-D rectangular box with $n$ critical points inside.

In any order of the points, you put ballon centered in the point one by one and expand it as big as possible so long as it not touch other ballons or borders of the box.

Your task is to find the minimum possible uncovered area by the ballons in the box.

## Remark

The box has non-zero length in each dimension.

## Input Format

$1\le n\le 6$

points $(x, y, z)$ in integer.

## Output Format

The minimum possible uncovered area rouned to the nearest integer.

## Solution

Use DFS to traverse every permutation of the points.

For each level of the recursion, determine the maximum radius of the current by checking other ballons and the borders in linear time.

## Time complexity

$O(n!)$ for DFS.

$O(n)$ for determing the radius.

$O(n!\times n)$ in total.

## Other solution

Generating every permutation in $O(n!)$ time.

For each permutation, iterate each point in $O(n)$ time and for each of them determing the radius in another $O(n)$ time.

$O(n!\times n^2)$ in total.

## AC Code

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
vector<ll> a, b;
vector<vector<ll>> v;

double ans;
double rad[10];

double dis(vector<ll> a, vector<ll> b) {
	double res = 0;
	for (int i = 0; i < 3; ++ i)
		res += (a[i] - b[i]) * (a[i] - b[i]);
	return sqrtl(res);
}

void Dfs(int cnt) {
	if (cnt == n) {
		double res = 0;
		for (int i = 0; i < n; ++ i)
			if (rad[i] != -1)
				res += rad[i] * rad[i] * rad[i];
		ans = max(ans, res);
		return;
	}
	
	for (int i = 0; i < n; ++ i) {
		if (rad[i] != -1) continue;
		
		bool ok = true;
		for (int j = 0; j < 3; ++ j) {
			if (v[i][j] < a[j] || b[j] < v[i][j])
				ok = false;
		}
		for (int j = 0; j < n; ++ j) {
			if (rad[j] == -1) continue;
			if (dis(v[i], v[j]) <= rad[j])
				ok = false;
		}
		
		if (ok == false) continue;
		double mn = MOD * MOD;
		for (int j = 0; j < 3; ++ j) {
			mn = min(mn, 1.0 * v[i][j] - a[j]);
			mn = min(mn, 1.0 * b[j] - v[i][j]);
		}
		for (int j = 0; j < n; ++ j) {
			if (rad[j] == -1) continue;
			mn = min(mn, dis(v[i], v[j]) - rad[j]);
		}
		
		rad[i] = mn;
		Dfs(cnt + 1);
		rad[i] = -1;
	}
	Dfs(cnt + 1);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	a.resize(3);
	b.resize(3);
	
	int t = 1;
	while (cin >> n && n) {
		for (int i = 0; i < 3; ++ i) cin >> a[i];
		for (int i = 0; i < 3; ++ i) cin >> b[i];
		for (int i = 0; i < 3; ++ i) if (a[i] > b[i]) swap(a[i], b[i]);
		
		v = vector<vector<ll>>(n, vector<ll>(3, 0));
		for (auto &i : v) for (auto &j : i) cin >> j;
		
		ans = 0;
		fill(rad, rad + n, -1);
		Dfs(0);
		
		double ret = 1;
		for (int i = 0; i < 3; ++ i) ret *= b[i] - a[i];
		ret -= 4.0 * ans * pi / 3.0;
		
		cout << "Box " << t << ": " ;
		cout << fixed << setprecision(0) << ret << "\n\n";
		t += 1;
	}
}
```