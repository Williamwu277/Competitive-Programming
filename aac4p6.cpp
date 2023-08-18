#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6+9;

int N, K;
int arr[MX], ans[MX], fin[MX];
deque<int> idx;

void solve(){
    int rem = K - N;
    K = min(K, N);
    for(int i=N-K; i<N; i++){
        idx.push_back(i-N);
        int cnter = arr[i];
        while(idx.size() > 0 && cnter > 0){
            cnter --; idx.pop_back();
        }
    }
    for(int i=0; i<N; i++){
        idx.push_back(i);
        if(idx.size() > 0 && idx.front() == i-K){
            ans[i] = max(0, (int)(arr[i] - idx.size() + 1));
        }else{
            ans[i] = max(0, (int)(arr[i] - idx.size())) + 1;
        }
        int cnter = arr[i];
        while(idx.size() > 0 && cnter > 0){
            cnter -- ; idx.pop_back();
        }
        if(idx.size() > 0 && idx.front() == i-K){
            idx.pop_front();
        }
    }
    bool give = false;
    if(rem > 0){
        int low = INT_MAX;
        for(int i=0; i<N; i++) low = min(low, ans[i]);
        if(low == 0){
            rem %= N;
            for(int i=0; i<N; i++){
                fin[(i+rem)%N] = ans[i];
            }
            give = true;
        }
    }
    if(!give){
        for(int i=0; i<N; i++) fin[i] = ans[i];
    }
    for(int i=0; i<N; i++){
        cout << fin[i];
        if(i != N-1) cout << " ";
    }
    cout << "\n";
}


int main(){
    cin >> N >> K;
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }
    solve();
}

// https://dmoj.ca/problem/aac4p6