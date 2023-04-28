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
        vector<int> v(n);
        
        if (_ == 1) v = vector<int>(n, 1);
        else if (_ == 2) iota(v.begin(), v.end(), 1);
        else if (_ == 3) iota(v.begin(), v.end(), 1), reverse(v.begin(), v.end());
        else if (_ == 4) {
            for (int i = 0; i < n; ++ i) v[i] = (i < n / 2 ? 1 : 2);
            shuffle(v.begin(), v.end());
        } else if (_ == 5) {
            for (int i = 0; i < n; ++ i)
                v[i] = rnd.next(1, 1000000000);
        } else {
            vector<int> res((int)sqrt(n) * 2);
            for (auto &i : res) i = rnd.next(1, 1000000000);
            for (auto &i : v) i = res[rnd.next(0, (int)res.size() - 1)];
        }
        for (int i = 0; i < n; ++ i) cout << v[i] << " \n"[i == n - 1];

        int L = 1, R = 1;
        for (int i = 1; i <= q / 2; ++ i) {
            int l = rnd.wnext(L, n / 2, -20);
            int r = rnd.wnext(max(l, R), n / 2, -20);
            int x = v[rnd.next(l - 1, r - 1)];
            if (rnd.next(0, 9) == 0) x = rnd.next(1, 1000000000);
            L = l, R = r;
            cout << L << " " << R << " " << x << "\n";
        }
        for (int i = q / 2 + 1, a = n / 2, b = 3 * n / 4; i <= q - 2; ++ i) {
            int x = v[rnd.next(a - 1, b - 1)];
            if (rnd.next(0, 9) == 0) x = rnd.next(1, 1000000000);
            cout << a << " " << b << " " << x << "\n";
            ++ a, ++ b;
            if (n - 1 < a) a = n - 1;
            if (n - 1 < b) b = n - 1;
        }
        for (int i = q - 1, now = n - 1; i <= q; ++ i, ++ now) {
            int x = v[rnd.next(now - 1, now - 1)];
            if (rnd.next(0, 9) == 0) x = rnd.next(1, 1000000000);
            cout << now << " " << now << " " << x << "\n";
        }
    }
}