# Combining Images 

[Link](https://vjudge.net/contest/546122#problem/F)

## Description

For any $N\times N$ ($N=2^m$) image composed of $0$ or $1$, it can be encoded by the following way:

$$
f(Image) = \begin{cases}
"11" & \text{If it is composed of } 1 \text{ only} \\
"10" & \text{If it is composed of } 0 \text{ only} \\
"0" + f(UL) + f(UR) + f(BL) + f(BR) & \text{Otherwise} 
\end{cases}
$$

where "U" means upper and so does "DLR".

Given the encoded code of two images with the same shape, your task is to find the encoded code of their bitwise AND.

## Input Format

You will be given the hex representation of the codes.

## Output Format

You should output the hex representation of the encoding of their bitwises AND.

## Solution

Decode the two encoding together.

Remember to deal with the case that four area becomes all $0$.

## AC code

```cpp
#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

string RemoveFront(string x) {
	while (x.front() == '0') x = x.substr(1, (int)x.size() - 1);
	return x.substr(1, (int)x.size() - 1);
}

string HexToBin(string x) {
	string u = "";
	for (auto i : x) {
		int t = 0;
		if (isdigit(i)) t = i - '0';
		else t = i - 'A' + 10;

		string p = "";
		for (int _ = 0; _ < 4; ++ _) {
			p.push_back(t % 2 + '0');
			t >>= 1;
		}
		reverse(p.begin(), p.end());
		u += p;
	}
	return RemoveFront(u);
}

string BinToHex(string x) {
	x = "1" + x;
	while ((int)x.size() % 4 != 0) x = "0" + x;

	string u = "";
	for (int i = 0; i < (int)x.size(); i += 4) {
		int ret = 0;
		for (int j = i; j < i + 4; ++ j)
			ret = ret * 2 + x[j] - '0';
		if (ret <= 9) u.push_back(ret + '0');
		else u.push_back('A' + ret - 10);
	}
	return u;
}

string a, b;
int pa, pb;
string ans;

void Calc(string &s, int &p, bool f) {
	if (s[p] == '1') {
		if (f)
			ans += s.substr(p, 2);
		p += 2;
		return;
	} else {
		p += 1;
		if (f)
			ans += "0";
		for (int _ = 0; _ < 4; ++ _)
			Calc(s, p, f);
	}
}

void CalcAB() {
	if (a[pa] == '1' && b[pb] == '1') {
		if (a[pa + 1] == '1' && b[pb + 1] == '1')
			ans += "11";
		else
			ans += "10";
		pa += 2;
		pb += 2;
	} else if (a[pa] == '1') {
		if (a[pa + 1] == '1')
			Calc(b, pb, true);
		else {
			Calc(b, pb, false);
			ans += "10";
		}
		pa += 2;
	} else if (b[pb] == '1') {
		if (b[pb + 1] == '1')
			Calc(a, pa, true);
		else {
			Calc(a, pa, false);
			ans += "10";
		}
		pb += 2;
	} else {
		pa += 1, pb += 1;
		ans += "0";
		int now = (int)ans.size();
		for (int _ = 0; _ < 4; ++ _)
			CalcAB();
		
		if (now + 8 == (int)ans.size()) {
			if (ans.substr((int)ans.size() - 9, 9) == "010101010") {
				for (int _ = 0; _ < 9; ++ _)
					ans.pop_back();
				ans += "10";
			} else if (ans.substr((int)ans.size() - 9, 9) == "011111111") {
				for (int _ = 0; _ < 9; ++ _)
					ans.pop_back();
				ans += "11";
			}
		}
	}
}

int main() {
	int T = 1;
	while (cin >> a >> b && a != "0" && b != "0") {
		a = HexToBin(a); 
		b = HexToBin(b);

		pa = pb = 0;
		ans = "";
		CalcAB();
		
		ans = BinToHex(ans);

		if (T != 1) cout << "\n";
		cout << "Image " << T ++ << ":\n" << ans << "\n";
	}
}
```