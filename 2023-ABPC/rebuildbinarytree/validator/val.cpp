#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n;
int a[100009];
int b[100009];
int pa[100009];
int pb[100009];
int st[20][100009];
int rc[100009];
int lc[100009];

int query(int a, int b) {
    int k = __lg(b - a + 1);
    return min(st[k][a], st[k][b - (1 << k) + 1]);
}

int Calc(int l, int r) {
    if (l == r) return b[l];
    if (l > r) return 0;

    int pr = query(l, r);
    int L = Calc(l, pb[a[pr]] - 1);
    int R = Calc(pb[a[pr]] + 1, r);
    lc[a[pr]] = L;
    rc[a[pr]] = R;

    return a[pr];
}

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100'000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++ i) {
        a[i] = inf.readInt(1, n, "a");
        if (i != n) inf.readSpace();
    }
    inf.readEoln();
    
    for (int i = 1; i <= n; ++ i) {
        b[i] = inf.readInt(1, n, "b");
        if (i != n) inf.readSpace();
    }
    inf.readEoln();

    unordered_set<int> sa, sb;
    for (int i = 1; i <= n; ++ i) sa.insert(a[i]), sb.insert(b[i]);
    ensure((int)sa.size() == n);
    ensure((int)sb.size() == n);

    // solution
    for (int i = 1; i <= n; ++ i) pa[a[i]] = i;
    for (int i = 1; i <= n; ++ i) pb[b[i]] = i;
    for (int i = 1; i <= n; ++ i) st[0][i] = pa[b[i]];
    for (int i = 1; (1 << i) <= n; ++ i)
        for (int j = 1; j + (1 << i) <= n + 1; ++ j)
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);

    int r = Calc(1, n);
    //

    vector<int> in_order, level;
    function<void(int)> Dfs = [&](int u) -> void {
        if (lc[u]) Dfs(lc[u]);
        in_order.push_back(u);
        if (rc[u]) Dfs(rc[u]);
    };
    Dfs(r);

    queue<int> q;
    q.push(r);
    while (!q.empty()) {
        int p = q.front(); q.pop();
        level.push_back(p);
        if (lc[p]) q.push(lc[p]);
        if (rc[p]) q.push(rc[p]);
    }

    for (int i = 1; i <= n; ++ i) {
        ensure(a[i] == level[i - 1]);
        ensure(b[i] == in_order[i - 1]);
    }

    inf.readEof();
}