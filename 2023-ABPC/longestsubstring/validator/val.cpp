#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100'000, "t");
    inf.readEoln();

    for (int _ = 1; _ <= t; ++ _) {
        setTestCase(_);
        int n = inf.readInt(1, 100'000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 2, "m");
        inf.readEoln();
        string a = inf.readToken("[a-z]{1, 100000}", "a");
        inf.readEoln();
        string b = inf.readToken("[a-z]{1, 2}", "b");
        inf.readEoln();

        ensure((int)a.size() == n);
        ensure((int)b.size() == m);
    }

    inf.readEof();
}