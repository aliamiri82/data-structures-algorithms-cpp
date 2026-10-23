#include <iostream>
#include <cstring>

using namespace std;

int main() {

    char* s = new char[1000005];
    cin >> s;
    int n = strlen(s);

    int* pi = new int[n];
    pi[0] = 0;

    for(int i = 1; i < n; i++) {
        int j = pi[i-1];
        while(j > 0 && s[i] != s[j])
            j = pi[j-1];
        if(s[i] == s[j])
            j++;
        pi[i] = j;
    }

    int* ans = new int[n];
    int idx = 0;
    int cur = pi[n-1];

    while(cur > 0) {
        ans[idx++] = cur;
        cur = pi[cur-1];
    }

    for(int i = idx - 1; i >= 0; i--) {
        cout << ans[i] << " ";
    }

    return 0;
}