#include <iostream>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	
	int q = atoi(argv[1]);
	println(q);
	while ( q -- ) {
		println(rnd.next(1, 1'000'000'000));
	}
}
