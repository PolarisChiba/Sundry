#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;
const int N = 300 * 300;
 
struct MaxFlow {
    struct edge {
        ll to, cap, flow, rev;
    };
    vector<edge> G[N + 9];
    int s, t, dis[N + 9], cur[N + 9], n;
 
    ll dfs(int u, ll cap) {
        if (u == t || cap == 0) return cap;
        for (int &i = cur[u]; i < (int)G[u].size(); ++ i) {
            edge &e = G[u][i];
            if (dis[e.to] == dis[u] + 1 && e.flow != e.cap) {
                ll df = dfs(e.to, min(e.cap - e.flow, cap));
                if (df) {
                    e.flow += df;
                    G[e.to][e.rev].flow -= df;
                    return df;
                }
            }
        }
        dis[u] = -1;
        return 0;
    }
 
    bool bfs() {
        fill_n(dis, n, -1);
        queue<int> q;
        q.push(s), dis[s] = 0;
        while (!q.empty()) {
            int tmp = q.front(); q.pop();
            for (auto &u : G[tmp]) {
                if (dis[u.to] == -1 && u.flow != u.cap) {
                    q.push(u.to);
                    dis[u.to] = dis[tmp] + 1;
                }
            }
        }
        return dis[t] != -1;
    }
 
    ll maxflow(int _s, int _t) {
        s = _s, t = _t;
        ll flow = 0, df;
        while (bfs()) {
            fill_n(cur, n, 0);
            while ((df = dfs(s, MOD * MOD))) flow += df;
        }
        return flow;
    }
 
    void init(int _n) {
        n = _n;
        for(int i = 0; i < n; ++ i) G[i].clear();
    }
 
    void add_edge(int u, int v, ll cap) {
        G[u].push_back(edge{v, cap, 0, (int)G[v].size()});
        G[v].push_back(edge{u, 0, 0, (int)G[u].size() - 1});
    }
}dinic;

int main() {
	// ios::sync_with_stdio(0); cin.tie(0);

	int n, m, c;
	cin >> n >> m >> c;
    dinic.init(n * m + 10);

	auto id = [&](int i, int j) -> int {
		return (i - 1) * m + (j - 1);
	};
	
	vector<vector<bool>> s(n + 1, vector<bool>(m + 1, false));
	for (int i = 1; i <= c; ++ i) {
		int a, b;
		cin >> a >> b;
		s[a][b] = true;
	}

    vector<pair<int, int>> left, right;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            if (s[i][j] == false) {
                if ((((i - 1) / 2) + ((j - 1) / 2)) % 2 == 0)
                    left.push_back({i, j});
                else
                    right.push_back({i, j});
            }
        }
    }

    for (auto [a, b] : left) dinic.add_edge(n * m, id(a, b), 1);
    for (auto [a, b] : right) dinic.add_edge(id(a, b), n * m + 1, 1);
    
    int dx[4] = {-2, 2, 0, 0};
    int dy[4] = {0, 0, -2, 2};
    for (auto [x, y] : left) {
        for (int k = 0; k < 4; ++ k) {
            int tx = x + dx[k], ty = y + dy[k];
            if (1 <= tx && tx <= n && 1 <= ty && ty <= m && s[tx][ty] == false) {
                dinic.add_edge(id(x, y), id(tx, ty), 1);
            }
        }
    }

	cout << n * m - c - dinic.maxflow(n * m, n * m + 1) << "\n";
}
