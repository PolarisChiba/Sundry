#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef long long ll;

vector<int> v;
vector<tuple<int, int, int>> u;

int mx;
int z, ans;

void Dfs(int st, int d) {
	if (d == 0) {
		int res = 0;
		for (int i = 0; i < (int)v.size(); ++ i) {
			if ((z >> i) & 1)
				res += v[i];
		}
		for (auto &[a, b, c] : u) {
			int cnt = __builtin_popcount((z & b));
			if (cnt)
				res -= (cnt - 1) * c;
		}
		if (mx < res) {
			mx = res;
			ans = z;
		}
		return;
	}
	for (int i = st; i < (int)v.size(); ++ i) {
		z ^= (1 << i);
		Dfs(i + 1, d - 1);
		z ^= (1 << i);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T = 1;
	int n, k;
	while (cin >> n >> k && (n || k)) {
		v.assign(n, 0);
		for (auto &i : v) cin >> i;
		int m;
		cin >> m;
		u.assign(m, tuple<int, int, int>(0, 0, 0));
		for (auto &[a, b, c] : u) {
			cin >> a;
			for (int i = 1; i <= a; ++ i) {
				int x;
				cin >> x;
				b ^= (1 << (x - 1));
			}
			cin >> c;
		}
		
		z = ans = mx = 0;
		Dfs(0, k);

		cout << "Case Number  " << T ++ << "\n";
		cout << "Number of Customers: " << mx << "\n";
		cout << "Locations recommended: ";
		vector<int> e;
		for (int i = 0; i < n; ++ i) {
			if ((ans >> i) & 1)
				e.push_back(i + 1);
		}
		for (int i = 0; i < (int)e.size(); ++ i) {
			cout << e[i] << " \n"[i == (int)e.size() - 1];
		}
		cout << "\n";
	}
}