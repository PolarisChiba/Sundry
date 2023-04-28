#include <bits/stdc++.h>
using namespace std;

int n;
int a[100009];
int b[100009];
int id[100009];
int ch[100009];
int lc[100009];
int rc[100009];
int now;

int Calc(int l, int r) {
    if (l == r) return b[l];
    if (l > r) return 0;

    now += 1;
    for (int i = l; i <= r; ++ i) ch[b[i]] = now;
    int pr = 0;
    for (int i = 1; i <= n; ++ i) {
        if (ch[a[i]] == now) {
            pr = i;
            break;
        }
    }

    for (int i = l; i <= r; ++ i) {
        if (b[i] == a[pr]) {
            lc[a[pr]] = Calc(l, i - 1);
            rc[a[pr]] = Calc(i + 1, r);
            return a[pr];
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> a[i];
    for (int i = 1; i <= n; ++ i) cin >> b[i];

    Calc(1, n);
    for (int i = 1; i <= n; ++ i)
        cout << lc[i] << " " << rc[i] << "\n";
}