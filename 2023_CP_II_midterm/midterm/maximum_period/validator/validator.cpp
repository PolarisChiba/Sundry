#include "testlib.h"
using namespace std;

int main() {
	registerValidation();

	int n = inf.readInt(1, 1'000'000, "n");
	inf.readEoln();
	
	string s = inf.readWord("[a-z]{1,1000000}");
	inf.readEoln();
	ensure((int)s.size() == n);

	for (int i = 0; i < n; ++ i) {
		inf.readInt(-1'000, 1'000, "a");
		if (i != n - 1) inf.readSpace();
		else inf.readEoln();
	}
	inf.readEof();
	
	return 0;
}
