#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;
    while ( q -- ) {
        ll k;
        cin >> k;

        if (k == 0) {
            cout << "Peace TeTe\n";
            continue;
        }

        int ans = 0;
        for (ll i = 2; i * i <= k; ++ i) {
            int cnt = 0;
            while (k % i == 0) {
                k /= i;
                cnt += 1;
            }
            ans ^= cnt;
        }
        if (k != 1)
            ans ^= 1;

        if (ans == 0)
            cout << "Aleak\n";
        else
            cout << "Eillo\n";
    }
}
