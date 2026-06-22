// https://www.spoj.com/problems/SUMMATION/
#include <iostream>
#include <vector>
using namespace std;

long long exp(long long b, long long e, long long mod){
    long long res = 1;
    while (e > 0){
        if (e % 2 == 1){
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        e /= 2;
    }
    return res;
}

int main() {
    int t; cin >> t;
    for (int j = 0; j < t; j++){
        int n; cin >> n;
        long long mod = 100000007, res = 0, w = exp(2, n - 1, mod);
        for (int i = 0; i < n; i++){
            long long x; cin >> x;
            res = (res + (x % mod) * w % mod) % mod;
        } 
        cout <<"Case "<<j + 1<<": "<< res << endl;
    }
}