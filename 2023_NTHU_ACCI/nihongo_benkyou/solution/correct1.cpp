#include<bits/stdc++.h>
using namespace std;

bool isVowel(char c) {
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
	ios::sync_with_stdio(0); cin.tie();
	
	string s = "";
	int T = 1;
	while (getline(cin, s)) {
		int mx = 0, mn = 0;
		for (int i = 0; i < (int)s.size(); ++ i) {
			if (isVowel(s[i])) {
				mn += 1;
			} else if (s[i] == 'n' && (i == (int)s.size() - 1 || isVowel(s[i + 1]) == false)) {
				mn += 1;
			}
		}
		for (auto i : s) {
			mx += (isVowel(i) || i == 'n');
		}

		cout << "Case " << T ++ << ": " << mn << " " << mx << "\n";
	}
}
