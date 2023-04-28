#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {

    registerGen(argc, argv, 1);

    int t = opt<int>(1);
    int n = opt<int>(2);
    println(t);

    vector<int> v = rnd.partition(t, n, 3);
    for (auto i : v) {
        int b = rnd.next(1, 2);
        println(i, b);
        
        string x(i, 'a'), y(b, 'a');
        for (auto &i : x) i = rnd.next(0, 25) + 'a';
        for (auto &i : y) i = rnd.next(0, 25) + 'a';
        
        println(x);
        println(y);
    }
}

