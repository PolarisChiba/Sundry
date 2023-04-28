#include <bits/stdc++.h>
using namespace std;

int main() {
    // ios::sync_with_stdio(0); cin.tie(0);

    int t;
    scanf("%d", &t);
    while (t -- ) {
        int q;
        scanf("%d", &q);
        vector<int> v(8, -1e9);
        while ( q -- ) {
            int op, a[3];
            scanf("%d %d %d %d", &op, &a[0], &a[1], &a[2]);
            if (op == 1) {
                for (int i = 0; i < 8; ++ i) {
                    int b[3];
                    for (int j = 0; j < 3; ++ j) {
                        if ((i >> j) & 1) b[j] = a[j];
                        else b[j] = -a[j];
                    }
                    v[i] = max(v[i], b[0] + b[1] + b[2]);
                }
            } else if (op == 2) {
                int ans = -1e9;
                for (int i = 0; i < 8; ++ i) {
                    int b[3];
                    for (int j = 0; j < 3; ++ j) {
                        if ((i >> j) & 1) b[j] = -a[j];
                        else b[j] = a[j];
                    }
                    ans = max(ans, b[0] + b[1] + b[2] + v[i]);
                }
                printf("%d\n", ans);
            }
        }
    }
}