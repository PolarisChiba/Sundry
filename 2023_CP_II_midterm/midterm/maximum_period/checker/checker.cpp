#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerChecker("maximum_period", argc, argv);
	compareRemainingLines();
}
