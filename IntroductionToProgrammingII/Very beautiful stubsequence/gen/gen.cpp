#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    println(10);
    int n = atoi(argv[1]);
    for (int _ = 1; _ <= 10; ++ _) {
        println(n);

        if (_ == 1) {
            vector<int> v(n, rnd.next(1, 1'000'000'000));
            println(v);
        } else if (_ <= 3) {
            vector<int> v(n);
            vector<int> z((int)sqrt(n));
            for (auto &i : z) i = rnd.next(1, 1'000'000'000);
            for (auto &i : v) i = rnd.any(z);
            println(v);
        } else if (_ <= 6) {
            vector<int> v;
            for (int i = 1; i <= 10; ++ i) {
                vector<int> z((int)sqrt(n / 10));
                for (auto &i : z) i = rnd.next(1, 1'000'000'000);
                for (int j = 1; j <= n / 10; ++ j)
                    v.push_back(rnd.any(z));
            }
            println(v);
        } else if (_ <= 9) {
            vector<int> v;
            for (int i = 1; i <= 10; ++ i) {
                vector<int> z(n / 100);
                for (auto &i : z) i = rnd.next(1, 1'000'000'000);
                for (int j = 1; j <= n / 10; ++ j)
                    v.push_back(rnd.any(z));
            }
            if (_ == 9) shuffle(v.begin(), v.end());
            println(v);
        } else {
            vector<int> v(n);
            for (auto &i : v) i = rnd.next(1, n / 10);
            println(v);
        }
    }
}