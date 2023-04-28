#include "testlib.h"
using namespace std;

int main() {
	registerValidation();
	
	int n = inf.readInt(1, 100'000, "n");
	inf.readSpace();
	int m = inf.readInt(1, 200'000, "m");
	inf.readEoln();

	for (int i = 1; i <= n; ++ i) {
		inf.readInt(1, 1'000'000'000, "k");
		if (i != n) inf.readSpace();
		else inf.readEoln();
	}

	set<pair<int, int>> s;
	for (int i = 1; i <= m; ++ i) {
		int a = inf.readInt(1, n, "a");
		inf.readSpace();
		int b = inf.readInt(1, n, "b");
		inf.readEoln();
		
		ensure(a != b);
		ensure(s.find({a, b}) == s.end());
		s.insert({a, b});
	}
	inf.readEof();

	return 0;
}
