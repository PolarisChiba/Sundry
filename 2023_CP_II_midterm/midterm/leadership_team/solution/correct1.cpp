#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;
 
typedef long long ll;
ll MOD = 1000000007LL;
 
int n, m;
ll w[100009];
 
vector<int> v[100009];
vector<int> r[100009];
bool vis[100009];
 
vector<int> z;
void Dfs1(int u) {
    vis[u] = 1;
    for (auto i : v[u]) if (!vis[i]) Dfs1(i);
    z.push_back(u);
}

ll sum = 0;
void Dfs2(int u) {
    sum += w[u];
    vis[u] = 0;
    for (auto i : r[u]) if (vis[i]) Dfs2(i);
}
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
 
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) cin >> w[i];
    for (int i = 1; i <= m; ++ i) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        r[b].push_back(a);
    }
 
    for (int i = 1; i <= n; ++ i) if (!vis[i]) Dfs1(i);
    reverse(z.begin(), z.end());
	ll ans = 0;
    for (auto i : z) if(vis[i]) {
		sum = 0;
        Dfs2(i);
		ans = max(ans, sum);
    }

    cout << ans << "\n";
}