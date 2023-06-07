#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef long long ll;
const ll MOD = 1000000009LL;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T = 1;
	int n;
	while (cin >> n && n) {
		vector<pair<int, int>> v(n);
		for (auto &[a, b] : v)
			cin >> a >> b;
		
		int ans = MOD;
		auto Calc = [&](vector<pair<int, int>> u) -> void {
			vector<int> f((1 << n), MOD);
			f[0] = 0;
			for (int i = 0; i < (1 << n); ++ i) {
				int id = __builtin_popcount(i) - 1;
				for (int j = 0; j < n; ++ j) {
					if ((i >> j) & 1) {
						f[i] = min(f[i], f[i ^ (1 << j)] 
									+ abs(u[id].first - v[j].first) 
									+ abs(u[id].second - v[j].second));
					}
				}
			}
			ans = min(ans, f.back());
		};
		for (int i = 1; i <= n; ++ i) {
			vector<pair<int, int>> u;
			for (int j = 1; j <= n; ++ j)
				u.push_back({i, j});
			Calc(u);
		}
		for (int i = 1; i <= n; ++ i) {
			vector<pair<int, int>> u;
			for (int j = 1; j <= n; ++ j)
				u.push_back({j, i});
			Calc(u);
		}
		vector<pair<int, int>> u;
		for (int i = 1; i <= n; ++ i) {
			u.push_back({i, i});
		}
		Calc(u);
		for (auto &[a, b] : u) 
			b = n + 1 - b;
		Calc(u);
		
		cout << "Board " << T ++ << ": " << ans << " moves required.\n\n";
	}
}