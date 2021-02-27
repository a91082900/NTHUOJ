#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool cmp(string a, string b) {
    /*if(a.size() > b.size()) return true;
    else if(a.size() < b.size()) return false;*/

    if(a.size() > b.size()) {
        for(int i = 0; i < a.size(); i++) {
            if(a[i] > b[i%b.size()]) return true;
            else if(a[i] < b[i%b.size()]) return false;
        }
    }
    else {
        for(int i = 0; i < b.size(); i++) {
            if(a[i%a.size()] > b[i]) return true;
            else if(a[i%a.size()] < b[i]) return false;
        }
    }

    return a.size() > b.size();

}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    string num[101];
    while(cin >> n) {
        for(int i = 0; i < n; i++) {
            cin >> num[i];
        }
        sort(num, num+n, cmp);

        for(int i = 0; i < n; i++) {
            cout << num[i];
        }
        cout << '\n';
    }
    return 0;
}
