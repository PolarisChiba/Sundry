#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "t");
    inf.readEoln();
    while (t -- ) {
        int n = inf.readInt(1, 100'000, "n");
        inf.readEoln();
        vector<int> v = inf.readIntegers(n, 1, 1'000'000'000, "v");
        inf.readEoln();
    }
    inf.readEof();
}