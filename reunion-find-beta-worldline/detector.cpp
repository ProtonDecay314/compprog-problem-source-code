/*
Input Format:
q
SAIKAI u v
BUILD u v
EXPAND k
TIMEWARP k
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll q;
    cin >> q;

    // bool ql3 = q <= 3ll, ql2000 = q <= 2000ll, ql2e5 = q <= 200'000ll;

    bool has_timewarp_query = false;

    bool saikai_query_found = false;
    bool bridge_creation_before_query = true;

    ll maxn = 0ll;
    stack<ll> s;
    s.push(0);
    
    while(q--) {
        string qtype;
        cin >> qtype;

        if(qtype == "SAIKAI") {
            saikai_query_found = true;
            ll u, v;
            cin >> u >> v;
            u--; v--;
        } else if(qtype == "BUILD") {
            if(saikai_query_found) bridge_creation_before_query = false;
            ll u, v;
            cin >> u >> v;
            u--; v--;
            s.push(s.top());
        } else if(qtype == "EXPAND") {
            ll k;
            cin >> k;
            s.push(s.top() + k);
            maxn = max(maxn, s.top());
        } else {
            has_timewarp_query = true;

            ll k;
            cin >> k;
            for(ll i = 0; i < k; i++) {
                if(s.size() > 1) s.pop();
            }
        }
    }

    // Finds valid subtasks
    vector<bool> valid(8, true);

    valid[0] = maxn <= 3ll && q <= 2000ll && !has_timewarp_query;
    valid[1] = maxn <= 3ll && q <= 2000ll;
    valid[2] = maxn <= 2000ll && q <= 2000ll && !has_timewarp_query;
    valid[3] = maxn <= 2000ll && q <= 2000ll;
    valid[4] = maxn <= 200'000ll && q <= 200'000ll && !has_timewarp_query && bridge_creation_before_query;
    valid[5] = maxn <= 200'000ll && q <= 200'000ll && !has_timewarp_query;
    valid[6] = maxn <= 200'000ll && q <= 200'000ll;
    valid[7] = maxn <= 1'000'000'000ll && q <= 200'000ll;

    for(int i = 0; i < 8; i++) {
        if(valid[i]) cout << i + 1 << " ";
    }
    cout << endl;

    return 0;
}