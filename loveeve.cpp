#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000005;
int N, arr[MAXN];

int main() {
    
    ios::sync_with_stdio(0); cin.tie(0);
    
    cin >> N;
    for(int i=1; i<=2*N; i++){
        cin >> arr[i];
    }
    sort(arr+1, arr+2*N+1);
    int ours = 0, theirs = 0;
    for(int i=1; i<=2*N; i++){
        if(i <= N) theirs += arr[i];
        else ours += arr[i];
    }
    cout << ours - theirs << "\n";
    
}

// https://dmoj.ca/problem/loveeve