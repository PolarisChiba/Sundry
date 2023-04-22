# Riding the Bus 

[Link](https://vjudge.net/contest/546122#problem/C)

## Description

TBD

## Input

The order and the two positions.

## Output

The distance.

## Solution

Recursively calculate and "苦工".

## AC code

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
#define X first
#define Y second
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

const double eps = 1e-8;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef pair<bool, bool>pbb;

ll len[10];
ll sum[10];
vector<pll> sz_ord[2][2];
vector<pbb> sz_rev[2][2];

double Distance(pdd a, pll b) { return sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y)); }

pll CurrentPoint(pdd p) { 
	return pll((ll)round(p.X - eps), (ll)round(p.Y - eps)); 
}

ll NumberOfLen(int r, pll p, pbb rev = pbb(false, false)) {
	auto &order = sz_ord[rev.X][rev.Y];

	if (r == 0) {
		for (int i = 0; i < 9; ++ i) {
			if (p == order[i])
				return i;
		}
	}

	for (int i = 0; i < 9; ++ i) {
		ll B = order[i].X * (len[r - 1] + 1);
		ll U = B + len[r - 1];
		ll L = order[i].Y * (len[r - 1] + 1);
		ll R = L + len[r - 1];

		if (B <= p.X && p.X <= U && L <= p.Y && p.Y <= R) {
			return sum[r - 1] * i + NumberOfLen(r - 1, pll(p.X - B, p.Y - L), sz_rev[rev.X][rev.Y][i]);
		}
	}
	assert(false);
}

int main() {
	len[0] = 2;
	for (int i = 1; i <= 7; ++ i) len[i] = len[i - 1] * 3 + 2;
	sum[0] = 9;
	for (int i = 1; i <= 7; ++ i) sum[i] = sum[i - 1] * 9;
	
	sz_ord[0][0] = sz_ord[0][1] = vector<pll>{pll(0, 0), pll(0, 1), pll(0, 2), pll(1, 2), pll(1, 1), pll(1, 0), pll(2, 0), pll(2, 1), pll(2, 2)};
	sz_ord[1][0] = sz_ord[1][1] = vector<pll>{pll(0, 2), pll(0, 1), pll(0, 0), pll(1, 0), pll(1, 1), pll(1, 2), pll(2, 2), pll(2, 1), pll(2, 0)};
	reverse(sz_ord[0][1].begin(), sz_ord[0][1].end());
	reverse(sz_ord[1][1].begin(), sz_ord[1][1].end());

	sz_rev[0][0] = sz_rev[0][1] = vector<pbb>{pbb(0, 0), pbb(1, 1), pbb(0, 0), pbb(1, 0), pbb(0, 1), pbb(1, 0), pbb(0, 0), pbb(1, 1), pbb(0, 0)};
	sz_rev[1][0] = sz_rev[1][1] = vector<pbb>{pbb(1, 0), pbb(0, 1), pbb(1, 0), pbb(0, 0), pbb(1, 1), pbb(0, 0), pbb(1, 0), pbb(0, 1), pbb(1, 0)};
	reverse(sz_rev[0][1].begin(), sz_rev[0][1].end());
	reverse(sz_rev[1][1].begin(), sz_rev[1][1].end());
	for (auto &[a, b] : sz_rev[0][1]) b ^= 1;
	for (auto &[a, b] : sz_rev[1][1]) b ^= 1;
	
	int T = 1, r;
	while ( cin >> r && r ) {
		r -= 1;

		pdd a, b;
		cin >> a.Y >> a.X >> b.Y >> b.X;

		a.X *= len[r];
		a.Y *= len[r];
		b.X *= len[r];
		b.Y *= len[r];

		pll A = CurrentPoint(a);
		pll B = CurrentPoint(b);

		ll IdA = NumberOfLen(r, A);
		ll IdB = NumberOfLen(r, B);

		double ans = (Distance(a, A) + Distance(b, B) + abs(IdA - IdB)) * 1.0 / len[r];
		ans = round(ans * 10000) / 10000.0;

		if (T != 1) cout << endl;
		cout << "Case " << T ++ << ".  Distance is " << fixed << setprecision(4) << ans << endl;
	}
}
```