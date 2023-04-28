#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int t;
    cin >> t;
    while ( t -- ) {
        int q;
        cin >> q;
        vector<tuple<int, int, int>> v;
        while ( q -- ) {
            int op, a, b, c;
            cin >> op >> a >> b >> c;
            if (op == 1) v.push_back({a, b, c});
            else {
                int ans = 0;
                for (auto [x, y, z] : v)
                    ans = max(ans, abs(x - a) + abs(y - b) + abs(z - c));
                cout << ans << "\n";
            }
        }
    }
}