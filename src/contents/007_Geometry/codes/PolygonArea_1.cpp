/* Hash: C632B83D */
double polygon_area(const vector<Point>& pts) {
    long long area2 = 0; int n = pts.size();
    for (int i = 0; i < n; i++) {
        area2 += cross(pts[i], pts[(i + 1) % n]);
    }
    return abs(area2) / 2.0;
}