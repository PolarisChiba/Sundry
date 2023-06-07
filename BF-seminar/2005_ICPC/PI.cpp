#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T = 1;
	int w, r;
	while (cin >> w && w) {
		vector<pair<int, int>> work(w);
		for (auto &[a, b] : work)
			cin >> b >> a;
		cin >> r;
		vector<pair<int, int>> room(r);
		for (auto &[a, b] : room) {
			string s;
			cin >> b >> s;
			a = (stoi(s.substr(0, 2)) - 14) * 60 + stoi(s.substr(3, 2));
		}
		
		sort(room.begin(), room.end());
		sort(work.begin(), work.end(), greater<pair<int, int>>());
		multiset<int> s;
		for (auto &[a, b] : room) {
			while (!work.empty() && work.back().first <= a) {
				s.insert(work.back().second);
				work.pop_back();
			}
			auto it = s.upper_bound(b);
			if (it != s.begin()) {
				s.erase(-- it);
			}
		}
		
		int sum = 0;
		for (auto i : s)
			sum += i;
		for (auto [a, b] : work)
			sum += b;

		cout << "Trial " << T << ": " << (int)s.size() + (int)work.size() << " " << sum << "\n\n";
		T += 1;
	}
}