#include <bits/stdc++.h>
using namespace std;
 
int main() {
	int t;
    cin >> t;
    while (t -- ) {
        int n; 
        cin >> n;
        
        set<int> s;
        int ans = 0;
        int pre = 0;
        vector<int> v(n);
        for (int i = 0; i < n; ++ i) {
            cin >> v[i];
            while (s.count(v[i])) {
                s.erase(v[pre]);
                ++ pre;
            }
            s.insert(v[i]);
            ans = max(ans, (int)s.size());
        }
        cout << ans << "\n";
    }
}