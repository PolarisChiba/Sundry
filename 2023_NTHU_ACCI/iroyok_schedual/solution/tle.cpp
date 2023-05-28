#include <bits/stdc++.h>
using namespace std;

int n, q;
deque<int> d;

int Calc() {
    int a = 0, b = d.front();
    for (int i = 1; i < (int)d.size(); ++ i) {
        int c = max(a + d[i], b);
        a = b;
        b = c;
    }
    return b;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    d.resize(n);
    for (auto &i : d)
        cin >> i;
    cin >> q;
    while ( q -- ) {
        char op;
        int x;
        cin >> op >> x;
        if (op == 'f')
            d.push_front(x);
        else
            d.push_back(x);
        cout << Calc() << "\n";
    }
}