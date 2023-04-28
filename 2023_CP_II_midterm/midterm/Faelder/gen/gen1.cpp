#include <iostream>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);

	int n = rnd.next(1, 300);
	int m = rnd.next(1, 300);
	int c = rnd.next(0, n * m);

	println(n, m);
	println(c);
	
	vector<pair<int, int>> v;
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
			v.push_back({i, j});
	
	shuffle(v.begin(), v.end());
	
	for (int i = 0; i < c; ++ i)
		println(v[i].first, v[i].second);
}
