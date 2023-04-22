# Island Hopping

[Link](https://vjudge.net/contest/538106#problem/E)

## Description

Given $n$ weighted points. The weight of $i$-th point is $m_i$.

One of the vertices is called main point.

You can build edges between any two points with their distance as the length.

Find a minimum spanning tree.

Let $t_i$ be the largest weight of the edges on the path from $i$-th vertex to main point on the MST.

Output $\dfrac{\sum t_i\times m_i}{\sum m_i}$。

## Input Format

$n\le 50$

$x_i, y_i, m_i$ integer.

$m_i > 0$

## Output Format

$\dfrac{\sum t_i\times m_i}{\sum m_i}$ rounded to two digits to the right of the decimal point.

## Solution

Any MST algorithm will do, while you can just use a modified version of Prim's algorithm as the code below.s

## AC code

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
#define F first
#define S second
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

int n;
vector<tuple<int, int, int>> v;
double w[100];

double dis(tuple<int, int, int> a, tuple<int, int, int> b) {
	auto [x1, y1, z1] = a;
	auto [x2, y2, z2] = b;
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t = 1;
	while (cin >> n && n) {
		v.resize(n);
		for (auto &[a, b, c] : v) cin >> a >> b >> c;
		
		fill(w, w + n, MOD);
		w[0] = 0;
		for (int _ = 1; _ < n; ++ _) {
			vector<double> u(n, MOD);
			for (int i = 0; i < n; ++ i) if (w[i] == MOD) {
				for (int j = 0; j < n; ++ j) if (w[j] != MOD) {
					u[i] = min(u[i], max(dis(v[i], v[j]), w[j]));
				}
			}
			int i = min_element(u.begin(), u.end()) - u.begin();
			w[i] = u[i];
		}
		
		double ans = 0;
		double s = 0;
		for (int i = 0; i < n; ++ i) {
			ans += w[i] * get<2>(v[i]);
			s += get<2>(v[i]);
		}
		cout << "Island Group: " << t << " Average ";
		cout << fixed << setprecision(2) << ans / s << "\n\n";
		t += 1;
	}
}
```

## Remark

One can prove whatever MST is built, the answer is consistent.

### Proof 1

Assume we know any two MST can transformed to each other by swapping edges one by one.

Then we only need to show swapping one edge has no influence on the answer.

Check differnt situations and one can see the correctness.

### Proof 2

Sort the weight of the edges in acsending order and make them unique. Let it be $w_1, w_2, \cdots , w_m$.

For any MST $T$.

We can use induction to show that we can construct the subgraph of $T$ induced by the edges with weight $w_1\sim w_k$ for any $k=1\sim m$ by Kruskal's algorithm.