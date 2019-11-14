#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> links;

int ans = 0;

int dfs(int now, int father) {
    priority_queue<int> heap;
    for (auto iter=links[now].begin(); iter != links[now].end(); iter++) {
        if (*iter != father) {
            heap.push(dfs(*iter, now));
        }
    }
    if (heap.size() == 0)
        return 0;
    if (heap.size() == 1) {
        if (1+heap.top() > ans)
            ans = 1+heap.top();
        return 1+heap.top();
    }
    else {
        int tot = 2, max_height = heap.top();
        tot += max_height;
        heap.pop();
        tot += heap.top();
        if (tot > ans) {
            ans = tot;
        }
        return 1+max_height;
    }
}

int main() {
    int n, m;
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> m;
        links = *new vector<vector<int>>;
        for (int i=0; i<=m; i++) {
            links.push_back(*new vector<int>);
        }
        ans = 0;
        for (int j=0; j<m-1; j++) {
            int x, y;
            cin >> x >> y;
            links[x].push_back(y);
            links[y].push_back(x);
        }
        int h = dfs(1, 0);
        links.clear();
        cout << ans << endl;
    }
}