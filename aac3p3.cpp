#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+5;
int N;
int arr[MAXN];

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for(int i=1; i<=N; i++) cin >> arr[i];
    sort(arr+1, arr+N+1);
    int cur = N;
    for(int i=1; i<=N/2; i++){
        if(N % 2 == 0 && i == N/2) cout << arr[i] << " " << arr[cur] << "\n";
        else cout << arr[i] << " " << arr[cur] << " ";
        cur --;
    }
    if(N % 2 == 1){
        cout << arr[cur] << "\n"; 
    }
    for(int i=1; i<=N/2; i++){
        if(N % 2 == 0 && i == N/2) cout << "BS\n";
        else cout << "BS";
        cur --;
    }
    if(N % 2 == 1){
        cout << "E\n"; 
    }
}

// https://dmoj.ca/problem/aac3p3