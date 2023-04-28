#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;
 
typedef long long ll;
ll MOD = 1000000007LL;

int n;
string s;
int v[1000009];
int z[1000009];
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
 
    cin >> n >> s;
	for (int i = 0; i < n; ++ i) {
		cin >> v[i];
		if (i) v[i] += v[i - 1];
	}
    
    int res = 0;
    for (int i = 1; i < (int)s.size(); ++ i){
        z[i] = max(0, min(z[i - res], z[res] - i + res));
        while (i + z[i] < (int)s.size() && s[i + z[i]] == s[z[i]]) ++ z[i];
        if (res + z[res] < i + z[i]) res = i;
    }
 
    int now = (int)s.size();
	int ans = v[now - 1];
 
    for (int i = (int)s.size() - 1; i >= 1; -- i) {
        if (i + z[i] >= (int)s.size()) {
			ans = max(ans, v[i - 1]);
            now = i;
        }
    }
    
	cout << ans << "\n";
}