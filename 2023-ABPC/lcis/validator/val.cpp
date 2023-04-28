#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    vector<int> a(n);
    for (int i = 0; i < n; ++ i) {
        a[i] = inf.readInt(1, n, "a");
        if (i != n - 1) inf.readSpace();
        else inf.readEoln();
    }

    vector<int> b(n);
    for (int i = 0; i < n; ++ i) {
        b[i] = inf.readInt(1, n, "b");
        if (i != n - 1) inf.readSpace();
        else inf.readEoln();
    }
    
    inf.readEof();

    vector<int> che_a(n, 0), che_b(n, 0);
    for (auto &i : a) che_a[i - 1] = 1;
    for (auto &i : b) che_b[i - 1] = 1;
    ensure((che_a == vector<int>(n, 1)));
    ensure((che_b == vector<int>(n, 1)));
}