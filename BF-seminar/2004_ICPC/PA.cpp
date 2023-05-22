// De 132 行的 BUG 花了四、五個小時 = = ；我太難了
#include <bits/stdc++.h>
#define X first
#define Y second
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

int sign(const int a) {
    return a == 0 ? 0 : a > 0 ? 1 : -1;
}

int n, m, d;
pair<int, int> dir[409][409]; // next coordinate
pair<int, int> antPos[109]; // the pos of each ants
int posAnt[409][409]; // inverse of antPos
int antInter[409][409]; // which ants has the right of the road
int waitTime[109]; // waiting time at the spot
int walkTime[109];
int tx[8] = {0, 1, 1, 0, -1, -1, 2, -2};
int ty[8] = {2, 1, -1, -2, -1, 1, 0, 0};

int main() {
    // ios::sync_with_stdio(0); cin.tie(0);

    int T ;
    cin >> T ;
    for (int _ = 1; _ <= T; ++ _) {
        cin >> n >> m >> d;
        pair<int, int> now(200, 200);
        vector<pair<int, int>> path;
        int pathSize = 0;
        for (int i = 1; i <= n; ++ i) {
            pair<int, int> nxt;
            cin >> nxt.X >> nxt.Y;
            nxt.X = (nxt.X + 100) * 2;
            nxt.Y = (nxt.Y + 100) * 2;
            int dx = sign(nxt.X - now.X);
            int dy = sign(nxt.Y - now.Y);
            pathSize += abs(nxt.X - now.X) + abs(nxt.Y - now.Y);
            // record Carl's path
            while (now != nxt) {
                now.X += dx;
                now.Y += dy;
                path.push_back(now);
            }
        }
        reverse(path.begin(), path.end());

        fill(antPos, antPos + m, make_pair(-1, -1));
        memset(posAnt, -1, sizeof(posAnt));
        memset(antInter, -1, sizeof(antInter));
        memset(waitTime, 0, sizeof(waitTime));
        memset(walkTime, 0, sizeof(walkTime));

        vector<int> finish;
        int time = 0;
        now = pair<int, int>(200, 200);

        while (true) {
            // determine the direction by Carl's path
            if (path.empty() == false) {
                dir[now.X][now.Y] = path.back();
                now = path.back();
                path.pop_back();
                dir[now.X][now.Y] = path.back();
                now = path.back();
                path.pop_back();
                if (path.empty()) {
                    dir[now.X][now.Y] = make_pair(-2, -2);
                }
            }

            vector<bool> blocked(m, false);
            queue<int> blockQueue;
            vector<pair<int, int>> intersections;
            for (int i = 0; i < m; ++ i) {
                if (antPos[i] == make_pair(-1, -1) || antPos[i] == make_pair(-2, -2)) {
                    // not yet or reached goal
                    continue;
                }

                auto inter = dir[antPos[i].X][antPos[i].Y];
                auto &id = antInter[inter.X][inter.Y];
                if ((id == -1 || waitTime[id] < waitTime[i] || (waitTime[id] == waitTime[i] && walkTime[i] > walkTime[id])) && id != 0) {
                    if (id != -1) {
                        blockQueue.push(id);
                        blocked[id] = true;
                    }
                    id = i;
                } else {
                    blocked[i] = true;
                    blockQueue.push(i);
                }
                intersections.push_back(inter);
            }

            while (blockQueue.empty() == false) {
                int id = blockQueue.front();
                blockQueue.pop();
                for (int k = 0; k < 8; ++ k) {
                    int x = antPos[id].X + tx[k];
                    int y = antPos[id].Y + ty[k];
                    if (x < 0 || y < 0 || posAnt[x][y] == -1 || blocked[posAnt[x][y]]) continue;
                    auto nxt = dir[x][y];
                    if (dir[nxt.X][nxt.Y] != antPos[id]) continue;
                    blocked[posAnt[x][y]] = true;
                    blockQueue.push(posAnt[x][y]);
                }
            }

            vector<tuple<int, int, int>> v;
            for (int i = 0; i < m; ++ i) {
                if (antPos[i] == make_pair(-1, -1) || antPos[i] == make_pair(-2, -2)) {
                    continue;
                }
                if (blocked[i]) {
                    waitTime[i] += 1;
                } else {
                    posAnt[antPos[i].X][antPos[i].Y] = -1;
                    antPos[i] = dir[antPos[i].X][antPos[i].Y];
                    antPos[i] = dir[antPos[i].X][antPos[i].Y];
                    waitTime[i] = 0;
                    walkTime[i] += 1;

                    if (antPos[i] == make_pair(-2, -2)) {
                        finish.push_back(i);
                    } else {
                        v.push_back({antPos[i].X, antPos[i].Y, i});
                    }
                }
            }
            // 哭哇
            for (auto [x, y, i] : v) {
                posAnt[x][y] = i;
            }
            for (auto [x, y] : intersections) {
                antInter[x][y] = -1;
            }

            for (int i = 0; i < m; ++ i) {
                bool ok = false;
                if (antPos[i] == make_pair(-1, -1) && time >= i * d && posAnt[dir[200][200].X][dir[200][200].Y] == -1) {
                    posAnt[dir[200][200].X][dir[200][200].Y] = i;
                    antPos[i] = make_pair(dir[200][200].X, dir[200][200].Y);
                    if (time == i * d) {
                        ok = true;
                    }
                }
                if (time == i * d)
                    assert(ok);
            }
            time += 1;
            if ((int)finish.size() == m)
                break;
            /*
            for (int i = 0; i < m; ++ i) {
                cout << i << " : " << antPos[i].X << " " << antPos[i].Y << "\n";
            }
            cout << "\n";
            */
        }

        if (_ != 1) cout << endl;
        cout << "Case " << _ << ":" << endl;
        cout << "Carl finished the path at time " << pathSize / 2 + 1 << endl;
        cout << "The ants finished in the following order:" << endl;
        for (int i = 0; i < m; ++ i) {
            cout << finish[i] << " \n"[i == m - 1];
        }
        cout << "The last ant finished the path at time " << time << endl;
    }
}