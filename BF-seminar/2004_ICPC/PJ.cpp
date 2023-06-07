// the problem statement is ambiguous
#include <bits/stdc++.h>
#define X first
#define Y second
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef pair<double, double> pdd;

const double eps = 0.00001;

pdd operator+(const pdd &a, const pdd &b)
{ return pdd(a.X + b.X, a.Y + b.Y); }
pdd operator-(const pdd &a, const pdd &b)
{ return pdd(a.X - b.X, a.Y - b.Y); }
pdd operator*(const pdd &a, double b)
{ return pdd(a.X * b, a.Y * b); }
pdd operator/(const pdd &a, double b)
{ return pdd(a.X / b, a.Y / b); }
double dot(const pdd &a, const pdd &b)
{ return a.X * b.X + a.Y * b.Y; }
double abs2(const pdd &a)
{ return dot(a, a); }
double abs(const pdd &a)
{ return sqrt(dot(a, a)); }
int sign(const double &a)
{ return fabs(a) < eps ? 0 : a > 0 ? 1 : -1; }


pair<pdd, double> circenter(pdd p0, pdd p1, pdd p2) {
	p1 = p1 - p0, p2 = p2 - p0;
	double x1 = p1.X, y1 = p1.Y, x2 = p2.X, y2 = p2.Y;
	double m = 2.0 * (x1 * y2 - y1 * x2);
	if (sign(m) == 0) {
		return {pdd(0, 0), -1};
	}
	pdd center;
	center.X = (x1 * x1 * y2 - x2 * x2 * y1 + y1 * y2 * (y1 - y2)) / m;
	center.Y = (x1 * x2 * (x2 - x1) - y1 * y1 * x2 + x1 * y2 * y2) / m;
	return {center + p0, abs(center)};
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int T = 1;
	int np, nc;
	while (cin >> np >> nc && np) {
		vector<pdd> airplanes(np);
		for (auto &[x, y] : airplanes)
			cin >> x >> y;
		sort(airplanes.begin(), airplanes.end(), [](pdd a, pdd b) {
			return a.Y > b.Y || (a.Y == b.Y && a.X > b.X);
		});
		vector<int> cnt(np);
		bool ok = true;
		for (int _ = 0; _ < nc; ++ _) {
			int num;
			pdd p1, p2;
			cin >> num >> p1.X >> p1.Y >> p2.X >> p2.Y;
			assert(p1 != p2);
			
			double R = -1;
			vector<bool> chk(np, false);
			
			auto Check = [&](pdd center, double r) -> void {
				vector<bool> buf(np, false);
				int res = 0, ret = 0;
				for (int i = 0; i < np; ++ i) {
					auto &p = airplanes[i];
					double d = abs(p - center);
					if (d < r - eps) {
						res += 1;
						ret += 1;
						buf[i] = true;
					} else if (d < r + eps) {
						ret += 1;
					}
				}
				if (res <= num && num <= ret) {
					int tmp = num - res;
					for (int i = 0; i < np; ++ i) {
						auto &p = airplanes[i];
						double d = abs(p - center);
						if (r - eps <= d && d <= r + eps && tmp) {
							buf[i] = true;
							tmp -= 1;
						}
					}
					bool f = true;
					for (int i = 0; i < np; ++ i) {
						if (chk[i] && !buf[i]) {
							f = false;
							break;
						}
						if (!chk[i] && buf[i]) {
							f = true;
							break;
						}
					}
					if (R < 0 || r < R - eps || (r < R + eps && f)) {
						R = r;
						chk = buf;
					}
				}
			};
			
			for (auto p : airplanes) {
				auto [center, r] = circenter(p, p1, p2);
				if (r == -1)
					continue;
				Check(center, r);
			}
			
			if (R == -1) {
				ok = false;
				continue;
			}
			for (int i = 0; i < np; ++ i)
				cnt[i] += chk[i];
		}

		cout << "Trial " << T ++ << ":  ";
		if (ok == false) {
			cout << "Impossible";
		} else {
			vector<int> ans(nc + 1);
			for (int i = 0; i < np; ++ i) {
				ans[cnt[i]] += 1;
			}
			for (int i = 0; i <= nc; ++ i) {
				cout << ans[i];
				if (i != nc)
					cout << "  ";
			}
		}
		cout << "\n\n";
	}
}