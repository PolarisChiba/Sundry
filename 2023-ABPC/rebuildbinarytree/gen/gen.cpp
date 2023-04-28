#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

class ParentGenerator {
    public:
        void push(int x) {
            for (int _ = 0; _ < 2; ++ _) {
                pool.push_back(x);
                swap(pool[rnd.next(0, (int)pool.size() - 1)], pool.back());
            }
        }
        int pop() {
            int p = rnd.next(0, (int)pool.size() - 1);
            int x = pool[p];
            swap(pool[p], pool.back());
            pool.pop_back();
            return x;
        }

        ParentGenerator(int r) {
            pool.clear();
            push(r);
        }
    private:
        vector<int> pool;
};

class BinaryTree {
    public:
        BinaryTree(int n, int r):root(r) {
            v.assign(n + 1, vector<int>(0));
        }
        void add_pedge(int p, int a) {
            // 1 ~ n
            v[p].push_back(a);
        }
        void set_child() {
            for (auto &i : v) {
                if (i.empty()) {
                    i.push_back(0);
                    i.push_back(0);
                } else if ((int)i.size() == 1) {
                    i.push_back(0);
                    if (rnd.next(0, 1) == 0) swap(i.front(), i.back());
                }
            }
        }
        void Dfs(int u) {
            if (v[u][0]) Dfs(v[u][0]);
            in_order.push_back(u);
            if (v[u][1]) Dfs(v[u][1]);
        }
        vector<int> Dfs() {
            in_order.clear();
            Dfs(root);
            return in_order;
        }
        vector<int> Bfs() {
            level_order.clear();
            queue<int> q;
            q.push(root);
            while (!q.empty()) {
                int p = q.front(); q.pop();
                level_order.push_back(p);
                if (v[p][0]) q.push(v[p][0]);
                if (v[p][1]) q.push(v[p][1]);
            }
            return level_order;
        }

    private:
        int root;
        vector<vector<int>> v;
        vector<int> in_order;
        vector<int> level_order;
};

int main(int argc, char* argv[]) {

    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);

    ParentGenerator pg(1);
    BinaryTree bt(n, 1);
    for (int i = 2; i <= n; ++ i) {
        int p = pg.pop();
        bt.add_pedge(p, i);
        // cout << p << " " << i << "\n";
        pg.push(i);
    }
    bt.set_child();

    auto level = bt.Bfs();
    auto in_order = bt.Dfs();

    vector<int> id(n + 1);
    iota(id.begin() + 1, id.end(), 1);
    shuffle(id.begin() + 1, id.end());
    
    for (auto &i : level) i = id[i];
    for (auto &i : in_order) i = id[i];
    
    println(n);
    println(level);
    println(in_order);
}