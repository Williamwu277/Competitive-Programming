#include <bits/stdc++.h>
using namespace std;

const int MAXN = 605;
int T, N, arr[MAXN], out[MAXN];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> T;
    while(T--){
        
        cin >> N;
        for(int i=1; i<=N; i++) cin >> arr[i];
        sort(arr+1, arr+N+1);

        if(N % 2 == 0 && arr[1] == arr[N]) cout << -1 << "\n";
        else if(N % 2 == 1){
            for(int i=1; i<=N; i++){
                if(i == N) cout << arr[i] << "\n";
                else cout << arr[i] << " ";
            }
        }else{
            int cur = N;
            for(int i=1; i<=N; i+=2){
                out[i] = arr[cur]; cur --;
            }
            for(int i=2; i<=N; i+=2){
                out[i] = arr[cur]; cur --;
            }
            for(int i=1; i<=N; i++){
                if(i==N) cout << out[i] << "\n";
                else cout << out[i] << " ";
            }
        }
    }
}

//https://dmoj.ca/problem/aac2p4