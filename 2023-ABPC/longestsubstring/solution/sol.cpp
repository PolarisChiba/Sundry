#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int _ ; cin >> _ ;
    while ( _ -- ) {
        int n, m;
        string a, b;
        cin >> n >> m >> a >> b;

        int ans = 0;
        if (m == 1) {
            for (int i = 0; i < n; ++ i) if (a[i] != b[0]) {
                int j = i;
                while (j < n && a[j] != b[0]) ++ j;
                ans = max(ans, j - i);
                i = j;
            }
        } else {
            int now = 0;
            for (int i = 0; i < n; ++ i) {
                if (i == 0) now = 1;
                else {
                    if (a.substr(i - 1, 2) == b) now = 1;
                    else now += 1;
                }
                ans = max(ans, now);
            }
        }

        cout << ans << "\n";
    }
}