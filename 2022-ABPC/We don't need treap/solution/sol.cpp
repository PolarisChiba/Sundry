#include <bits/stdc++.h>
using namespace std;

int main() {
    // ios::sync_with_stdio(0); cin.tie(0);

    int t;
    scanf("%d", &t);
    while (t -- ) {
        int n, Q;
        scanf("%d %d", &n, &Q);
        vector<pair<int, long long>> v(n + 1);
        for (int i = 1; i <= n; ++ i) scanf("%d", &v[i].first);
        for (int i = 1; i <= n; ++ i) scanf("%lld", &v[i].second);
        vector<tuple<int, int, int, int>> q(Q);
        for (auto &[a, b, c, d] : q) {
            scanf("%d", &a);
            if (a == 1) scanf("%d %d", &b, &c);
            else if (a == 2) scanf("%d %d %d", &b, &c, &d);
            else if (a == 3) scanf("%d %d %d", &b, &c, &d);
        }
        int Y, p = 0;
        long long z = 0;
        scanf("%d", &Y);
        for (int i = 1; i <= n; ++ i) if (v[i].first == Y) p = i, z = v[i].second;
        for (auto [a, b, c, d] : q) {
            if (a == 1) {
                if (b <= p && p <= c)
                    p = b + c - p;
            } else if (a == 2) {
                if (b <= p && p <= b + d - 1)
                    p = p + (c - b);
                else if (c <= p && p <= c + d - 1)
                    p = p - (c - b);
            } else if (a == 3) {
                if (b <= p && p <= c)
                    z += 1LL * d;
            }
        }
        printf("%lld\n", z);
    }
}