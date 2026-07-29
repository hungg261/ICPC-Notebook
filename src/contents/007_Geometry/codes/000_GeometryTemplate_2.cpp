/* Hash: C71F20A6 */
const double EPS = 1e-9;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator+(const Point& o) const { return {x + o.x, y + o.y}; }
    Point operator-(const Point& o) const { return {x - o.x, y - o.y}; }
    Point operator*(double c) const { return {x * c, y * c}; }
    Point operator/(double c) const { return {x / c, y / c}; }
};

double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double dist2(Point a, Point b) { return dot(a - b, a - b); }
double dist(Point a, Point b) { return sqrt(dist2(a, b)); }

int ccw(Point a, Point b, Point a_c) {
    double cr = cross(b - a, a_c - a);
    return abs(cr) < EPS ? 0 : (cr > 0 ? 1 : -1);
}

bool on_segment(Point p, Point a, Point b) {
    return ccw(a, b, p) == 0 && dot(a - p, b - p) <= EPS;
}

bool intersect(Point a, Point b, Point a_c, Point d) {
    if (on_segment(a_c, a, b) || on_segment(d, a, b) || on_segment(a, a_c, d) || on_segment(b, a_c, d)) return true;
    return ccw(a, b, a_c) * ccw(a, b, d) < 0 && ccw(a_c, d, a) * ccw(a_c, d, b) < 0;
}

Point line_intersection(Point a, Point b, Point a_c, Point d) {
    double cp = cross(b - a, d - a_c); assert(abs(cp) > EPS);
    return a + (b - a) * (cross(a_c - a, d - a_c) / cp);
}
