#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int lc[100009];
int rc[100009];

int main(int argc, char* argv[]) {

    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);

    for (int i = 1; i < n; ++ i) {
        if (rnd.next(0, 1) == 0)
            lc[i] = i + 1;
        else
            rc[i] = i + 1;
    }

    int r = 1;
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

    vector<int> id(n + 1);
    iota(id.begin() + 1, id.end(), 1);
    shuffle(id.begin() + 1, id.end());
    
    for (auto &i : level) i = id[i];
    for (auto &i : in_order) i = id[i];
    
    println(level);
    println(in_order);
}