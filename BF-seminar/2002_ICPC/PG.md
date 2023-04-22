# Partitions

[Link](https://vjudge.net/contest/538106#problem/G)

## Description

A partition of a rectangle is a subdivision of the rectangle into a set of smaller, non-overlapping sub-rectangles.

Given two partition of $w\times h$ rectangles $A$, $B$.

Find the minimum partition that includes both $A$ and $B$.

Find the maximum partition that belongs to both $A$ and $B$.

## Input Format

$0 < w, h\le 20$

The partition is given in ```'|'``` and ```'_'```.

## Output Format

As description mentions.

## Solution

The union of $A$ and $B$ is obvious.

For the other one, find the intersection of $A$ and $B$ first.

Then brute force to remove the invalid edges one by one. This will lead to $O((wh)^2)$ complexity.

On the other hand, we can find 'some' invalid edges in $O(wh)$ time.

Then for each invalid edge found, do dfs to delete 'all' invalid edges. This lead to $O(wh)$ complexity in total.

## AC code

The code below is just brute force to delete the edges.

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
#define X first
#define Y second
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

typedef pair<double, double> pdd;

int w, h;
string a[50], b[50];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int T = 1;
	while (cin >> w >> h && w) {
		for (int i = 0; i < h + 1; ++ i)
			a[i] = b[i] = string(2 * w + 1, ' ');
		
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		for (int i = 0; i < h + 1; ++ i) {
			string s = "";
			getline(cin, s, '\n');
			if (i == 0 && s.back() != ' ') s.push_back(' ');

			for (int j = 0; j < 2 * w + 1; ++ j) {
				if (s[j] != ' ') a[i][j] = s[j];
				if (s[j + 2 * w + 2] != ' ') a[i][j] = s[j + 2 * w + 2];
				if (s[j] != ' ' && s[j + 2 * w + 2] != ' ')
					b[i][j] = s[j];
			}
		}
		while (true) {
			bool ok = false;
			for (int i = 1; i <= h; ++ i) {
				for (int j = 2; j <= 2 * w - 2; j += 2) {
					if (b[i][j] != ' ' && b[i - 1][j] == ' ' && (b[i - 1][j - 1] == ' ' || b[i - 1][j + 1] == ' '))
						b[i][j] = ' ', ok = true;
				}
			}
			for (int i = h; i >= 1; -- i) {
				for (int j = 2; j <= 2 * w - 2; j += 2) {
					if (b[i][j] != ' ' && (i == h || b[i + 1][j] == ' ') && (b[i][j - 1] == ' ' || b[i][j + 1] == ' '))
						b[i][j] = ' ', ok = true;
				}
			}
			for (int j = 1; j <= 2 * w - 1; j += 2) {
				for (int i = 1; i <= h - 1; ++ i) {
					if (b[i][j] != ' ' && (j == 1 || b[i][j - 2] == ' ') && (b[i][j - 1] == ' ' || b[i + 1][j - 1] == ' '))
						b[i][j] = ' ', ok = true;
				}
			}
			for (int j = 2 * w - 1; j >= 1; j -= 2) {
				for (int i = 1; i <= h - 1; ++ i) {
					if (b[i][j] != ' ' && (j == 2 * w - 1 || b[i][j + 2] == ' ') && (b[i][j + 1] == ' ' || b[i + 1][j + 1] == ' '))
						b[i][j] = ' ', ok = true;
				}
			}
			if (!ok) break;
		}

		cout << "Case " << T ++ << ":\n";
		for (int i = 0; i < h + 1; ++ i) {
			for (auto j : a[i]) assert((int)j != 13);
			for (auto j : b[i]) assert((int)j != 13);

			cout << a[i] + " " + b[i] << "\n";
		}
		cout << "\n";
	}
}
```