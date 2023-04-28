#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;
    while (t -- ) {
        int n;
        cin >> n;
        vector<pair<int, int>> v(n);
        for (int i = 0; i < n; ++ i) cin >> v[i].first;
        for (int i = 0; i < n; ++ i) cin >> v[i].second;
        vector<int> s;
        for (int i = 0; i < n; ++ i) {
            while (!s.empty() && v[i] >= v[s.back()]) s.pop_back();
            cout << (s.empty() ? 0 : s.back() + 1) << " \n"[i == n - 1];
            s.push_back(i);
        }
    }
}