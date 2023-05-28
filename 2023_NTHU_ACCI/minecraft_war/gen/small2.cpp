#include <iostream>
#include "testlib.h"
using namespace std;

vector<int> prime;
vector<bool> notPrime;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);

    int q = atoi(argv[1]);
    int N = atoi(argv[2]);

    notPrime.assign(N + 1, false);

    for (int i = 2; i <= N; ++ i) {
        if (notPrime[i] == false)
            prime.push_back(i);
        for (auto p : prime) {
            if (i * p > N) break;
            notPrime[i * p] = true;
            if (i % p == 0)
                break;
        }
    }
	
    println(q);
	while ( q -- ) {
        vector<int> v(rnd.next(1, 10));
        for (auto &i : v) 
            i = rnd.any(prime);
        long long res = 1;
        while (true) {
            long long tmp = rnd.any(v);
            if (1e9 / tmp >= res)
                res *= tmp;
            else 
                break;
        }
        println(res);
    }
}
