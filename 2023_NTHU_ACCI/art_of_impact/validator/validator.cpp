#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

const int MAXN = 200'000;
const int MAXM = 200'000;
const int MAXP = 1'000'000'000;

struct Dsu {
	int fa[MAXN + 1];
	Dsu(int n) {
		iota(fa + 1, fa + n + 1, 1);
	}
	int find(int x) {
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}
	void unite(int x, int y) {
		fa[find(y)] = find(x);
	}
};

int main() {
	registerValidation();

	int n = inf.readInt(1, MAXN, "n");
	inf.readSpace();
	int m = inf.readInt(n - 1, min(MAXM * 1LL, 1LL * n * (n - 1) / 2), "m");
	inf.readEoln();

	set<int> t;
	for (int i = 1; i <= n; ++ i) {
		int p = inf.readInt(1, MAXP, "p");
		if (i < n)
			inf.readSpace();
		ensure(t.find(p) == t.end());
		t.insert(p);
	}
	inf.readEoln();

	set<pair<int, int>> s;
	for (int i = 1; i <= m; ++ i) {
		int u = inf.readInt(1, n, "u");
		inf.readSpace();
		int v = inf.readInt(1, n, "v");
		inf.readEoln();

		ensure(u != v && s.find({u, v}) == s.end() && s.find({v, u}) == s.end());
		s.insert({u, v});
	}
	inf.readEof();

	Dsu dsu(n);
	for (auto i : s)
		dsu.unite(i.first, i.second);
	for (int i = 1; i <= n; ++ i)
		ensure(dsu.find(1) == dsu.find(i));

	return 0;
}
