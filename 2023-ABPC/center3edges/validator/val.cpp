#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100'000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200'000, "m");
    inf.readEoln();

    set<pair<int, int>> s;
    for (int i = 1; i <= m; ++ i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        int c = inf.readInt(1, 10'000, "c");
        inf.readEoln();

        if (a > b) swap(a, b);
        ensure(s.find({a, b}) == s.end());
        s.insert({a, b});
    }

    inf.readEof();
}