#include <bits/stdc++.h>
using namespace std;

int n;
int a[509];
int b[509];
int f[2][509][509];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> a[i];
    for (int i = 1; i <= n; ++ i) cin >> b[i];
    
    for (int i = 1; i <= n; ++ i) {
        int now = (i & 1);
        int pre = (now ^ 1);
        for (int j = 1; j <= n; ++ j) {
            for (int k = 1; k <= n; ++ k) {
                f[now][j][k] = max({f[pre][j][k], f[now][j - 1][k], f[now][j][k - 1]});
                if (a[i] == b[j] && b[j] == k)
                    f[now][j][k] = max(f[now][j][k], f[pre][j - 1][k - 1] + 1);
            }
        }
    }
    cout << f[(n & 1)][n][n] << "\n";
}