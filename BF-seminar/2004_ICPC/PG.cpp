#include <bits/stdc++.h>
#define X first
#define Y second
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;

typedef pair<double,double> pdd;
typedef pair<pdd,pdd> Line;
struct Cir{pdd O; double R; Cir(pair<pdd, double> x): O(x.first), R(x.second) {}};
const double eps=1e-8;
const double pi = acos(-1);
pdd operator+(const pdd &a, const pdd &b)
{ return pdd(a.X + b.X, a.Y + b.Y);}
pdd operator-(const pdd &a, const pdd &b)
{ return pdd(a.X - b.X, a.Y - b.Y);}
pdd operator*(const pdd &a, const double &b)
{ return pdd(a.X * b, a.Y * b);}
pdd operator/(const pdd &a, const double &b)
{ return pdd(a.X / b, a.Y / b);}
double dot(const pdd &a,const pdd &b)
{ return a.X * b.X + a.Y * b.Y;}
double abs2(const pdd &a)
{ return dot(a, a);}
double abs(const pdd &a)
{ return sqrt(dot(a, a));}
int sign(const double &a)
{ return fabs(a) < eps ? 0 : a > 0 ? 1 : -1;}

vector<pdd> CCinter(Cir a, Cir b) {
  pdd o1 = a.O, o2 = b.O;
  double r1 = a.R, r2 = b.R, d2 = abs2(o1 - o2), d = sqrt(d2);
  // if(d < max(r1, r2) - min(r1, r2) || d > r1 + r2) return {};
  pdd u = (o1 + o2) * 0.5 + (o1 - o2) * ((r2 * r2 - r1 * r1) / (2 * d2));
  double A = sqrt((r1 + r2 + d) * (r1 - r2 + d) * (r1 + r2 - d) * (-r1 + r2 + d));
  pdd v = pdd(o1.Y - o2.Y, -o1.X + o2.X) * A / (2 * d2);
  return {u + v, u - v};
}

int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    int T = 1;
    int n;
    double tReceive;
    pdd goal;
    while (cin >> n >> tReceive >> goal.X >> goal.Y && n) {
        vector<pair<pdd, double>> source(n);
        bool ok = true, inf = (n == 1);
        for (auto &[center, radius] : source) {
            double ang, tSend;
            cin >> center.X >> center.Y >> ang >> tSend;
            ang = (450.0 - ang) * pi / 180.0;
            center.X += tSend * 100 * cos(ang);
            center.Y += tSend * 100 * sin(ang);
            radius = (tReceive - tSend) * 350;
            ok &= (radius >= 0);
        }

        vector<pdd> cand;
        // Find one that doesn't coincide with source[0]
        for (int i = 1; i < n && ok; ++ i) {
            auto &[p0, r0] = source[0];
            auto &[p1, r1] = source[1];
            double dx = p0.X - p1.X;
            double dy = p0.Y - p1.Y;
            double dr = r0 - r1;
            if (dx * dx + dy * dy + dr * dr > 0.01) {
                double centerDist = abs(p0 - p1);
                if (centerDist < 0.1);
                else if (centerDist + 0.1 > r0 + r1);
                else if (centerDist + 0.1 < max(r0, r1) - min(r0, r1));
                else if (centerDist >= r0 + r1) {
                    cand.push_back(p0 + (p1 - p0) * (r0 + 0.05) / centerDist);
                } else if (centerDist < max(r0, r1) - min(r0, r1)) {
                    if (r0 > r1) {
                        cand.push_back(p0 + (p1 - p0) / centerDist * (r0 - 0.05));
                    } else {
                        cand.push_back(p1 + (p0 - p1) / centerDist * (r1 - 0.05));
                    }
                } else {
                    cand = CCinter(source[0], source[1]);
                    if (abs2(cand.front() - cand.back()) < 0.01)
                        cand.pop_back();
                }
                break;
            }
            if (i == n - 1)
                inf = true;
        }
        // cout << cand[0].X << " " << cand[0].Y << "\n";

        vector<pdd> inters;
        for (auto p : cand) {
            bool chk = true;
            for (int i = 0; i < n; ++ i) {
                chk &= (fabs(abs(source[i].first - p) - source[i].second) <= 0.1);
            }
            if (chk)
                inters.push_back(p);
        }
        if (inters.size() > 1u)
            inf = true;
        if (inters.empty())
            ok = false;
        
        cout << "Trial " << T ++ << ": ";
        if (inf == true)
            cout << "Inconclusive\n";
        else if (ok == false)
            cout << "Inconsistent\n";
        else if (abs2(inters.front() - goal) < 0.01)
            cout << "Arrived\n";
        else {
            double ang = acos((goal.X - inters[0].X) / abs(goal - inters[0])) * 180.0 / pi;
            if (sign(goal.Y - inters[0].Y) == -1)
                ang = 360.0 - ang;
            ang = fmod(450 - ang, 360.0);
            assert(0 <= ang && ang < 360);
            // cout << fixed << setprecision(0) << ang << " degrees\n";
            printf("%.0lf degrees\n", ang);
        }
    }
}