#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, 10, "t");
    inf.readEoln();
    while ( t -- ) {
        int n = inf.readInt(1, 100, "n");
        inf.readSpace();
        int q = inf.readInt(1, 100, "q");
        inf.readEoln();
        for (int i = 1; i <= n; ++ i) {
            int x = inf.readInt(1, 1000000000, "x");
            if (i == n) inf.readEoln();
            else inf.readSpace();
        }
        vector<tuple<int, int, int>> Q(q);
        for (auto &i : Q) {
            
            get<0>(i) = inf.readInt(1, n, "l");
            inf.readSpace();
            get<1>(i) = inf.readInt(1, n, "r");
            inf.readSpace();
            get<2>(i) = inf.readInt(1, 1000000000, "x");
            inf.readEoln();
            ensure(get<0>(i) <= get<1>(i));
        }
        for (int i = 0; i < q - 1; ++ i) {
            ensure(get<0>(Q[i]) <= get<0>(Q[i + 1]));
            ensure(get<1>(Q[i]) <= get<1>(Q[i + 1]));
        }
    }
    inf.readEof();
}