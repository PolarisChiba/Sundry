#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerChecker("leadership_team", argc, argv);
	compareRemainingLines();
}
