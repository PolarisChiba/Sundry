#include <iostream>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);

	int n = atoi(argv[1]);
	int q = atoi(argv[2]);

	println(n);
	vector<int> v(n);
	for (auto &i : v) i = rnd.next(1, 10'000);
	println(v);

	println(q);
	while ( q -- ) {
		string op;
		if (rnd.next(0, 1) == 0)
			op = "f";
		else
			op = "b";
		int x = rnd.next(1, 10'000);
		println(op, x);
	}
}
