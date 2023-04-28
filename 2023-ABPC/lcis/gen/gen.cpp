#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {

    registerGen(argc, argv, 1);

	int n = opt<int>(1);
    vector<int> a = rnd.perm(n, 1);
    vector<int> b = rnd.perm(n, 1);
    
    println(n);
    println(a);
    println(b);
}
