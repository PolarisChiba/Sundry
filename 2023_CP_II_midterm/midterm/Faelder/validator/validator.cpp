#include "testlib.h"
using namespace std;

const int MAXN = 1000;

int main() {
	registerValidation();

	int n = inf.readInt(1, 300, "n");
	inf.readSpace();
	int m = inf.readInt(1, 300, "m");
	inf.readEoln();
	
	int c = inf.readInt(0, n * m, "c");
	inf.readEoln();
	
	set<pair<int, int>> s;
	for (int i = 0; i < c; ++ i) {
		int x = inf.readInt(1, n, "x");
		inf.readSpace();
		int y = inf.readInt(1, m, "y");
		inf.readEoln();
		
		ensure(s.find({x, y}) == s.end());
		s.insert({x, y});
	}
	inf.readEof();

	return 0;
}
