#include <bits/stdc++.h>
using namespace std;

using LL = long long;

LL modMul(LL a, LL b, LL m) { return __int128{a} * b % m; }
LL pow(LL a, LL b, LL m) {
  LL ret = 1;
  for (; b; a = modMul(a, a, m), b >>= 1)
    if (b % 2)
      ret = modMul(ret, a, m);
  return ret;
}
bool isPrime(LL n) {
  LL sprp[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  if (n == 2)
    return true;
  if (n < 2 || n % 2 == 0)
    return false;
  LL t = 0, u = n - 1;
  for (; u % 2 == 0; t++)
    u >>= 1;
  for (int i = 0; i < 7; i++) {
    LL a = sprp[i] % n;
    if (a == 0 || a == 1 || a == n - 1)
      continue;
    LL x = pow(a, u, n);
    if (x == 1 || x == n - 1)
      continue;
    for (int j = 1; j < t; j++) {
      x = modMul(x, x, n);
      if (x == 1)
        return false;
      if (x == n - 1)
        break;
    }
    if (x == n - 1)
      continue;
    return false;
  }
  return true;
}

inline LL f(LL x, LL mod) { return (modMul(x, x, mod) + 1) % mod; }
inline LL pollard_rho(LL n) {
  if (!(n & 1))
    return 2;
  while (true) {
    LL y = 2, x = rand() % (n - 1) + 1, res = 1;
    for (int sz = 2; res == 1; sz *= 2) {
      for (int i = 0; i < sz && res <= 1; i++) {
        x = f(x, n);
        res = __gcd(abs(x - y), n);
      }
      y = x;
    }
    if (res != 0 && res != n)
      return res;
  }
}

void factorize(LL n, vector<LL> &ans) {
  if (n == 1)
    return;
  if (isPrime(n))
    ans.push_back(n);
  else {
    auto p = pollard_rho(n);
    factorize(p, ans);
    factorize(n / p, ans);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int q;
  cin >> q;
  while (q--) {
    LL k;
    cin >> k;

    if (k == 0) {
      cout << "Peace TeTe\n";
      continue;
    }

    assert(0 <= k and k <= 1'000'000'000'000'000'000);
    auto p = vector<LL>{};
    factorize(k, p);

    long long res = 1;
    for (auto i : p)
      res *= i;
    assert(k == res);

    for (auto i : p)
      assert(isPrime(i));

    map<LL, int> cnt;
    for (auto &v : p)
      cnt[v] += 1;

    int tmp = 0;
    for (auto &i : cnt)
      tmp ^= i.second;

    if (tmp != 0) {
      cout << "Eillo\n";
    } else {
      cout << "Aleak\n";
    }
  }
}
