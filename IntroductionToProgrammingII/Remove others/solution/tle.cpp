#include <bits/stdc++.h>
using namespace std;

int t, n, q;
int a[400009];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> t;
    while ( t -- ) {
        cin >> n >> q;
        for (int i = 1; i <= n; ++ i) cin >> a[i];
        while ( q -- ) {
            int l, r, x;
            cin >> l >> r >> x;
            int cnt = 0;
            for (int i = l; i <= r; ++ i) cnt += (a[i] != x);
            cout << cnt << "\n";
        }
        cout << "\n";
    }
}