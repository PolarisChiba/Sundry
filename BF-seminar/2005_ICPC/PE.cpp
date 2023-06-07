#include <bits/stdc++.h>
#define X first
#define Y second
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

const double pi = acos(-1);

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T = 1;
	int n;
	while (cin >> n && n) {
		double w, h;
		cin >> w >> h;
		vector<double> m(n), d(n);
		for (int i = 0; i < n; ++ i) {
			cin >> m[i];
			if (i < n - 1) {
				cin >> d[i + 1];
				d[i + 1] += d[i];
			}
		}
		cout << "Apartment Complex: " << T ++ << "\n\n";
		int q;
		while (cin >> q && q) {
			int id = q % 100 - 1, num = q / 100;
			if ((0 <= id && id < n) == false || (1 <= num && num <= m[id]) == false) {
				cout << "Apartment " << q << ": Does not exist\n\n";
				continue;
			}

			double L = pi, R = 0;
			for (int i = 0; i < id; ++ i) {
				if (m[i] < num)
					continue;
				double x = -((id - i - 1) * w + d[id] - d[i]);
				double y = (m[i] - num + 1) * h;
				double ang = acos(x / hypot(x, y));
				L = min(L, ang);
			}
			for (int i = id + 1; i < n; ++ i) {
				if (m[i] < num)
					continue;
				double x = (i - id - 1) * w + d[i] - d[id];
				double y = (m[i] - num + 1) * h;
				double ang = acos(x / hypot(x, y));
				R = max(R, ang);
			}

			double tot = ((7 + 6) * 60 - 37 + 17) * 60;
			int st = floor(tot * (pi - L) / pi) + 5 * 60 * 60 + 37 * 60;
			int ed = floor(tot * (pi - R) / pi) + 5 * 60 * 60 + 37 * 60;

			auto output = [](int time, string s) -> void {
				cout << setw(2) << setfill('0');
				cout << time / 3600 << ":";
				cout << setw(2) << setfill('0');
				cout << time / 60 % 60 << ":";
				cout << setw(2) << setfill('0');
				cout << time % 60;
				cout << s;
			};

			cout << "Apartment " << q << ": ";
			output(st, " - ");
			output(ed, "\n\n");
		}
	}
}