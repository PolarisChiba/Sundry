#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    
    int t = inf.readInt(1, 100'000, "t");
    inf.readEoln();
    int N = 0, Q = 0;
    for (int testcase = 1; testcase <= t; ++ testcase) {
        setTestCase(testcase);
        int n = inf.readInt(1, 100'000, "n");
        inf.readSpace();
        int q = inf.readInt(1, 100'000, "q");
        inf.readEoln();

        N += n;
        Q += q;
        
        vector<int> z;
        for (int i = 1; i <= n; ++ i) {
            int a = inf.readInt(1, n, "a");
            z.push_back(a);
            if (i == n) inf.readEoln();
            else inf.readSpace();
        }
        sort(z.begin(), z.end());
        for (int i = 0; i < n; ++ i) ensure(z[i] == i + 1);
        
        for (int i = 1; i <= n; ++ i) {
            int b = inf.readInt(1, 1'000'000'000, "b");
            if (i == n) inf.readEoln();
            else inf.readSpace();
        }
        
        while ( q -- ) {
            int op = inf.readInt(1, 3, "op");
            inf.readSpace();
            if (op == 1) {
                int L = inf.readInt(1, n, "L");
                inf.readSpace();
                int R = inf.readInt(L, n, "R");
                inf.readEoln();
            } else if (op == 2) {
                int a = inf.readInt(1, n, "a");
                inf.readSpace();
                int b = inf.readInt(a + 1, n, "b");
                inf.readSpace();
                int t = inf.readInt(1, min(b - a, n - b + 1), "t");
                inf.readEoln();
            } else if (op == 3) {
                int L = inf.readInt(1, n, "L");
                inf.readSpace();
                int R = inf.readInt(L, n, "R");
                inf.readSpace();
                int x = inf.readInt(1, 1'000'000'000, "x");
                inf.readEoln();
            } else {
                ensure(false);
            }
        }
        int Y = inf.readInt(1, n, "Y");
        inf.readEoln();
    }
    ensure(N <= 100'000);
    ensure(Q <= 100'000);
    inf.readEof();
}