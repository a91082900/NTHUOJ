#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int deg[5005];
vector<pair<int, int> > edge;
vector<int> ans;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, u, v;
    cin >> n;
    pair<int, int> tmp;
    for(int i = 1; i < n; i++) {
        cin >> u >> v;
        tmp = make_pair(u, v);
        edge.push_back(tmp);
        deg[u]++;
        deg[v]++;
    }

    int mini, idx;

    for(int k = 0; k < n-2; k++) {
        mini = 5005;
        for(int i = 0; i < n-1; i++) {
            if(edge[i].first < 0)
                continue;
            if(deg[edge[i].first] == 1) {
                if(edge[i].first < mini) {
                    mini = edge[i].first;
                    idx = i;
                }
            }
            if(deg[edge[i].second] == 1) {
                if(edge[i].second < mini) {
                    mini = edge[i].second;
                    idx = i;
                }
            }
        }
        //cout << idx << '\n';
        deg[edge[idx].first]--;
        deg[edge[idx].second]--;
        if(deg[edge[idx].first] == 0)
            ans.push_back(edge[idx].second);
        else
            ans.push_back(edge[idx].first);
        edge[idx].first = -1;
    }

    for(int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    cout << '\n';
    return 0;
}
