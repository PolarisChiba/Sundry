#include<bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

struct Dsu {
	vector<int> fa;
	Dsu(int n) {
		fa.resize(n + 1);
		iota(fa.begin(), fa.end(), 0);
	}
	int find(int x) {
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}
	void unite(int x, int y) {
		fa[find(y)] = find(x);
	}
};

int n, m;
vector<int> v[200009];
int p[200009];
int sur[200009];
bool chk[200009];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= n; ++ i)
		cin >> p[i];
	for (int i = 1; i <= m; ++ i) {
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}

	Dsu dsu(n);
	int ans = 0, cnt = n;
	while (cnt != 1) {
		ans += 1;
		for (int i = 1; i <= n; ++ i)
			sur[dsu.find(i)] = dsu.find(i);
		for (int i = 1; i <= n; ++ i) {
			for (auto j : v[i]) {
				if (p[sur[dsu.find(i)]] < p[dsu.find(j)])
					sur[dsu.find(i)] = dsu.find(j);
			}
		}
		for (int i = 1; i <= n; ++ i) {
			if (dsu.find(i) == i && sur[i] != i) {
				dsu.unite(sur[i], i);
				cnt -= 1;
			}
		}
	}
	cout << ans << "\n";
}
