# Ferries 

[Link](https://vjudge.net/contest/538106#problem/D)

## Description

There's a route composed of $s$ sections. Each section may be road or river.

At first, it's 00:00:00 time. You want to complete the route.

You can drive car to pass the roads while your velocity can't exceed $80$ km/h.

You can take ferry to cross the rivers.

For the $i$-th river, there will be $f$ ferries. You can take the $j$-th ferry at $t_j$ moment per clock. It will take you $K_i$ time to cross the $i$-th river.

For example, $t_j = 10$ then you can take the $j$-th ferry of the $i$-th river at 00:10, 01:10, 02:10 ( hr:min ) periodically.

Even though you may arrive earlier, you still have to want for the next ferry.

Calculate the minimum time needed to complete the route and the minimum possible value of the maximum velocity on each road to reach the minimum time.

## Remark

It's guaranteed the minimum time needed doesn't exceed 10 hr.

## Input Format

$s > 0$

$t_j, K_i$ are given in minute.

The road length is given in km.

## Output Format

The minimum time needed in hr:min:sec format.

The minimum possible value of the maximum velocity on each road, rounded to two digit to the right of the decimal point.

## Solution

We can just drive at 80km/hr on each road to get the minimum time needed.

It's also clear that we'll complete the route earlier if driving faster.

Hence, binary search the least velocity needed.

However, there's a problem in binary search. 

The case $L=4.444\overline{999}$ and $R=4.445\overline{000}$. After rounding the former will be $4.44$ while the latter $4.45$.

It's caused by round-off error.

The proper way to do this is checking whether $L+\epsilon$ and $R+\epsilon$ are the same after rounding while $\epsilon$ is some little number.

## Time complexity

Binary search takes $O(80\times C)$ while $C$ depends on the precision.

We need $O(s+\sum f)$ to calculate the time needed.

$O(80\times C\times (s+\sum f))$ in total.

## Remark

One have to combine all the continuse roads together or there will be precision problem.

Notice that under 80km/hr, the consuming time will be integer with respect to second.

## AC code

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
#define F first
#define S second
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

const double eps = 1e-8;

int n;
vector<ll> v;
vector<vector<ll>> w;

ll Calc(double x) {
	ll now = 0;
	for (int i = 0; i < n; ++ i) {
		if (w[i].empty()) {
			if (x < 1e-6) return MOD;
			now += ceil(1.0 * v[i] / x);
		} else {
			ll res = now % 3600;
			if (res > w[i].back()) {
				now = now - res + w[i].front() + 3600;
			} else {
				for (auto j : w[i]) {
					if (res <= j) {
						now = now - res + j;
						break;
					}
				}
			}
			now += v[i];
		}
	}
	return now;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t = 1;
	while (cin >> n && n) {
		v.clear();
		w.clear();
		int pre = -1;
		for (int i = 0; i < n; ++ i) {
			string a, b, c;
			int z;
			cin >> a >> b >> c >> z;
			if (c == "ferry") {
				pre = -1;
				int x;
				cin >> x;
				v.push_back(z * 60);
				w.push_back(vector<ll>(x));
				for (auto &j : w.back()) cin >> j, j *= 60;
			} else {
				if (pre == 1) v.back() += z * 3600;
				else v.push_back(z * 3600), w.push_back(vector<ll>(0));
				pre = 1;
			}
		}
		n = (int)v.size(); 
		
		ll mn = Calc(80);
		double L = 0.00;
		double R = 80.00;
		while (round((R + eps) * 100) != round((L + eps) * 100)) {
			double mid = (R + L) / 2.0;
			if (mn == Calc(mid)) R = mid;
			else L = mid;
		}
		if (Calc(0) == mn) R = 0;
		
		cout << "Test Case " << t << ": ";
		cout << setw(2) << setfill('0') << mn / 3600 << ":";
		cout << setw(2) << setfill('0') << mn % 3600 / 60 << ":";
		cout << setw(2) << setfill('0') << mn % 60 << " ";
		cout << fixed << setprecision(2) << R << "\n\n";
		
		t += 1;
	}
}
```

## Other solution

First one can see if the last section is road then the velocity needed is 80km/hr.

Hence we can consider the case the last section is ferry only.

Notice only departure time of each ferry of each hour is important, since we have to wait if arriving early and the time we cross the river is determined by that as well.

Hence, for each time we calculate the least maximum velocity we need by dynamic programming.

Formally, $f(i, j, k)$ means the answer to $i$-th river, $j$ hour, and $k$-th ferry.

Then iterate all $f(i + 1, 0\sim 9, 0\sim ferry[i+1].size())$, and use the length of the $i+1$-th road to update $f(i, j, k)$.

Time complexity: 
* Input: $O(s+\sum f)$
* Calculate minimum time needed: $O(s+\sum \log{f})$
* Initial dp array: $O(10\times \sum f + \log{f_{n-1}})$
* Calculate dp: $O(10^2\times \sum (f_i\times f_{i+1}))$
* Get answer to least velocity needed: $O(10\times f_{0})$

$O(s+ 10^2\times\sum (f_i\times f_{i+1}))$ in total.


## AC code

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

int n;
vector<int> road; // length of each road
vector<int> cross; // crossing time for ferry
vector<vector<int>> ferry; // time ferry arrives
vector<vector<double>> velocity; 
int min_time;

void Clear() {
	road.clear();
	cross.clear();
	ferry.clear();
	min_time = 0;
}
void Input() {
	road.push_back(0);
	bool pre = false; // false for road and true for ferry

	while ( n -- ) {
		string a, b, c;
		int r;
		cin >> a >> b >> c >> r;
		if (c == "road") {
			if (pre == false) road.back() += r;
			else road.push_back(r), pre = false;
		} else {
			if (pre == true) road.push_back(0);
			int k;
			cin >> k;
			cross.push_back(r);
			ferry.push_back(vector<int>(k));
			for (auto &i : ferry.back()) cin >> i;
			pre = true;
		}
	}
	n = (int)road.size();
}
void CalcMinTime() {
	for (int i = 0; i < n; ++ i) {
		min_time += road[i] * 3600 / 80;

		if ((int)ferry.size() > i) {
			int min_level = (min_time / 60 % 60) + (min_time % 60 != 0);
			auto it = lower_bound(ferry[i].begin(), ferry[i].end(), min_level);
			if (it == ferry[i].end()) {
				min_time += 3600;
				it = ferry[i].begin();
			}
			min_time = (min_time / 3600) * 3600 + (*it) * 60 + cross[i] * 60;
		}
	}
}
int id(int i, int j) { // i hr j-th ferry
	return j * 10 + i;
}
double CalcVelocity() {
	velocity.resize(n);
	for (int i = 0; i < n; ++ i)
		velocity[i].assign((int)ferry[i].size() * 10, 80);

	int res = ((min_time - cross.back() * 60) / 60) % 60;
	int it = lower_bound(ferry.back().begin(), ferry.back().end(), res) - ferry.back().begin();
	velocity[n - 1][id((min_time - cross.back() * 60) / 3600, it)] = 0;

	for (int i = n - 2; i >= 0; -- i) {
		for (int j = 0; j < 10; ++ j) {
			for (int k = j; k < 10; ++ k) {
				for (int a = 0; a < (int)ferry[i].size(); ++ a) {
					for (int b = 0; b < (int)ferry[i + 1].size(); ++ b) {
						int p = j * 60 + ferry[i][a] + cross[i];
						int q = k * 60 + ferry[i + 1][b];
						if (p > q) continue;

						if (road[i + 1] != 0 && p != q)
							velocity[i][id(j, a)] = min(velocity[i][id(j, a)], max(velocity[i + 1][id(k, b)], 60.0 * road[i + 1] / (q - p)));
						else if (road[i + 1] == 0)
							velocity[i][id(j, a)] = min(velocity[i][id(j, a)], velocity[i + 1][id(k, b)]);
					}
				}
			}
		}
	}
	double ans = 80;
	for (int i = 0; i < 10; ++ i) {
		for (int j = 0; j < (int)ferry[0].size(); ++ j) {
			if (road[0] != 0 && i * 60 + ferry[0][j] != 0)
				ans = min(ans, max(velocity[0][id(i, j)], 60.0 * road[0] / (i * 60 + ferry[0][j])));
			else if (road[0] == 0)
				ans = min(ans, velocity[0][id(i, j)]);
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int _ = 1;
	while (cin >> n && n) {
		Clear();
		Input();
		CalcMinTime();

		double min_v = 80.00;
		if (ferry.size() == road.size())
			min_v = CalcVelocity();
		
		cout << "Test Case " << _ ++ << ": ";
		cout << setw(2) << setfill('0') << min_time / 3600 << ":";
		cout << setw(2) << setfill('0') << min_time / 60 % 60 << ":";
		cout << setw(2) << setfill('0') << min_time % 60 << " ";
		cout << fixed << setprecision(2) << min_v << "\n\n";
	}
}
```