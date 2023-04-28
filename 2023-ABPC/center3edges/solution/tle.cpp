#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;
vector<pair<int, int>> v[100009];
vector<tuple<int, int, int>> edge;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; ++ i) {
        int a, b, c;
        cin >> a >> b >> c;
        v[a].push_back({b, c});
        v[b].push_back({a, c});
        edge.push_back({a, b, c});
    }
    
    ll ans = 0;
    for (auto &[a, b, c] : edge) {
        for (auto &[x1, y1] : v[a]) if (x1 != b) {
            for (auto &[x2, y2] : v[b]) if (x2 != a) {
                ans += gcd(c, gcd(y1, y2));
            }
        }
    }
    cout << ans << "\n";
}