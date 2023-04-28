#include <bits/stdc++.h>
using namespace std;

int t, n, Q;
pair<int, long long> v[100009];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> t;
    while (t -- ) {
        cin >> n >> Q;
        for (int i = 1; i <= n; ++ i) cin >> v[i].first;
        for (int i = 1; i <= n; ++ i) cin >> v[i].second;
        while ( Q -- ) {
            int op;
            cin >> op;
            if (op == 1) {
                int L, R;
                cin >> L >> R;
                reverse(v + L, v + R + 1);
            } else if (op == 2) {
                int a, b, t;
                cin >> a >> b >> t;
                for (int i = a; i <= a + t - 1; ++ i)
                    swap(v[i], v[i + (b - a)]);
            } else if (op == 3) {
                int L, R, x;
                cin >> L >> R >> x;
                for (int i = L; i <= R; ++ i)
                    v[i].second += 1LL * x;
            }
        }
        int Y;
        cin >> Y;
        for (int i = 1; i <= n; ++ i) 
            if (v[i].first == Y) 
                cout << v[i].second << "\n";
    }
}