#include<bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
#define X first
#define Y second
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef tuple<ll, ll, ll> line;
ll MOD = 1000000007LL;

ll ori(pll o, pll a, pll b) {
    return (a.X - o.X) * (b.Y - o.Y) - (b.X - o.X) * (a.Y - o.Y);
}
int Counterclockwise(vector<pll> &v) {
    ll sum = 0;
    for (int i = 0; i < (int)v.size(); ++ i)
        sum += ori(pll(0, 0), v[i], v[(i + 1) % (int)v.size()]);
    return (sum > 0);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

    int T = 1, h, c;
    while (cin >> h >> c && h) {
        vector<pll> hole(h);
        vector<pll> cover(c);
        for (auto &[a, b] : hole) cin >> a >> b;
        for (auto &[a, b] : cover) cin >> a >> b;

        if (!Counterclockwise(hole)) reverse(hole.begin(), hole.end());
        if (!Counterclockwise(cover)) reverse(cover.begin(), cover.end());

        vector<line> h_left, h_right;
        vector<line> c_left, c_right;
        for (int i = 0; i < h; ++ i) {
            int j = (i + 1) % h;
            if (hole[i].X == hole[j].X) {
                if (hole[i].Y < hole[j].Y)
                    h_right.push_back(line(hole[i].X, hole[i].Y, hole[j].Y));
                if (hole[i].Y > hole[j].Y)
                    h_left.push_back(line(hole[i].X, hole[j].Y, hole[i].Y));
            }
        }
        for (int i = 0; i < c; ++ i) {
            int j = (i + 1) % c;
            if (cover[i].X == cover[j].X) {
                if (cover[i].Y < cover[j].Y)
                    c_right.push_back(line(cover[i].X, cover[i].Y, cover[j].Y));
                if (cover[i].Y > cover[j].Y)
                    c_left.push_back(line(cover[i].X, cover[j].Y, cover[i].Y));
            }
        }

        vector<line> h_top, h_bottom;
        vector<line> c_top, c_bottom;
        for (int i = 0; i < h; ++ i) {
            int j = (i + 1) % h;
            if (hole[i].Y == hole[j].Y) {
                if (hole[i].X < hole[j].X)
                    h_bottom.push_back(line(hole[i].Y, hole[i].X, hole[j].X));
                if (hole[i].X > hole[j].X)
                    h_top.push_back(line(hole[i].Y, hole[j].X, hole[i].X));
            }
        }
        for (int i = 0; i < c; ++ i) {
            int j = (i + 1) % c;
            if (cover[i].Y == cover[j].Y) {
                if (cover[i].X < cover[j].X)
                    c_bottom.push_back(line(cover[i].Y, cover[i].X, cover[j].X));
                if (cover[i].X > cover[j].X)
                    c_top.push_back(line(cover[i].Y, cover[j].X, cover[i].X));
            }
        }

        vector<line> h_ver, h_hor;
        vector<line> c_ver, c_hor;
        if (h_left.size() * c_left.size() < h_right.size() * c_right.size()) {
            h_ver = h_left;
            c_ver = c_left;
        } else {
            h_ver = h_right;
            c_ver = c_right;
        }
        if (h_top.size() * c_top.size() < h_bottom.size() * c_bottom.size()) {
            h_hor = h_top;
            c_hor = c_top;
        } else {
            h_hor = h_bottom;
            c_hor = c_bottom;
        }

        auto CheckCover = [&](int delta_x, int delta_y) -> bool {
            vector<pair<line, int>> ver;
            for (auto &i : c_left) ver.push_back({i, 1});
            for (auto &i : c_right) ver.push_back({i, -1});
            for (auto &[x, y1, y2] : h_left) ver.push_back({{x + delta_x, y1 + delta_y, y2 + delta_y}, -1});
            for (auto &[x, y1, y2] : h_right) ver.push_back({{x + delta_x, y1 + delta_y, y2 + delta_y}, 1});
            
            vector<int> X, Y;
            for (auto &[a, b] : ver) {
                auto &[x, y1, y2] = a;
                Y.push_back(y1);
                Y.push_back(y2 - 1);
            }
            sort(Y.begin(), Y.end());
            Y.resize(unique(Y.begin(), Y.end()) - Y.begin());

            for (auto &[a, b] : ver) {
                auto &[x, y1, y2] = a;
                y1 = lower_bound(Y.begin(), Y.end(), y1) - Y.begin();
                y2 = lower_bound(Y.begin(), Y.end(), y2 - 1) - Y.begin();
            }

            sort(ver.begin(), ver.end(), [](pair<line, int> a, pair<line, int> b) {
                return get<0>(a.first) < get<0>(b.first) || (get<0>(a.first) == get<0>(b.first) && (a.second > b.second));
            });
            vector<int> seg((int)Y.size());
            for (auto &[a, b] : ver) {
                auto &[x, y1, y2] = a;
                for (int i = y1; i <= y2; ++ i) {
                    seg[i] += b;
                    if (seg[i] < 0)
                        return false;
                }
            }
            return true;
        };

        bool ok = false;
        for (auto &i : h_ver)
            for (auto &j : c_ver)
                for (auto &k : h_hor)
                    for (auto &l : c_hor)
                        ok |= CheckCover(get<0>(j) - get<0>(i), get<0>(l) - get<0>(k));

        if (ok)
            cout << "Hole " << T ++ << ": Yes" << endl;
        else
            cout << "Hole " << T ++ << ": No" << endl;
    }
}