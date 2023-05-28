#include<bits/stdc++.h>
using namespace std;

bool isVowel(char c) {
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
	ios::sync_with_stdio(0); cin.tie();

	int T = 1;
	char c = ' ';
	while ((c = getchar()) != EOF) {
		string s = "";
		while (c != '\n') {
			s.push_back(c);
			c = getchar();
		}
		stringstream s_stream(s);
		int mx = 0, mn = 0;
		while (s_stream >> s) {
			for (int i = 0; i < (int)s.size(); ++ i) {
				if (isVowel(s[i]))
					mn += 1;
				else if (s[i] == 'n' && (i == (int)s.size() - 1 || isVowel(s[i + 1]) == false))
					mn += 1;
			}
			for (auto i : s)
				mx += (isVowel(i) || i == 'n');
		}
		
		cout << "Case " << T ++ << ": " << mn << " " << mx << "\n";
	}
}
