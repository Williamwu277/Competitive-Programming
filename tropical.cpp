#include <bits/stdc++.h>
using namespace std;

const int MAX = 200002;

int n, q;
long psa[MAX] = {0};
long lft[MAX] = {0}, rit[MAX] = {0}, ladd[MAX] = {0}, radd[MAX] = {0};

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for(int i = 0 ; i < q ; i ++ ){
        long a, b, c, d, e; cin >> a >> b >> c >> d >> e;
        if(a == 0){
            psa[b] += d; psa[c+1] -= d;
            lft[b] += e; lft[c+1] -= e; ladd[c+1] -= (c-b+1) * e;
        }else{
            psa[b] += d; psa[c+1] -= d;
            rit[c] += e; rit[b-1] -= e; radd[b-1] -= (c-b+1) * e; 
        }
    }
    for(int i = 2; i <= n; i ++ ) psa[i] = psa[i-1] + psa[i];
    long cur = 0;
    for(int i = 1; i <= n; i ++ ){
        cur += lft[i];
        ladd[i] += ladd[i-1] + cur;
        psa[i] += ladd[i];
    }
    cur = 0;
    for(int i = n; i > 0; i -- ){
        cur += rit[i];
        radd[i] += radd[i+1] + cur;
        psa[i] += radd[i]; 
    }
    for(int i = 1; i <= n; i ++)cout << psa[i] << "\n";
}

// https://dmoj.ca/problem/tropical