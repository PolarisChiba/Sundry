#include "testlib.h"
using namespace std;

int main() {
	registerValidation();
	
	int q = inf.readInt(1, 100, "q");
	inf.readEoln();
	while ( q -- ) {
		inf.readLong(0LL, 1'000'000'000'000'000'000LL, "n");
		inf.readEoln();
	}
	inf.readEof();

	return 0;
}
