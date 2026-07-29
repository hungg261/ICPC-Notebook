/* Hash: FB4DD0B5 */
struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {}
    Point operator+(const Point& o) const { return {x + o.x, y + o.y}; }
    Point operator-(const Point& o) const { return {x - o.x, y - o.y}; }
};

long long dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
long long cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
long long dist2(Point a, Point b) { return dot(a - b, a - b); }

int ccw(Point a, Point b, Point a_c) {
    long long cr = cross(b - a, a_c - a);
    return cr == 0 ? 0 : (cr > 0 ? 1 : -1);
}

bool on_segment(Point p, Point a, Point b) {
    return ccw(a, b, p) == 0 && dot(a - p, b - p) <= 0;
}

bool intersect(Point a, Point b, Point a_c, Point d) {
    if (on_segment(a_c, a, b) || on_segment(d, a, b) || on_segment(a, a_c, d) || on_segment(b, a_c, d)) return true;
    return ccw(a, b, a_c) * ccw(a, b, d) < 0 && ccw(a_c, d, a) * ccw(a_c, d, b) < 0;
}
