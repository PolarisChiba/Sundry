#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "t");
    inf.readEoln();
    while (t -- ) {
        int n = inf.readInt(1, 100000, "n");
        inf.readEoln();
        for (int i = 1; i <= n; ++ i) {
            int x = inf.readInt(1, 1000000000, "x");
            if (i == n) inf.readEoln();
            else inf.readSpace();
        }
        for (int i = 1; i <= n; ++ i) {
            int x = inf.readInt(1, 1000000000, "x");
            if (i == n) inf.readEoln();
            else inf.readSpace();
        }
    }
    inf.readEof();
}