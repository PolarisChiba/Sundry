# The Solar System 

[Link](https://vjudge.net/contest/546122#problem/I)

## Description

There are two planet $p_1$ and $p_2$ orbiting the same focus.

The ellipses of their orbits are centered at $(0, 0)$, and their focus are on nonnegative $x$-axis.

Given semimajor $a_1$, semiminor of $b_1$, and period $t_1$ of $p_1$.

Given semiminor $a_2$ and semiminor $b_2$ of $p_2$.

Given time $t$.

Find the position of $p_2$ at time t.

## Input

$a_1, b_1, t_1, a_2, b_2, t$ integer

## Output

The position of $p_2$ at $t$ with $3$ digits to the right of the decimal.

## Solution

Let $t_2$ be the period of $p_2$.

According to the 2nd Kepler's law, $t_2=t_1\times (\frac{a_2}{a_1})^{\frac{3}{2}}$.

Let $t'$ be $t\bmod t_2$ to deal with the case with more than one period $p_2$ orbits.

Compare $\frac{t'}{t_2}$ with $0.5$ to see the position is on upper part or lower part.

Binary search $x$-coordinate of the position by calculating the area $p_2$ travels to there and compare it with the area of the whole ellipse.

The ellipse area $=\pi\times a_2\times b_2$.

Calculating the partial area needs some formula.

Time complexity: $O(\log{a_2\times 2 \times 10^7})$ where $10^9$ is for precision.

## AC code

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
#define X first
#define Y second
#define double long double
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

const double eps = 1e-8;
const double pi = acos(-1);

double a1, b1, t1, a2, b2, t;

double det(vector<vector<double>> m) {
	double res = 0;
	for (int i = 0; i < 3; ++ i) {
		double ret = 1;
		for (int j = 0; j < 3; ++ j)
			ret *= m[j][(j + i) % 3];
		res += ret;
	}
	for (int i = 0; i < 3; ++ i) {
		double ret = 1;
		for (int j = 0; j < 3; ++ j)
			ret *= m[j][(2 - j + i) % 3];
		res -= ret;
	}
	return res;
}
double Area2(double r1, double r2, double a1, double a2, double b1, double b2, double c1, double c2) {
	vector<vector<double>> m1 = {{1, 0, 0}, {1, b1, b2}, {1, c1, c2}};
	vector<vector<double>> m2 = {{1, a1, a2}, {1, b1, b2}, {1, c1, c2}};
	return (r1 * r2 * acos((b1 * c1) / (r1 * r1) + (b2 * c2) / (r2 * r2)) - det(m1) + det(m2));
}

int main() {
	int T = 1;
	while (cin >> a1 >> b1 >> t1 >> a2 >> b2 >> t && (a1 || b1 || t1 || a2 || b2 || t)) {
		double t2 = t1 * a2 * sqrt(a2 / a1) / a1;
		t = fmod(t, t2);
		double A = pi * a2 * b2;
		double c = sqrt(a2 * a2 - b2 * b2);

		bool neg = false;
		if (t2 <= t * 2) {
			neg = true;
			t = t - t2 / 2;
			c = -c;
		}

		double L = -a2, R = a2;
		while (R - L > 1e-9) {
			double x = L + (R - L) / 2.0;
			double y = b2 * sqrt(1 - x * x / a2 / a2);
			if (t2 * Area2(a2, b2, c, 0, a2, 0, x, y) > A * t * 2.0)
				L = x;
			else
				R = x;
		}

		double x = R;
		double y = b2 * sqrt(1 - x * x / a2 / a2);
		x = round(x * 1000) / 1000.0;
		y = round(y * 1000) / 1000.0;
		if (neg) {
			x = -x;
			y = -y;
		}
		cout << "Solar System " << T++ << ": " << fixed << setprecision(3) << x << " " << y << endl;
	}
}
```