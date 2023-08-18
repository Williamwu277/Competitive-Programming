#include <bits/stdc++.h>
using namespace std;

const int SEGMENT_TREE_SIZE = 400100;
const int MAXN = 100005;

struct Event{
    int operation, a, b, ind;
};

struct SegmentTree{

    struct Node{
        int l, r, max;
    } seg[SEGMENT_TREE_SIZE];
    
    void build(int cur, int l, int r){
        if(l == r) seg[cur] = {l, r, 0};
        else {
            int mid = (l + r) / 2;
            build(cur*2, l, mid);
            build(cur*2+1, mid+1, r);
            seg[cur] = {l, r, 0};
        }
    }

    void update(int cur, int ind, int val){
        if(seg[cur].l == ind && seg[cur].r == ind) seg[cur].max = val;
        else{
            int mid = (seg[cur].l + seg[cur].r) / 2;
            if(ind <= mid) update(cur*2, ind, val);
            else update(cur*2+1, ind, val);
            seg[cur].max = max(seg[cur*2].max, seg[cur*2+1].max);
        }
    }

    int query(int cur, int l, int r){
        if(l > seg[cur].r || r < seg[cur].l) return 0;
        else if(l <= seg[cur].l && seg[cur].r <= r) return seg[cur].max;
        return max(query(cur*2, l , r), query(cur*2+1, l, r));
    }

} segmentTree;

int dp[MAXN], N;
vector<Event> events;
set<int> position, order;
unordered_map<int, int> idx;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    segmentTree.build(1, 1, MAXN);
    cin >> N;
    for(int i=1; i<=N; i++){
        int a, b; cin >> a >> b;
        events.push_back({1, a+b, a, i});
        events.push_back({2, a, b, i});
        order.insert(a);
    }
    sort(events.begin(), events.end(), [](const Event& one, const Event& two)->bool{
        if(one.a == two.a) return one.operation < two.operation;
        return one.a < two.a;
    });
    int cur = 0;
    for(int nxt: order){
        cur ++; idx[nxt] = cur;
    }
    int best = 0;
    for(int i=0; i<2*N; i++){
        if(events[i].operation == 1){
            position.insert(events[i].b);
            segmentTree.update(1, idx[events[i].b], dp[events[i].ind]);
        }else{
            auto it = position.upper_bound(events[i].a - events[i].b); 
            int res = 0;
            if(it == position.end()) res = segmentTree.query(1, 1, MAXN);
            else if(it != position.begin()){
                it--;
                res = segmentTree.query(1, 1, idx[*it]);
            }
            dp[events[i].ind] = res + 1;
            best = max(best, dp[events[i].ind]);
        }
    }
    cout << best << "\n";
}

// https://dmoj.ca/problem/aac1p6