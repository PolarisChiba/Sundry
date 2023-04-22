#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

    int T = 1, n;
    while (cin >> n && n) {
        vector<vector<int>> nation(11, vector<int>(11, 0));
        vector<string> name(n + 1);
        for (int _ = 1; _ <= n; ++ _) {
            int xl, yt, xr, yb;
            cin >> name[_] >> xl >> yt >> xr >> yb;
            for (int i = xl; i <= xr; ++ i)
                for (int j = yt; j <= yb; ++ j)
                    nation[i][j] = _;
        }
            
        vector<vector<int>> city_time(11, vector<int>(11, 1e9));
        vector<vector<vector<int>>> money(11, vector<vector<int>>(11, vector<int>(n + 1, 0)));

        for (int i = 1; i <= 10; ++ i)
            for (int j = 1; j <= 10; ++ j)
                if (nation[i][j] != 0)
                    money[i][j][nation[i][j]] = 1e6;

        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        auto Range = [](int x, int y) -> bool {
            return 1 <= x && x <= 10 && 1 <= y && y <= 10;
        };
        int now_time = 0;
        auto Simulate = [&]() -> bool {
            bool flag = true;
            for (int i = 1; i <= 10; ++ i) {
                for (int j = 1; j <= 10; ++ j) {
                    if (city_time[i][j] != 1e9 || nation[i][j] == 0) continue;
                    bool ok = true;
                    for (int k = 1; k <= n; ++ k)
                        ok &= (money[i][j][k] != 0);
                    if (ok) city_time[i][j] = now_time;
                    flag &= ok;
                }
            }
            now_time += 1;
            if (flag) return true;

            vector<vector<vector<int>>> temp(11, vector<vector<int>>(11, vector<int>(n + 1, 0)));
            for (int i = 1; i <= 10; ++ i) {
                for (int j = 1; j <= 10; ++ j) {
                    if (nation[i][j] == 0) continue;
                    for (int l = 1; l <= n; ++ l) {
                        if (money[i][j][l] < 1000) continue;
                        int res = money[i][j][l] / 1000;
                        for (int k = 0; k < 4; ++ k) {
                            int tx = i + dx[k], ty = j + dy[k];
                            if (!Range(tx, ty) || nation[tx][ty] == 0) continue;
                            temp[tx][ty][l] += res;
                            money[i][j][l] -= res;
                        }   
                    }
                }
            }

            for (int i = 1; i <= 10; ++ i)
                for (int j = 1; j <= 10; ++ j)
                    for (int k = 1; k <= n; ++ k)
                        money[i][j][k] += temp[i][j][k];

            return false;
        };

        while (Simulate() == false);

        vector<int> nation_time(n + 1);
        for (int i = 1; i <= 10; ++ i)
            for (int j = 1; j <= 10; ++ j)
                if (nation[i][j] != 0)
                    nation_time[nation[i][j]] = max(nation_time[nation[i][j]], city_time[i][j]);
        
        cout << "Case Number " << T ++ << endl;
        vector<pair<int, string>> ans;
        for (int i = 1; i <= n; ++ i)
            ans.push_back({nation_time[i], name[i]});
        sort(ans.begin(), ans.end());
        for (auto [a, b] : ans)
            cout << "   " << b << "   " << a << endl;
    }
}