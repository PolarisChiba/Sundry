#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int t = atoi(argv[1]);
    int n = atoi(argv[2]);
    int q = atoi(argv[3]);

    cout << t << "\n";
    for (int _ = 1; _ <= t; ++ _) {
        cout << n << " " << q << "\n";
        
        if (_ == 1) {
            for (int i = 1; i <= n; ++ i)
                cout << 1 << " \n"[i == n];
        } else if (_ == 2) {
            for (int i = 1; i <= n; ++ i)
                cout << i << " \n"[i == n];
        } else if (_ <= 4) {
            vector<int> v;
            for (int i = 1; i <= n / 2 + 1; ++ i) {
                int res = rnd.next(1, 1000000000);
                v.push_back(res);
                v.push_back(res);
            }
            shuffle(v.begin(), v.end());
            for (int i = 0; i < n; ++ i)
                cout << v[i] << " \n"[i == n - 1];
        } else if (_ <= 5) {
            vector<int> v(n / 2, 1);
            while ((int)v.size() < n) v.push_back(2);
            shuffle(v.begin(), v.end());
            for (int i = 0; i < n; ++ i)
                cout << v[i] << " \n"[i == n - 1];
        } else {
            vector<int> v;
            while ((int)v.size() < 2 * (int)sqrt(n)) v.push_back(rnd.next(1, 1000000000));
            for (int i = 1; i <= n; ++ i) 
                cout << v[rnd.next(0, (int)v.size() - 1)] << " \n"[i == n];
        }
        
        int L = 1, R = 1;
        for (int i = 1; i <= q / 2; ++ i) {
            int l = rnd.wnext(L, n / 2, -10);
            int r = rnd.wnext(max(l, R), n / 2, -10);
            L = l, R = r;
            cout << L << " " << R << "\n";
        }
        for (int i = q / 2 + 1, a = n / 2, b = 3 * n / 4; i <= q - 2; ++ i) {
            cout << a << " " << b << "\n";
            ++ a, ++ b;
            if (n - 1 < a) a = n - 1;
            if (n - 1 < b) b = n - 1;
        }
        for (int i = q - 1, now = n - 1; i <= q; ++ i, ++ now) {
            cout << now << " " << now << "\n";
        }
        
    }
}