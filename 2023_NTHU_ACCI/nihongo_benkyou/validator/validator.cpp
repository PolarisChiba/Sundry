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
bool isVowel(char c) {
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
	registerValidation();

	int cnt = 0;
	while (!inf.eof()) {
		string s = inf.readString();
		int res = 0;
		for (auto i : s) {
			if (isalpha(i))
				cnt += 1;
			else if (i == ' ')
				res += 1;
			else 
				ensure(i == '\n');
		}
		ensure(res <= 19);
		
		for (int i = 0; i < (int)s.size();) {
			int p = i;
			if (s[i] == ' ' || s[i] == '\n') {
				i += 1;
				continue;
			}
			for (auto j : japanese) {
				if (i + (int)j.size() <= (int)s.size() && s.substr(i, (int)j.size()) == j)
					i += (int)j.size();
			}
			ensure(p != i);
		}
	}
	inf.readEof();
	
	ensure(cnt <= 30'000);

	return 0;
}
