#include<bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef long long ll;

const int bias = 1700 * 10000;
int date_to_time[5000000];
int time_to_date[5000000];
int month_day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool LeapYear(int x) {
    return (x % 400 == 0) || (x % 100 != 0 && x % 4 == 0);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

    int now = 0;
    for (int i = 1700; i <= 2100; ++ i) {
        if (LeapYear(i)) month_day[2] = 29;
        else month_day[2] = 28;

        for (int j = 1; j <= 12; ++ j) {
            for (int k = 1; k <= month_day[j]; ++ k) {
                date_to_time[i * 10000 + j * 100 + k - bias] = ++ now;
                time_to_date[now] = i * 10000 + j * 100 + k - bias;
            }
        }
    }

    int nx, nr, T = 1;
    while (cin >> nx >> nr && (nx || nr)) {
        vector<pair<int, ll>> v;
        for (int i = 0; i < nx; ++ i) {
            int a, b;
            cin >> a >> b;
            v.push_back({date_to_time[a - bias], 1e9});
            v.push_back({date_to_time[b - bias] + 1, -1e9});
        }
        for (int i = 0; i < nr; ++ i) {
            int a, b;
            cin >> a >> b;
            v.push_back({date_to_time[a - bias], -1});
            v.push_back({date_to_time[b - bias] + 1, 1});
        }

        sort(v.begin(), v.end());
        ll sum = 0;
        vector<pair<int, int>> ans;
        for (int i = 0; i < (int)v.size(); ++ i) {
            // cout << v[i].first << " " << v[i].second << "\n";
            sum += v[i].second;
            if (i == (int)v.size() - 1 || v[i].first != v[i + 1].first) {
                if (ans.empty() == false && ans.back().second == -1 && sum >= 0) {
                    ans.back().second = v[i].first - 1;
                }
                if ((ans.empty() == true || ans.back().second != -1) && sum < 0) {
                    ans.push_back({v[i].first, -1});
                }
            }
        }

        for (int i = 0; i < (int)ans.size(); ++ i) {
            if (i + 1 < (int)ans.size())
                assert(ans[i].second + 1 < ans[i + 1].first);
            assert(ans[i].first <= ans[i].second);
        }

        if (T != 1) cout << endl;
        cout << "Case " << T ++ << ":" << endl;
        if (ans.empty()) cout << "    No additional quotes are required." << endl;
        for (auto [a, b] : ans) {
            string a_day = to_string((time_to_date[a] + bias) % 100);
            string a_month = to_string((time_to_date[a] + bias) / 100 % 100);
            string a_year = to_string((time_to_date[a] + bias) / 10000);
            string b_day = to_string((time_to_date[b] + bias) % 100);
            string b_month = to_string((time_to_date[b] + bias) / 100 % 100);
            string b_year = to_string((time_to_date[b] + bias) / 10000);
            
            cout << "    " << a_month << "/" << a_day << "/" << a_year;
            if (a != b) {
                cout << " to " << b_month << "/" << b_day << "/" << b_year;
            }
            cout << endl;
        }
    }
}
