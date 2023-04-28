#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> factors[10009];
int phi[10009];

int n, m;
vector<pair<int, int>> edge[10009];
int deg[100009];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    for (int i = 1; i <= 10000; ++ i) {
        for (int j = i; j <= 10000; j += i)
            factors[j].push_back(i);
    }
    
    phi[1] = 1;
    for (int i = 2; i <= 10000; ++ i) {
        int p = factors[i][1];
        if (i % (1LL * p * p) != 0) phi[i] = phi[i / p] * (p - 1);
        else phi[i] = phi[i / p] * p;
    }

    cin >> n >> m;
    for (int i = 1; i <= m; ++ i) {
        int a, b, c;
        cin >> a >> b >> c;
        for (auto j : factors[c])
            edge[j].push_back({a, b});
    }

    ll ans = 0;
    for (int i = 1; i <= 10000; ++ i) {
        for (auto [a, b] : edge[i]) {
            deg[a] += 1;
            deg[b] += 1;
        }

        for (auto [a, b] : edge[i]) {
            ans += 1LL * phi[i] * (deg[a] - 1) * (deg[b] - 1);
        }

        for (auto [a, b] : edge[i]) {
            deg[a] -= 1;
            deg[b] -= 1;
        }
    }

    cout << ans << "\n";
}