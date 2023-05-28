#include "testlib.h"
using namespace std;

int main() {
	registerValidation();

	int n = inf.readInt(0, 100'000, "n");
	inf.readEoln();
	for (int i = 1; i <= n; ++ i) {
		inf.readInt(1, 10'000, "x");
		if (i < n) inf.readSpace();
	}
	inf.readEoln();

	int q = inf.readInt(1, 100'000, "q");
	inf.readEoln();
	while ( q -- ) {
		inf.readWord("f|b");
		inf.readSpace();
		inf.readInt(1, 10'000, "xx");
		inf.readEoln();
	}
	inf.readEof();

	return 0;
}
