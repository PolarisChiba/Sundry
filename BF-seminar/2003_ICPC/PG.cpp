#include<bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;

int HexToDec(string s) {
    int res = 0;
    for (auto i : s) {
        if (isdigit(i)) res = res * 16 + (i - '0');
        else res = res * 16 + (i - 'A' + 10);
    }
    return res;
}
string DecToHex(int x) {
    string s = "";
    for (int i = 0; i < 4; ++ i) {
        if (x % 16 < 10) s.push_back(x % 16 + '0');
        else s.push_back(x % 16 - 10 + 'A');
        x >>= 4;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    while (true) {
        map<string, vector<int>> var_addr;
        vector<string> mem_addr;
        vector<string> mod_var;
        int now_addr = HexToDec("0100");

        string op;
        while (cin >> op) {
            if (op == "D") {
                string var, offset;
                cin >> var >> offset;
                var_addr[var].push_back(now_addr + HexToDec(offset));
            } else if (op == "E") {
                string var;
                cin >> var;
                if (var_addr.find(var) == var_addr.end())
                    var_addr[var] = vector<int>(0);
                mod_var.push_back(var);
            } else if (op == "C") {
                string s;
                cin >> s;
                int n = HexToDec(s);
                vector<string> mod_addr(n);
                for (auto &i : mod_addr) cin >> i;
                for (int i = 1; i < n; ++ i) {
                    if (mod_addr[i - 1] == "$")
                        mod_addr[i] = mod_var[HexToDec(mod_addr[i])];
                }
                for (auto i : mod_addr) 
                    mem_addr.push_back(i);
            } else if (op == "Z") {
                now_addr = 256 + (int)mem_addr.size();
                mod_var.clear();
            } else if (op == "$") {
                break;
            }
        }

        if (var_addr.empty() && mem_addr.empty() && now_addr == 256)
            return 0;

        for (auto &[a, b] : var_addr) {
            if (b.empty())
                b.push_back(0);
        }

        for (int i = 1; i < (int)mem_addr.size(); ++ i) {
            if (mem_addr[i - 1] == "$") {
                string res = DecToHex(var_addr[mem_addr[i]].front());
                mem_addr[i - 1] = res.substr(0, 2);
                mem_addr[i] = res.substr(2, 2);
            }
        }

        int checksum = 0;
        for (auto i : mem_addr) {
            checksum <<= 1;
            checksum += (checksum >> 16) + HexToDec(i);
            checksum &= ((1 << 16) - 1);
        }
        
        if (T != 1) cout << endl;
        cout << "Case " << T ++ << ": checksum = " << DecToHex(checksum) << endl;
        cout << " SYMBOL   ADDR" << endl;
        cout << "--------  ----" << endl;
        for (auto [a, b] : var_addr) {
            cout << left << setw(10) << setfill(' ') << a;
            if (b.front() != 0)
                cout << DecToHex(b.front());
            else
                cout << "????";
            if ((int)b.size() >= 2) cout << " M";
            cout << endl;
        }
    }
}