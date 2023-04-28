#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);

    int t = 10;

    println(t);
    while (t -- ) {

        vector<int> v(n);
        if (t == 1) {
            n = 10;
            v = vector<int>({1, 1, 1, 1, 2, 3, 3, 3, 3, 3});
        } else if (t == 2) {
            for (auto &i : v) 
                i = rnd.next(1, n / 998);
        } else if (t == 3) {
            for (auto &i : v) 
                i = rnd.next(1, n / 100);
        } else if (t == 4) {
            for (auto &i : v) 
                i = rnd.next(1, n / 10);
        } else if (t == 5) {
            for (auto &i : v) 
                i = rnd.next(1, n);
        } else if (t == 6) {
            for (auto &i : v) 
                i = rnd.next(1, 10 * n);
        } else if (t == 7) {
            for (auto &i : v) 
                i = rnd.next(1, 100 * n);
        } else if (t == 8) {
            for (auto &i : v) 
                i = rnd.next(1, 1000 * n);
        } else {
            for (auto &i : v)
                i = rnd.next(1, 1'000'000'000);
        }

        println(n);
        println(v);
    }
}