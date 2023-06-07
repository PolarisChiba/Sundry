#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef long long ll;
const ll MOD = 1000000007LL;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T = 1;
	int n;
	while (cin >> n && n) {
		vector<int> vx, vy;
		vector<tuple<int, int, int, int>> v(n);
		for (auto &[x1, y1, x2, y2] : v) {
			cin >> x1 >> y1 >> x2 >> y2;
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);
			vx.push_back(x1);
			vx.push_back(x2);
			vy.push_back(y1);
			vy.push_back(y2);
		}
		pair<int, int> st, ed;
		cin >> st.first >> st.second >> ed.first >> ed.second;
		vx.push_back(st.first);
		vx.push_back(ed.first);
		vy.push_back(st.second);
		vy.push_back(ed.second);

		sort(vx.begin(), vx.end());
		vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
		sort(vy.begin(), vy.end());
		vy.resize(unique(vy.begin(), vy.end()) - vy.begin());

		auto idx = [&](int x) -> int {
			return 2 * (lower_bound(vx.begin(), vx.end(), x) - vx.begin()) + 1;
		};
		auto idy = [&](int y) -> int {
			return 2 * (lower_bound(vy.begin(), vy.end(), y) - vy.begin()) + 1;
		};

		for (auto &[x1, y1, x2, y2] : v) {
			x1 = idx(x1);
			y1 = idy(y1);
			x2 = idx(x2);
			y2 = idy(y2);
		}
		st.first = idx(st.first);
		ed.first = idx(ed.first);
		st.second = idy(st.second);
		ed.second = idy(ed.second);

		int nx = (int)vx.size() * 2 + 1;
		int ny = (int)vy.size() * 2 + 1;

		vector<vector<int>> g(nx, vector<int>(ny, 0));
		for (auto &[x1, y1, x2, y2] : v) {
			for (int i = x1; i <= x2; ++ i)
				g[i][y1] = g[i][y2] = -1;
			for (int i = y1; i <= y2; ++ i)
				g[x1][i] = g[x2][i] = -1;
		}

		int dx[4] = {0, 1, 0, -1};
		int dy[4] = {1, 0, -1, 0};
		auto in_range = [&](int x, int y) -> bool {
			return 0 <= x && x < nx && 0 <= y && y < ny;
		};
		int now = 1;
		function<void(int, int)> Dfs = [&](int x, int y) -> void {
			g[x][y] = now;
			for (int i = 0; i < 4; ++ i) {
				int tx = x + dx[i];
				int ty = y + dy[i];
				if (in_range(tx, ty) && g[tx][ty] == 0)
					Dfs(tx, ty);
			}
		};
		for (int i = 0; i < nx; ++ i) {
			for (int j = 0; j < ny; ++ j) {
				if (g[i][j] == 0) {
					Dfs(i, j);
					now += 1;
				}
			}
		}

		vector<set<int>> u(now);
		for (int i = 0; i < nx; ++ i) {
			for (int j = 0; j < ny; ++ j) {
				if (g[i][j] == -1)
					continue;
				for (int k = 0; k < 4; ++ k) {
					int x = i + dx[k] * 2;
					int y = j + dy[k] * 2;
					if (in_range(x, y) && g[x][y] != -1 && g[x][y] != g[i][j]) {
						u[g[i][j]].insert(g[x][y]);
					}
				}
			}
		}

		queue<int> q;
		vector<int> dis(now, MOD);
		dis[g[st.first][st.second]] = 0;
		q.push(g[st.first][st.second]);
		while (!q.empty()) {
			int p = q.front();
			q.pop();
			for (auto i : u[p]) {
				if (dis[i] == MOD) {
					dis[i] = dis[p] + 1;
					q.push(i);
				}
			}
		}

		cout << "City " << T ++ << "\n";
		cout << "Peter has to cross " << dis[g[ed.first][ed.second]] << " streets\n";
	}
}