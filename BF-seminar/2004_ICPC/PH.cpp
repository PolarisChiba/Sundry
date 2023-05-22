#include<bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
#define X first
#define Y second
using namespace std;

typedef pair<double,double> pdd;
typedef pair<pdd,pdd> Line;
struct Cir{pdd O; double R;};
const double eps=1e-8;
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
double cross(const pdd &a,const pdd &b)
{ return a.X * b.Y - a.Y * b.X;}
double abs2(const pdd &a)
{ return dot(a, a);}
double abs(const pdd &a)
{ return sqrt(dot(a, a));}
int sign(const double &a)
{ return fabs(a) < eps ? 0 : a > 0 ? 1 : -1;}
int ori(const pdd &a,const pdd &b,const pdd &c)
{ return sign(cross(b - a, c - a));}
bool collinearity(const pdd &p1, const pdd &p2, const pdd &p3)
{ return sign(cross(p1 - p3, p2 - p3)) == 0;}
bool btw(const pdd &p1,const pdd &p2,const pdd &p3) {
  if(!collinearity(p1, p2, p3)) return 0;
  return sign(dot(p1 - p3, p2 - p3)) <= 0;
}
bool seg_intersect(const pdd &p1,const pdd &p2,const pdd &p3,const pdd &p4) {
  int a123 = ori(p1, p2, p3);
  int a124 = ori(p1, p2, p4);
  int a341 = ori(p3, p4, p1);
  int a342 = ori(p3, p4, p2);
  if(a123 == 0 && a124 == 0)
    return btw(p1, p2, p3) || btw(p1, p2, p4) ||
      btw(p3, p4, p1) || btw(p3, p4, p2);
  return a123 * a124 <= 0 && a341 * a342 <= 0;
}
pdd intersect(const pdd &p1, const pdd &p2, const pdd &p3, const pdd &p4) {
  double a123 = cross(p2 - p1, p3 - p1);
  double a124 = cross(p2 - p1, p4 - p1);
  return (p4 * a123 - p3 * a124) / (a123 - a124);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

    int T = 1, n;
    while (cin >> n && n) {
        vector<pair<pair<double, double>, pair<double, double>>> v(n);
        for (auto &[a, b] : v) {
            cin >> a.X >> a.Y;
            cin >> b.X >> b.Y;
        }

        int ans = 0;
        for (int i = 0; i < n; ++ i) {
            vector<pair<double, double>> u;
            u.push_back(v[i].X);
            u.push_back(v[i].Y);
            for (int j = 0; j < n; ++ j) {
                if (i != j && seg_intersect(v[i].X, v[i].Y, v[j].X, v[j].Y))
                    u.push_back(intersect(v[i].X, v[i].Y, v[j].X, v[j].Y));
            }
            sort(u.begin(), u.end());
            int m = (int)u.size();
            for (int i = 0; i < m - 1; ++ i) {
                double dis = abs(u[i] - u[i + 1]);
                if (m == 2) ;
                else if (i == 0 || i == m - 2) dis -= 25;
                else dis -= 50;
                if (dis >= 0) ans += (int)dis / 50 + 1;
            }
        }

        cout << "Map " << T ++ << endl;
        cout << "Trees = " << ans << endl;
    }
}