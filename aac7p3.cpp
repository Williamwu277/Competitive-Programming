#include <bits/stdc++.h>
using namespace std;

int N, M; 
const long long MOD = 1e9+7;
const int MX = 1e6+5;
long long arr[MX], port[MX], psa[MX], break_points[MX];
pair<long long, long long> build_ups[MX];

// helper function for solution
long long build_up(int start, int end){
    long long ret = 0;
    if(start <= end){
        for(int i=start; i<end; i++){
            ret += (long long)(end - i) * arr[i+1]; ret %= MOD;
        }
    }else{
        for(int i=start; i>end; i--){
            ret += (long long)(i - end) * arr[i]; ret %= MOD;
        }
    }
    return ret;
}

// O(N)
void fast(){
    //start of solution
    sort(port+1, port+M+1);
    long long ans = 0;
    for(int i=1; i<=N; i++){
        psa[i] = psa[i-1] + arr[i];
    }
    long long total_build = 0;
    for(int k=1; k<M; k++){
        long long length = psa[port[k+1]] - psa[port[k]], prefix = 0, break_point = port[k];
        for(int i=port[k]+1; i<=port[k+1]; i++){
            prefix += arr[i]; length -= arr[i];
            if(prefix <= length) break_point = i;
            else {
                prefix -= arr[i]; length += arr[i]; break;
            }
        }
        break_points[k] = break_point;
        build_ups[k] = {build_up(port[k], break_point), build_up(port[k+1], break_point+1)};
        total_build += build_ups[k].first + build_ups[k].second; total_build %= MOD;
    }
    long long inc = build_up(1, port[1]), fourth = build_up(port[M], N);
    for(int i=1; i<=port[1]; i++){
        if(i != port[1]){
            ans += inc; ans %= MOD;
            inc = (inc + MOD - arr[i+1] * (port[1]-i)) % MOD;
        }
        ans += fourth + total_build + (N-port[1]) * (psa[port[1]] - psa[i]); ans %= MOD;
    }
    inc = 0;
    for(int i=port[M]; i<=N; i++){
        if(i != N){
            ans += fourth; ans %= MOD;
            fourth = (fourth + MOD - arr[i+1] * (N-i)) % MOD;
        }
        ans += total_build + (port[M] - port[1] - 1) * (psa[i] - psa[port[M]]); ans %= MOD;
    }
    for(int k=1; k<M; k++){
        long long ptr = port[k] + 1; long long length = psa[port[k+1]] - psa[port[k]], prefix = 0, second = 0;
        long long third = (build_up(port[k+1], port[k]) + MOD * 2 - (psa[port[k+1]] - psa[port[k]]) - (psa[port[k+1]] - psa[port[k]+1])) % MOD;
        total_build = (total_build + MOD - build_ups[k].first - build_ups[k].second) % MOD;
        for(int i=port[k]+1; i<port[k+1]; i++){
            if(i != port[k]+1){
                length += arr[i]; prefix -= arr[i]; second = (second + MOD - (ptr - i + 1) * arr[i]) % MOD;
            }
            while(ptr < port[k+1] - 1 && prefix + arr[ptr + 1] <= length - arr[ptr + 1]){
                ptr ++; prefix += arr[ptr]; length -= arr[ptr];
                second += psa[ptr] - psa[i]; second %= MOD; third = (third + MOD - (psa[port[k+1]] - psa[ptr])) % MOD;
            }
            ans += second + third + (port[k+1] - ptr - 1) * (psa[i] - psa[port[k]]); ans %= MOD;
            ans += total_build + (port[M] - port[k+1]) * (i <= break_points[k] ? psa[i] - psa[port[k]] : psa[port[k+1]] - psa[i]);
            ans %= MOD;
        }
        // from the portals to everywhere that hasn't reached it since only portal 1 & N get dealt with up there — the loop skips them
        if(k+1 != M) {ans += total_build; ans %= MOD;}
    }
    cout << ans << "\n";
}


int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for(int i=1; i<=M; i++) cin >> port[i];
    for(int i=2; i<=N; i++) cin >> arr[i];
    fast();
}

// https://dmoj.ca/problem/aac7p3