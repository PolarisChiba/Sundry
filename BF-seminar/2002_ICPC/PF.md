# Toil for Oil

[Link](https://vjudge.net/contest/538106#problem/F)

## Description

Given a simple polygon with $n$ edges.

It is full of water first.

However there are some holes on some edges. Water will spoil over through these holes according to Pascal's law.

Calculate the volume of water left in the polygon.

## Input Format

$3\le n\le 100$

The points of the polygon is given in 2d-coordinate and counterclockwise order.

$x_i, y_i$ integer.

## Output Format

The volume rounded to the nearest integer.

## Solution

Slice the polygon by the y-coordinate of each point.

For each block do dfs to see if it connects to some hole (brute force).

Or use sweep line technique and dsu to maintain if the water in the block will spill over or not.

Either will do. 

By slicing, you'll create a graph with $O(n^2)$ vertices and edges.

The complexity for brute force is $O(n^4)$.

The complexity for sweep line method and dsu is $O(n^2\log{n^2})$ since each block will be process onece.

## AC code

Though the code uses the second method but there is somewhere not optimal. I'll modify it later.

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
#define X first
#define Y second
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

struct Dsu {
	vector<int> fa;
	vector<bool> b;
	Dsu() {}
	Dsu(int n) {
		b.assign(n + 1, false);
		fa.resize(n + 1);
		iota(fa.begin(), fa.end(), 0);
	}
	int find(int x) {
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}
	void unite(int x, int y) {
		x = find(x), y = find(y);
		if (b[x] || b[y]) b[x] = b[y] = true;
		fa[y] = x;
	}
	void setflood(int x) {
		b[find(x)] = true;
	}
	bool isflood(int x) {
		return b[find(x)];
	}
};

typedef pair<double, double> pdd;

int n;
pair<pdd, int> v[109];

double intersect(pdd a, pdd b, double h) {
	return a.X + (h - a.Y) * (b.X - a.X) / (b.Y - a.Y);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int T = 1;
	while (cin >> n && n) {
		vector<double> vy;
		for (int i = 0; i < n; ++ i) {
			cin >> v[i].X.X >> v[i].X.Y >> v[i].Y;
			vy.push_back(v[i].X.Y);
		}

		for (int i = 0; i < n; ++ i) {
			if (v[i].X.Y == v[(i + 1) % n].X.Y && v[i].Y)
				v[(i + 1) % n].Y = true;
		}
		for (int i = n - 1; i >= 0; -- i) {
			if (v[i].X.Y == v[(i + 1) % n].X.Y && v[(i + 1) % n].Y)
				v[i].Y = true;
		}

		sort(vy.begin(), vy.end());
		vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
		int ny = (int)vy.size();

		vector<vector<pair<pdd, int>>> u(ny);
		for (int i = 0; i < n; ++ i) {
			auto a = v[i], b = v[(i + 1) % n];
			if (a.X.Y > b.X.Y) swap(a, b);
			int L = lower_bound(vy.begin(), vy.end(), a.X.Y) - vy.begin();
			int R = lower_bound(vy.begin(), vy.end(), b.X.Y) - vy.begin();

			for (int j = L; j < R; ++ j) {
				double p1 = intersect(a.X, b.X, vy[j]);
				double p2 = intersect(a.X, b.X, vy[j + 1]);
				int res = 0;
				if (a.Y == 1) res = 1;
				else if (b.Y == 1 && vy[j + 1] == b.X.Y) res = 2;
				u[j + 1].push_back(make_pair(pdd(p1, p2), res));
			}
		}

		for (int i = 1; i < ny; ++ i) {
			sort(u[i].begin(), u[i].end(), [](pair<pdd, int> a, pair<pdd, int> b) {
				auto u = a.X, v = b.X;
				if (u.X > u.Y) swap(u.X, u.Y);
				if (v.X > v.Y) swap(v.X, v.Y);
				return u < v;
			});
		}

		vector<int> s(ny);
		for (int i = 1; i < ny; ++ i) s[i] = (int)u[i].size() / 2 + s[i - 1];
		auto id = [&](int i, int j) -> int {
			return s[i - 1] + j / 2;
		};

		Dsu dsu(s[ny - 1]);

		double ans = 0;
		for (int i = 1; i < ny; ++ i) {
			for (int j = 0; j < (int)u[i].size(); j += 2) {
				if (u[i][j].Y == 1 || u[i][j + 1].Y == 1) dsu.setflood(id(i, j));

				for (int k = 0; k < (int)u[i - 1].size(); k += 2) {
					if ((u[i - 1][k + 1].X.Y < u[i][j].X.X) == false && (u[i][j + 1].X.X < u[i - 1][k].X.Y) == false) {
						dsu.unite(id(i, j), id(i - 1, k));
					}
				}
			}
			for (int j = 0; j < (int)u[i].size(); j += 2) {
				if (dsu.isflood(id(i, j)) == false)
					ans += 1.0 * (vy[i] - vy[i - 1]) * (u[i][j + 1].X.X + u[i][j + 1].X.Y - u[i][j].X.X - u[i][j].X.Y);
				// cout << i << " " << j << " " << dsu.isflood(id(i, j)) << "\n";
			}
			for (int j = 0; j < (int)u[i].size(); j += 2) {
				if (u[i][j].Y == 2 || u[i][j + 1].Y == 2)
					dsu.setflood(id(i, j));
			}
		}
		
		cout << "Cave " << T ++ << ": Oil capacity = " << fixed << setprecision(0) << round(ans / 2.0) << "\n\n";
	}
}
```