#include<bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

vector<int> ord[41][41][41];
int buf[2048], front, back;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

    for (int n = 1; n <= 40; ++ n) {
        for (int x = 0; x < 40; ++ x) {
            for (int s = 0; s < n; ++ s) {
                ord[n][x][s].push_back(s);
                front = back = 0;
                for (int k = s + 1; k < n; ++ k) buf[back ++] = k;
                for (int k = 0; k < s; ++ k) buf[back ++] = k;

                for (int _ = 1; _ < n; ++ _) {
                    int step = x % (back - front);
                    while (step -- )
                        buf[back ++] = buf[front ++];
                    ord[n][x][s].push_back(buf[front ++]);
                }
            }
        }
    }

    int T = 1;
    string cipher;
    while (cin >> cipher && cipher != "X") {
        int m = (int)cipher.size();
        
        vector<string> ans;
        auto Check = [&](int n, int s, int i) -> void {
            string msg = "";
            vector<bool> vis(m);
            auto &v = ord[m][i][s];
            for (int k = 0; k < n; ++ k) {
                msg.push_back(cipher[v[k]]);
                vis[v[k]] = true;
            }

            if (ans.empty() == false && ans.front() == msg) return;

            string res = "";
            for (int k = 0; k < m; ++ k)
                if (!vis[k])
                    res.push_back(cipher[k]);

            for (int t = 0; t < (int)res.size(); ++ t) {
                for (int j = i + 1; j < m; ++ j) {
                    bool ok = true;

                    auto &v = ord[(int)res.size()][j][t];
                    for (int k = 0; k < n; ++ k) {
                        if (msg[k] != res[v[k]]) {
                            ok = false;
                            break;
                        }
                    }
                    
                    if (ok) {
                        ans.push_back(msg);
                        return;
                    }
                }
            }
        };
        
        for (int n = m / 2; n >= 1 && ans.empty(); -- n) {
            for (int s = 0; s < m && (int)ans.size() < 2; ++ s)
                for (int i = 0; i < m && (int)ans.size() < 2; ++ i)
                    Check(n, s, i);
        }

        cout << "Code " << T ++ << ": ";
        if (ans.size() == 1) cout << ans.front();
        else if (ans.size() == 2) cout << "Codeword not unique";
        else assert(false);
        cout << endl;
    }
}
