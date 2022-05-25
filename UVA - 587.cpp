#include <bits/stdc++.h>

using namespace std; 

#define FIO cin.tie(0),ios::sync_with_stdio(0),cout.tie(0)
#define oo __LONG_LONG_MAX__
#define ooi INT32_MAX
#define endl '\n'
#define EPS 1e-9
#define PI acos(-1)
#define DegToRad(theta) theta * PI / 180
#define areParallel(line1, line2) (fabs(line1.a - line2.a) < EPS && fabs(line1.b - line2.b) < EPS)
#define areSame(line1, line2) (areParallel(line1, line2) && fabs(line1.c - line2.c) < EPS)
#define scale(_vector, _scale) vec(_vector.x * _scale, _vector.y * _scale)
#define translate(_point, _vector) point(_point.x + _vector.x, _point.y + _vector.y)
#define dot(a, b) (double)(a.x * b.x + a.y * b.y)
#define cross(a, b) (double)(a.x * b.y - a.y + b.x)
#define norm_sq(_vector) (double)(_vector.x * _vector.x + _vector.y * _vector.y)
#define dist(_point1, _point2) hypot(_point1.x - _point2.x, _point1.y - _point2.y)
#define CCW(p, q, r) (bool)(cross(toVec(p, q), toVec(p, r)) > 0)
#define collinear(p, q, r) (bool)(fabs(cross(toVec(p, q), toVec(p, r))) < EPS)

bool DB = 0;
 
#define ll long long 
// Points
struct point_i{
    int x, y;
    point_i(){x = y = 0;}
    point_i(int _x, int _y): x(_x), y(_y) {};
};
struct point{
    double x, y;
    point(){x = y = 0.0;}
    point(double _x, double _y): x(_x), y(_y) {};
    bool operator < (point other) const {
        if(fabs(x - other.x) > EPS){
            return x < other.x;
        }
        return y < other.y;
    }
    bool operator == (point other) const {
        return (fabs(x - other.x) < EPS && fabs(y - other.y) < EPS ); // EPS 1e-9
    }
};
point O{0, 0};
point rotate(point p, double theta){
    double rad = DegToRad(theta);
    return point(p.x * cos(rad) - p.y * sin(rad), 
                 p.x * sin(rad) + p.y * cos(rad));
}
// Lines
struct line{
    double a, b, c; // ax + by + c = 0
};
void pointsToLine(point p1, point p2, line &l){
    if(fabs(p1.x - p2.x) < EPS){
        l.a = 1, l.b = 0, l.c = -p1.x;
    }else{
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;
        l.c = -(double)( p1.y + l.a * p1.x);
    }
    return;
}
bool areIntersect(line l1, line l2, point &p){
    if(areParallel(l1, l2)) return 0;
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b); // by solving 2 Equations
    if(fabs(l1.b) > EPS) // Test Vertical lines for line one then b = 0 so get it from line 2
        p.y = -( l1.a * p.x + l1.c );
    else
        p.y = -( l2.a * p.x + l2.c );
    return 1;
}
struct vec{
    double x, y;
    vec(){x = y = 0.0;}
    vec(double _x, double _y): x(_x), y(_y) {};
};
vec toVec(point a, point b){
    return vec(b.x - a.x, b.y - a.y);
}
double distToLine(point p, point a, point b, point &c){
    // c = a + u * ab
    // u = ap * cos(theta) / |ab|
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));
    return dist(a, c);
}
double distToLineSegment(point p, point a, point b, point &c){
    // c = a + u * ab
    // u = ap * cos(theta) / |ab|
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if(u < 0.0){ // closer to a
        c = a;
        return dist(p, a);
    }else if(u > 1.0){ // closer to b
        c = b;
        return dist(p, b);
    }
    // must be between a and b
    return distToLine(p, a, b, c);
}
double angle(point a, point o, point b){
    vec ao = toVec(a, o), ob = toVec(o, b);
    return acos(dot(ao, ob) / (sqrt(norm_sq(ao)) * sqrt(norm_sq(ob))));
}
bool betweenPoints(point a, point inMid, point b){
    if(fabs(a.x - inMid.x) < EPS && fabs(a.y - inMid.y) < EPS)
        return 1;
    if(fabs(b.x - inMid.x) < EPS && fabs(b.y - inMid.y) < EPS)
        return 1;
    vec ab = toVec(a, b);
    // if(ab.x < EPS && ab.y < EPS){
        
    // }
    vec ba = scale(ab, -1);
    vec aM = toVec(a, inMid);
    vec bM = toVec(b, inMid);
    double u = dot(ab, aM) / (sqrt( norm_sq(ab) * norm_sq(aM)));
    double v = dot(ba, bM) / (sqrt( norm_sq(ba) * norm_sq(bM)));
    return (fabs(u - 1) < EPS && fabs(v - 1) < EPS);
}

int main(){ 
    DB = 0;
    #ifdef VS_FreeOpen 
        freopen("input.in", "r", stdin); 
        freopen("output.in", "w", stdout); 
    #endif 
    FIO; 

    int tc = 1;
    // cin >> tc;
    int cnt = 0;
    cout << fixed << setprecision(3);
    while(1){
        ++cnt;
        point distination{};
        string inp;
        cin >> inp;
        if(inp == "END"){
            break;
        }
        cout << "Map #" << cnt << endl;
        int inc = 0, pos = 0;
        /*
              8   1   3
            7           2
              11  4   6

        */
        for(int i = 0 ; i < inp.size() ; ++i){
            if(inp[i] == ',' || inp[i] == '.'){
                // cout << pos << " " << inc << endl;
                if(pos == 1){ // 'N'
                    distination.y += inc;
                }else if(pos == 2){ // 'E'
                    distination.x += inc;
                }else if(pos == 4){ // 'S'
                    distination.y -= inc;
                }else if(pos == 7){ // 'W'
                    distination.x -= inc;
                }else if(pos == 3){ // 'NE'
                    distination.x += inc * cos(DegToRad(45));
                    distination.y += inc * sin(DegToRad(45));
                }else if(pos == 6){ // 'SE'
                    distination.x += inc * cos(DegToRad(45));
                    distination.y -= inc * sin(DegToRad(45));
                }else if(pos == 11){ // 'SW'
                    distination.x -= inc * cos(DegToRad(45));
                    distination.y -= inc * sin(DegToRad(45));
                }else if(pos == 8){ // 'NW'
                    distination.x -= inc * cos(DegToRad(45));
                    distination.y += inc * sin(DegToRad(45));
                }
                pos = 0;
                inc = 0;
            }else if(inp[i] - '0' > 9){
                if(inp[i] =='N'){
                    pos += 1;
                }else if(inp[i] == 'E'){
                    pos += 2;
                }else if(inp[i] == 'S'){
                    pos += 4;
                }else if(inp[i] == 'W'){
                    pos += 7;
                }
            }else{
                inc = inc * 10 + (inp[i] - '0');
            }
        }
        cout << "The treasure is located at (" << distination.x << ',' << distination.y << ").\n";
        cout << "The distance to the treasure is " << dist(O, distination) << ".\n\n";
    }
    

    return 0; 
}
