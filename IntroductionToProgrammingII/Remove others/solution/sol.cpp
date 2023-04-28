#include <bits/stdc++.h>
using namespace std;

int main() {
    // ios::sync_with_stdio(0); cin.tie(0);

    int t;
    scanf("%d", &t);
    while (t -- ) {
        int n, q;
        scanf("%d %d", &n, &q);
        vector<int> v(n);
        for (auto &i : v) scanf("%d", &i);
        int L = 0, R = -1;
        unordered_map<int, int> cnt;
        for (int i = 1; i <= q; ++ i) {
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);
            l -= 1, r -= 1;
            while (R < r) {
                cnt[v[R + 1]] += 1;
                R += 1;
            }
            while (L < l) {
                cnt[v[L]] -= 1;
                L += 1;
            }
            printf("%d\n", R - L + 1 - cnt[x]);
        }
        printf("\n");
    }
}