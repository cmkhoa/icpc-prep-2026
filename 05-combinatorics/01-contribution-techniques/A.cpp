// https://codeforces.com/contest/1165/problem/E
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long long n; cin >> n;
    vector<long long> a(n), b(n);

    for (long long i = 0; i < n ;i++) {
        long long x; cin >> x;
        a[i] = x * (i + 1) * (n - i);
    }

    for (long long i = 0; i < n ;i++) {
        cin >> b[i];
    }

    sort(a.begin(), a.end(), greater<long long>());
    sort(b.begin(), b.end());

    long long res = 0;
    for (long long i = 0; i < n; i++) {
        a[i] = (long long) ((a[i] % 998244353) * (b[i] % 998244353)) % 998244353;
        res = (res + a[i]) % 998244353;
    }

    cout << res << endl;
}