#include<bits/stdc++.h>
using namespace std;

struct schedual {
	int f[2][2];
	bool done;
	schedual() {
		fill_n(&f[0][0], 4, 0);
		done = false;
	}
	bool first_push(int x) {
		if (!done) {
			f[0][0] = 0;
			f[1][0] = -1e9;
			f[0][1] = -1e9;
			f[1][1] = x;
			done = true;
			return true;
		}
		return false;
	}
	void push_back(int x) {
		if (first_push(x)) 
			return;
		
		int u[2][2];
		for (int i = 0; i < 4; ++ i)
			u[i / 2][i % 2] = f[i / 2][i % 2];
		f[0][0] = max(u[0][0], u[0][1]);
		f[0][1] = u[0][0] + x;
		f[1][0] = max(u[1][0], u[1][1]);
		f[1][1] = u[1][0] + x;
	}
	void push_front(int x) {
		if (first_push(x)) 
			return;
		
		int u[2][2];
		for (int i = 0; i < 4; ++ i)
			u[i / 2][i % 2] = f[i / 2][i % 2];
		f[0][0] = max(u[0][0], u[1][0]);
		f[0][1] = max(u[0][1], u[1][1]);
		f[1][0] = x + u[0][0];
		f[1][1] = x + u[0][1];
	}
	int query() {
		return max({f[0][0], f[0][1], f[1][0], f[1][1]});
	}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	schedual iroyok;

	int n;
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		int x;
		cin >> x;
		iroyok.push_back(x);
	}

	int q;
	cin >> q;
	while ( q -- ) {
		string op;
		int x;
		cin >> op >> x;
		if (op == "f")
			iroyok.push_front(x);
		else
			iroyok.push_back(x);
		cout << iroyok.query() << "\n";
		assert(iroyok.query() > 0);
	}
}