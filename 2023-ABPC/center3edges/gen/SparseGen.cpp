#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// 0-based
vector<pair<int, int>> RandomTree(int n) {
    vector<pair<int, int>> v;

    vector<int> t;
    set<int> s;
    multiset<int> tt;
    for (int i = 1; i <= n - 2; ++ i) t.push_back(rnd.next(0, n - 1));
    for (int i = 0; i < n; ++ i) s.insert(i);
    for (auto i : t) {
        if (s.find(i) != s.end()) s.erase(s.find(i));
        tt.insert(i);
    }
    for (auto i : t) {
        auto it = s.begin();
        v.push_back({*it, i});
        s.erase(it);
        tt.erase(tt.find(i));
        if (tt.find(i) == tt.end())
            s.insert(i);
    }
    v.push_back({*s.begin(), *s.rbegin()});
    return v;
}

// 0-based
vector<pair<int, int>> RandomSparseConnectedGraph(int n, int m) {
    // n - 1 <= m

    auto v = RandomTree(n);
    set<pair<int, int>> s;
    for (auto i : v) s.insert(i);

    while ((int)v.size() < m) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 1);
        if (a == b || s.find({a, b}) != s.end() || s.find({b, a}) != s.end()) continue;
        
        v.push_back({a, b});
        s.insert({a, b});
    }
    return v;
}

vector<int> CountFactor(int n) {
    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; ++ i)
        for (int j = i; j <= n; j += i)
            cnt[j] += 1;
    return cnt;
}

int main(int argc, char* argv[]) {

    registerGen(argc, argv, 1);

    int n = opt<int>(1);
    int m = opt<int>(2);
    int c = opt<int>(3);
    
    auto v = RandomSparseConnectedGraph(n, m);
    auto cnt = CountFactor(10'000);

    auto x = vector<int>(10'000);
    iota(x.begin(), x.end(), 1);
    sort(x.begin(), x.end(), [&](int a, int b) {
        return cnt[a] > cnt[b];
    });
    x.resize(c);

    println(n, m);
    for (auto [a, b] : v) println(a + 1, b + 1, rnd.any(x));
}

