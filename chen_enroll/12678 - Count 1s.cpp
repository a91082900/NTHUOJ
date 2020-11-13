#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int presum[1000010];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int cnt = 0, sum = 0, num;
    for(int i = 0; i < 1000001; i++) {
        cnt = 0;
        num = i;
        while(num > 0) {
            if(num % 10 == 1) cnt++;
            num /= 10;
        }
        sum += cnt;
        presum[i] = sum;
    }

    int n, a, b;
    cin >> n;
    while(n--) {
        cin >> a >> b;
        cout << presum[b] - presum[a-1] << '\n';
    }

    return 0;
}
