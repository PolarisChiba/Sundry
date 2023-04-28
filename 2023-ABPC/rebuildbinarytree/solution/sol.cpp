#include <bits/stdc++.h>
using namespace std;

int n;
int a[100009];
int b[100009];
int pa[100009];
int pb[100009];
int st[20][100009];
int rc[100009];
int lc[100009];

int query(int a, int b) {
    int k = __lg(b - a + 1);
    return min(st[k][a], st[k][b - (1 << k) + 1]);
}

int Calc(int l, int r) {
    if (l == r) return b[l];
    if (l > r) return 0;

    int pr = query(l, r);
    int L = Calc(l, pb[a[pr]] - 1);
    int R = Calc(pb[a[pr]] + 1, r);
    lc[a[pr]] = L;
    rc[a[pr]] = R;

    return a[pr];
}

int main() {
    // ios::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> a[i];
    for (int i = 1; i <= n; ++ i) cin >> b[i];
    
    for (int i = 1; i <= n; ++ i) pa[a[i]] = i;
    for (int i = 1; i <= n; ++ i) pb[b[i]] = i;
    for (int i = 1; i <= n; ++ i) st[0][i] = pa[b[i]];
    for (int i = 1; (1 << i) <= n; ++ i)
        for (int j = 1; j + (1 << i) <= n + 1; ++ j)
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);

    int r = Calc(1, n);
    for (int i = 1; i <= n; ++ i)
        cout << lc[i] << " " << rc[i] << "\n";
}