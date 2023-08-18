#include <bits/stdc++.h>
using namespace std;

const int MAXM = 25;
int N, M;
vector<pair<long long, long long>> points;
set<pair<long long, long long>> slopes;
unordered_map<long long, long long> scores[MAXM];

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for(int i=0; i<N; i++){
        int a, b; cin >> a >> b;
        points.push_back({a, b});
    }
    for(int i=0; i<M; i++){
        int a, b; cin >> a >> b;
        int gcd = __gcd(a, b);
        slopes.insert({a / gcd, b / gcd});
    }
    for(int i=0; i<N; i++){
        int cur = 1;
        for(pair<long long, long long> nxt: slopes){
            long long value = nxt.first * points[i].first - nxt.second * points[i].second;
            if(scores[cur].find(value) == scores[cur].end()) scores[cur][value] = 1;
            else scores[cur][value] ++;
            cur ++;
        }
    }
    long long answer = 0;
    for(int i=0; i<N; i++){
        int cur = 1;
        for(pair<long long, long long> nxt: slopes){
            long long value = nxt.first * points[i].first - nxt.second * points[i].second;
            answer += scores[cur][value] - 1;
            cur++;
        }
    }
    if(answer > 0) cout << answer / 2 << "\n";
    else cout << 0 << "\n";
}

// https://dmoj.ca/problem/aac4p3