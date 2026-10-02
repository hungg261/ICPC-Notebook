/* Hash: C30EF4B1 */
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
int n;
long long dist[505][505];

void floyd_warshall() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

// Fast update in O(N^2) when adding a NEW vertex 'u'
void add_vertex(int u) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (dist[i][u] < INF && dist[u][j] < INF)
                dist[i][j] = min(dist[i][j], dist[i][u] + dist[u][j]);
}