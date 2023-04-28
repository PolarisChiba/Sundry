#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    
    int t = inf.readInt(1, 500'000, "t");
    inf.readEoln();
    int Q = 0;
    for (int _ = 1; _ <= t; ++ _) {
        setTestCase(_);
        int q = inf.readInt(1, 1'000'000, "q");
        inf.readEoln();
        Q += q;
        bool ok = false;
        for (int i = 1; i <= q; ++ i) {
            int a = inf.readInt(1, 2, "a");
            inf.readSpace();
            int b = inf.readInt(-q, q, "b");
            inf.readSpace();
            int c = inf.readInt(-q, q, "c");
            inf.readSpace();
            int d = inf.readInt(-q, q, "d");
            inf.readEoln();
            if (i == 1) ensure(a == 1);
            ok |= (a == 2);
        }
        ensure(ok);
    }
    ensure(Q <= 1'000'000);
    inf.readEof();
}