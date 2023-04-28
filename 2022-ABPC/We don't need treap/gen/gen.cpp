#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int t = atoi(argv[1]);
    int _N = atoi(argv[2]);
    int _Q = atoi(argv[3]);

    println(t);
    vector<int> N = rnd.partition(t, _N, 1);
    vector<int> Q = rnd.partition(t, _Q, 1);

    for (int testcase = 0; testcase < t; ++ testcase) {
        int n = N[testcase], q = Q[testcase];
        println(n, q);
        
        println(rnd.perm(n, 1));
        vector<int> b(n);
        for (auto &i : b) i = rnd.next(1, 1000000000);
        println(b);

        while ( q -- ) {
            int op = rnd.next(1, 3);
            if (op == 1) {
                int L = rnd.next(1, n), R = rnd.next(1, n);
                if (R < L) swap(L, R);
                println(op, L, R);
            } else if (op == 2) {
                int a = 0, b = 0;
                while ( a >= b || b == n) {
                    a = rnd.next(1, n);
                    b = rnd.next(1, n);
                }
                println(op, a, b, rnd.next(1, min(b - a, n - b + 1)));
            } else {
                int L = rnd.next(1, n), R = rnd.next(1, n);
                if (R < L) swap(L, R);
                println(op, L, R, rnd.next(1, 1000000000));
            }
        }

        println(rnd.next(1, n));
    }
}