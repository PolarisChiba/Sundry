#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);

    int k = atoi(argv[1]);
	
    int n = 1;
    vector<int> v{0};
    while ((n << 1) <= k) {
        vector<int> u;
        for (auto i : v) {
            u.push_back(i);
            u.push_back(i + n);
        }
        n <<= 1;
        swap(u, v);
    }
    println(n, n - 1);
    
    set<int> s;
	while ((int)s.size() < n) {
		s.insert(rnd.next(1, 1'000'000'000));
	}
	vector<int> t(s.begin(), s.end());

    vector<int> z(n);
    iota(z.begin(), z.end(), 0);
    shuffle(z.begin(), z.end());

    vector<int> p(n);
	for (int i = 0; i < n; ++ i)
        p[z[i]] = t[v[i]];
    println(p);

    for (int i = 0; i < n - 1; ++ i)
        println(z[i] + 1, z[i + 1] + 1);
}
