#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
	assert(n <= 300000);
    vector<int> v(n);
    for (auto &i : v) cin >> i, assert(1 <= i && i <= 1000000000);

    set<int> s;
    int ans = 0, pre = 0;
    for (int i = 0; i < n; ++ i) {
        while (!s.empty() && (s.find(v[i] * 2) != s.end() || (v[i] % 2 == 0 && s.find(v[i] / 2) != s.end()))) {
            if (s.find(v[pre]) != s.end()) s.erase(s.find(v[pre]));
            pre += 1;
        }
        s.insert(v[i]);
        ans = max(ans, i - pre + 1);
    }
    cout << ans << "\n";
}