#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef long long ll;
const ll MOD = 1000000007LL;

vector<int> judges;
vector<vector<int>> path;
vector<int> z;
vector<vector<int>> s;

void Dfs(int u, int f) {
	z.push_back(u);
	path[u] = z;
	reverse(path[u].begin(), path[u].end());
	for (auto i : s[u]) if (i != f) Dfs(i, u);
	z.pop_back();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T = 1;
	int n;
	while (cin >> n && ~n) {
		int ed, m;
		cin >> ed >> m;
		ed -= 1;
		vector<vector<int>> v(n, vector<int>(n, MOD));
		for (int i = 0; i < n; ++ i)
			v[i][i] = 0;
		for (int i = 0; i < m; ++ i) {
			int a, b, c;
			cin >> a >> b >> c;
			-- a, -- b;
			v[a][b] = min(v[a][b], c);
			v[b][a] = min(v[b][a], c);
		}
		int j, q;
		cin >> j;
		judges.clear();
		while ( j -- ) {
			int x;
			cin >> x;
			q ^= (1 << (x - 1));
			judges.push_back(x - 1);
		}

		vector<vector<int>> h(n, vector<int>((1 << n), -1));
		for (int i = 0; i < n; ++ i) {
			for (int j = 1; j < (1 << n); ++ j) {
				int b = __lg((j & -j));
				if (h[i][j ^ (1 << b)] == -1 || v[i][b] < v[i][h[i][j ^ (1 << b)]]) {
					h[i][j] = b;
				} else {
					h[i][j] = h[i][j ^ (1 << b)];
				}
			}
		}

		vector<int> f((1 << n), MOD);
		f[0] = 0;
		for (int i = 1; i < (1 << n); ++ i) {
			for (int j = 0; j < n; ++ j) {
				if (((i >> j) & 1) == 0)
					continue;
				if (i == (1 << j)) {
					f[i] = 0;
					continue;
				}
				f[i] = min(f[i], f[i ^ (1 << j)] + v[j][h[j][i ^ (1 << j)]]);
			}
		}

		int ans = (1 << n) - 1;
		for (int i = 0; i < (1 << n); ++ i) {
			if ((i & q) == q) {
				if (f[i] < f[ans]) {
					ans = i;
				} else if (f[i] == f[ans] || __builtin_popcount(i) < __builtin_popcount(ans)) {
					ans = i;
				}
			}
		}

		int sum = f[ans];
		s.assign(n, vector<int>(0));
		while (__builtin_popcount(ans) > 1) {
			for (int i = 0; i < n; ++ i) {
				if (((ans >> i) & 1) == 0)
					continue;
				if (f[ans] == f[ans ^ (1 << i)] + v[i][h[i][ans ^ (1 << i)]]) {
					ans ^= (1 << i);
					s[i].push_back(h[i][ans]);
					s[h[i][ans]].push_back(i);
					break;
				}
			}
		}

		z.clear();
		path.assign(n, vector<int>(0));
		Dfs(ed, ed);

		cout << "Case " << T ++ << ": distance = " << sum << "\n";
		for (auto i : judges) {
			cout << "   ";
			for (auto j : path[i]) {
				cout << j + 1;
				if (j != ed)
					cout << "-";
			}
			cout << "\n";
		}
		cout << "\n";
	}
}