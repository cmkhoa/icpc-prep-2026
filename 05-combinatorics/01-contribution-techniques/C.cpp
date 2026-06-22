// https://toph.co/p/easy-peasy-subset-sum
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long exp(long long b, long long e){
    long long res = 1;
    while (e > 0){
        if (e % 2 == 1){
            res = (res * b) % 1000000007;
        }
        b = (b * b) % 1000000007;
        e /= 2;
    }
    return res;
}

int main() {
    long long n; cin>>n;
    vector<long long>a(n);

    for (long long i = 0; i < n; i++) cin>>a[i];
    sort(a.begin(), a.end());
    
    long long res = 0;
    long long mod = 1000000007;
    long long pow = exp(2, n - 2) % mod;
    
    for (long long i = 0; i < n; i++){
        long long weight = (2 * (i + 1) - n - 1) % mod;
        long long dif = (a[i] % mod) * weight % mod;
        res = (res + dif) % 1000000007;
    }

    cout << (res * pow) % mod  << endl;
}