#include<bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n;
	while ( cin >> n && n ) {
		vector<string> front(n), left(n), back(n), right(n), top(n), bottom(n);
		for (int i = 0; i < n; ++ i)
			cin >> front[i] >> left[i] >> back[i] >> right[i] >> top[i] >> bottom[i];
		
		bool cube[11][11][11] = {};
		while (true) {
			bool ok = true;
			for (int i = 0; i < n; ++ i) {
				for (int j = 0; j < n; ++ j) {
					for (int k = 0; k < n; ++ k) {
						if (cube[i][j][k] == true)
							continue;
						
						set<char> s;
						bool flag;
						
						flag = true;
						for (int l = k - 1; l >= 0; -- l)
							flag &= (cube[i][j][l] == true);
						if (flag || k == 0)
							s.insert(front[i][j]);

						flag = true;
						for (int l = k + 1; l < n; ++ l)
							flag &= (cube[i][j][l] == true);
						if (flag || k == n - 1)
							s.insert(back[i][n - 1 - j]);
						
						flag = true;
						for (int l = j - 1; l >= 0; -- l)
							flag &= (cube[i][l][k] == true);
						if (flag || j == 0)
							s.insert(left[i][n - 1 - k]);
						
						flag = true;
						for (int l = j + 1; l < n; ++ l)
							flag &= (cube[i][l][k] == true);
						if (flag || j == n - 1)
							s.insert(right[i][k]);
						
						flag = true;
						for (int l = i - 1; l >= 0; -- l)
							flag &= (cube[l][j][k] == true);
						if (flag || i == 0)
							s.insert(top[n - 1 - k][j]);
						
						flag = true;
						for (int l = i + 1; l < n; ++ l)
							flag &= (cube[l][j][k] == true);
						if (flag || i == n - 1)
							s.insert(bottom[k][j]);
						
						if (s.size() > 1 || s.find('.') != s.end()) {
							cube[i][j][k] = true;
							ok = false;
						}
					}
				}
			}
			if (ok) break;
		}

		int ans = 0;
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < n; ++ j)
				for (int k = 0; k < n; ++ k)
					ans += (1 - cube[i][j][k]);
		cout << "Maximum weight: " << ans << " gram(s)" << endl;
	}
}