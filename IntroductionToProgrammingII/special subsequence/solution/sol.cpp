#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while ( t -- ) {
        int n;
        cin >> n;
        vector<int> v(n);
        for (auto &i : v) cin >> i;

        multiset<int> s;
        int ans = 0, pre = 0;
        for (int i = 0; i < n; ++ i) {
            while (!s.empty() && (s.find(v[i] * 2) != s.end() || (v[i] % 2 == 0 && s.find(v[i] / 2) != s.end()))) {
                s.erase(s.find(v[pre]));
                pre += 1;
            }
            s.insert(v[i]);
            ans = max(ans, (int)s.size());
        }
        cout << ans << "\n";
    }
}