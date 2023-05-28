#include <iostream>
#include "testlib.h"
using namespace std;

vector<string> japanese = {
	"a", "i", "u", "e", "o", 
	"ka", "ki", "ku", "ke", "ko", 
	"sa", "shi", "su", "se", "so",
	"ta", "chi", "tsu", "te", "to",
	"na", "ni", "nu", "ne", "no",
	"ha", "hi", "fu", "he", "ho",
	"ma", "mi", "mu", "me", "mo",
	"ya", "yu", "yo",
	"ra", "ri", "ru", "re", "ro",
	"wa", "o",
	"n"
};

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	
	int q = rnd.next(1, 100);
	vector<int> v = rnd.partition(q, 10'000, 1);

	for (int i = 0; i < (int)v.size(); ++ i) {
		int t = rnd.next(1, min(20, v[i]));
		vector<int> u = rnd.partition(t, v[i], 1);
		string z = "";
		for (int j = 0; j < t; ++ j) {
			while (u[j] --)
				z += rnd.any(japanese);
			if (j < t - 1)
				z += " ";
		}
		println(z);
	}
}
