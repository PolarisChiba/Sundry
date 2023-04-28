#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, 10, "t");
    inf.readEoln();
    while ( t -- ) {
        int n = inf.readInt(1, 200000, "n");
        inf.readSpace();
        int q = inf.readInt(1, 100000, "q");
        inf.readEoln();
        for (int i = 1; i <= n; ++ i) {
            int x = inf.readInt(1, 1000000000, "x");
            if (i == n) inf.readEoln();
            else inf.readSpace();
        }
        vector<pair<int, int>> Q(q);
        for (auto &i : Q) {
            
            i.first = inf.readInt(1, n, "l");
            inf.readSpace();
            i.second = inf.readInt(1, n, "r");
            inf.readEoln();
            ensure(i.first <= i.second);
        }
        for (int i = 0; i < q - 1; ++ i) {
            ensure(Q[i].first <= Q[i + 1].first);
            ensure(Q[i].second <= Q[i + 1].second);
        }
    }
    inf.readEof();
}