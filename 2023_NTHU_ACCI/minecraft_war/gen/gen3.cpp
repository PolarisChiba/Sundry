#include <iostream>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	
	int q = atoi(argv[1]);
	println(q);
	for (int i = 0; i < q; ++ i)
        println(i);
}
