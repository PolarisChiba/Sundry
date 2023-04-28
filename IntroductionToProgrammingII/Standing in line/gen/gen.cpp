#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int t = atoi(argv[1]);
    int n = atoi(argv[2]);

    cout << t << "\n";
    for (int _ = 1; _ <= t; ++ _) {
        cout << n << "\n";
        if (_ == 1) {
            for (int i = 1; i <= n; ++ i)
                cout << i << " \n"[i == n];
            for (int i = 1; i <= n; ++ i)
                cout << i << " \n"[i == n];
        } else if (_ == 2) {
            for (int i = 1; i <= n; ++ i)
                cout << n - i + 1 << " \n"[i == n];
            for (int i = 1; i <= n; ++ i)
                cout << n - i + 1 << " \n"[i == n];
        } else if (_ == 3) {
            for (int i = 1; i <= n; ++ i)
                cout << 1 << " \n"[i == n];
            for (int i = 1; i <= n; ++ i)
                cout << 1 << " \n"[i == n];
        } else {
            for (int i = 1; i <= n; ++ i) {
                if (n <= 10)
                    cout << rnd.next(1, 10) << " \n"[i == n];
                else
                    cout << rnd.next(1, 1000000000) << " \n"[i == n];
            }
            for (int i = 1; i <= n; ++ i) {
                if (n <= 10)
                    cout << rnd.next(1, 10) << " \n"[i == n];
                else
                    cout << rnd.next(1, 1000000000) << " \n"[i == n];
            }
        }
    }
}