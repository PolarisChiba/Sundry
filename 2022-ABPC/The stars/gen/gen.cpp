#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int t = atoi(argv[1]);

    cout << t << "\n";
    vector<int> Q = rnd.partition(t, 1000000, 2);
    int _ = 0;
    for (auto q : Q) {
        cout << q << "\n";
        _ += 1;

        vector<tuple<int, int, int, int>> v;
        if (_ == 1) {
            for (int i = 1; i <= q / 2; ++ i) {
                int res = rnd.next(-q, q);
                int ret = (q - abs(res)) * (rnd.next(1, 2) == 1 ? 1 : -1);
                v.push_back({1, res, ret, 0});
            }
            for (int i = q / 2 + 1; i <= q - 1; ++ i)
                v.push_back({2, rnd.next(-q, q), rnd.next(-q, q), 0});
            shuffle(v.begin() + 1, v.end());
        } else if (_ == 2) {
            for (int i = 1; i <= q / 2; ++ i) v.push_back({1, 0, 0, 0});
            for (int i = q / 2 + 1; i <= q - 1; ++ i) v.push_back({2, rnd.next(-q, q), rnd.next(-q, q), rnd.next(-q, q)});
            shuffle(v.begin() + 1, v.end());
        } else if (_ % 2 == 0) {
            v.push_back({1, 0, 0, 0});
            int buf = rnd.next(-q, q);
            for (int i = 2; i <= q - 1; ++ i) {
                vector<int> z = rnd.partition(2, i);
                if (rnd.next(1, 2) == 1) z[0] = -z[0];
                if (rnd.next(1, 2) == 1) z[1] = -z[1];
                v.push_back({rnd.next(1, 2), z[0], z[1], buf});
            }
        } else if (_ % 2 == 1) {
            for (int i = 1; i <= q / 2; ++ i) v.push_back({1, rnd.next(-q, q), rnd.next(-q, q), rnd.next(-q, q)});
            for (int i = q / 2 + 1; i <= q - 1; ++ i) v.push_back({2, rnd.next(-q, q), rnd.next(-q, q), rnd.next(-q, q)});
            shuffle(v.begin() + 1, v.end());
        }
        v.push_back({2, 0, 0, 0});
        for (int i = 0; i < q; ++ i) {
            auto [a, b, c, d] = v[i];
            cout << a << " " << b << " " << c << " " << d << "\n";
        }
    }
}