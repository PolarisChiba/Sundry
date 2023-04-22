# Building Bridges 

[Link](https://vjudge.net/contest/546122#problem/A)

## Description

Given $r\times c$ borad. Each grid on this board is either black or white.

You can build edges along straight grid lines. Each edge must connect exactly two black grids.

Two black grid are adjacent if they share at least one common corner or they are directly connected by an edge you build.

The length of the edges is measured in mutiples of the grid size.

Your task is to minimize the sum of lengths of the edges while keeping the disconnected groups of black grids minimum.

## Remark

Two edges may cross, but in this case they are considered to be in different level and don't provide connection to each other.

## Input Format

$1\le r, c\le 100$

## Output Format

The minimum number of disconnected groups and the minimum sum of lengths of edges needed.

## Solution

Turn the board into a graph and it turns out to be a minimum weight forest problem.

Kruskal's algorithm works.

## Time complexity

For each black grids, we need to check four direction to build the candidate edges; however, each grid line will be checked only once since we stop if encountering other black grid. 

Hence, $O(r\times c)$ for building graph.

The graph consists of $O(r\times c)$ vertices and edges.

Kruskal's algorithm works in $O(E\log{E})$ (sorting and dsu).

$O(r\times c)$ for calculating the number of disconnected groups.

$O(r\times c\log{(r\times c)})$ in total.

## AC code

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

struct Dsu {
	vector<int> fa;
	Dsu() {}
	Dsu(int n) {
		fa.assign(n + 1, 0);
		iota(fa.begin(), fa.end(), 0);
	}
	int find(int x) {
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}
	void unite(int x, int y) {
		fa[find(y)] = find(x);
	}
};

int r, c;
string g[101];
int now_id;
int id[101][101];

bool in_range(int x, int y) {
	return 0 <= x && x < r && 0 <= y && y < c;
}

int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int d[3] = {0, 1, -1};
void Dfs(int x, int y) {
	id[x][y] = now_id;
	for (int i = 0; i < 8; ++ i) {
		int tx = x + dx[i], ty = y + dy[i];
		if (in_range(tx, ty) && g[tx][ty] == '#' && id[tx][ty] == 0)
			Dfs(tx, ty);
	}
}

vector<tuple<int, int, int>> v;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T = 1;
	while (cin >> r >> c && r) {
		now_id = 0;
		for (int i = 0; i < r; ++ i)
			fill(id[i], id[i] + c, 0);
		v.clear();

		for (int i = 0; i < r; ++ i) 
			cin >> g[i];

		for (int i = 0; i < r; ++ i) {
			for (int j = 0; j < c; ++ j) {
				if (g[i][j] == '#' && id[i][j] == 0) {
					++ now_id;
					Dfs(i, j);
				}
			}
		}

		for (int i = 0; i < r; ++ i) {
			for (int j = 0; j < c; ++ j) {
				if (g[i][j] == '#') {
					for (int k = 0; k < 3; ++ k) {
						for (int l = i - 1; l >= 0; -- l) {
							if (in_range(l, j + d[k]) && g[l][j + d[k]] == '#') {
								v.push_back({abs(i - l) - 1, id[i][j], id[l][j + d[k]]});
								break;
							}
						}
						for (int l = i + 1; l < r; ++ l) {
							if (in_range(l, j + d[k]) && g[l][j + d[k]] == '#') {
								v.push_back({abs(i - l) - 1, id[i][j], id[l][j + d[k]]});
								break;
							}
						}
						for (int l = j - 1; l >= 0; -- l) {
							if (in_range(i + d[k], l) && g[i + d[k]][l] == '#') {
								v.push_back({abs(j - l) - 1, id[i][j], id[i + d[k]][l]});
								break;
							}
						}
						for (int l = j + 1; l < c; ++ l) {
							if (in_range(i + d[k], l) && g[i + d[k]][l] == '#') {
								v.push_back({abs(j - l) - 1, id[i][j], id[i + d[k]][l]});
								break;
							}
						}
					}
				}
			}
		}
		
		Dsu dsu(now_id);
		int ans = 0, res = 0;
		sort(v.begin(), v.end());
		for (auto [c, a, b] : v) {
			if (dsu.find(a) != dsu.find(b)) {
				dsu.unite(a, b);
				ans += c;
				res += 1;
			}
		}

		if (T != 1) cout << "\n";
		cout << "City " << T ++ << "\n";
		if (now_id <= 1) cout << "No bridges are needed.\n";
		else {
			if (res == 0) cout << "No bridges are possible.\n";
			else {
				if (res == 1) cout << "1 bridge ";
				else cout << res << " bridges ";
				cout << "of total length " << ans << "\n";
			}
			if (res != now_id - 1) {
				cout << now_id - res << " disconnected groups\n";
			}
		}
	}
}
// care one


```