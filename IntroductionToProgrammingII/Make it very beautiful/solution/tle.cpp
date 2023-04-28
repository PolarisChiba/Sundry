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
            int l, r;
            cin >> l >> r;
            vector<int> b(a + l, a + r + 1);
            sort(b.begin(), b.end());
            cout << r - l + 1 - (unique(b.begin(), b.end()) - b.begin()) << "\n";
        }
        cout << "\n";
    }
}