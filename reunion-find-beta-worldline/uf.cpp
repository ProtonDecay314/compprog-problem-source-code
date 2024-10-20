#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

class UF {
    public:
        vll par;
        vll csize;
        ll ncomps;
        ll n;

        UF(ll a_n): par(a_n, 0ll), csize(a_n, 0ll), ncomps(a_n), n(a_n) {
            for(ll i = 0ll; i < n; i++) par[i] = i;
        }

        ll find(ll i) {
            while(i != par[i]) {
                par[i] = par[par[i]];
                i = par[i];
            }

            return i;
        }

        ll conn(ll i, ll j) {
            return find(i) == find(j);
        }

        void unify(ll i, ll j) {
            ll pari = find(i), parj = find(j);

            if(pari == parj) return;

            if(csize[pari] < csize[parj]) {
                par[pari] = parj;
                csize[parj] += csize[pari];
            } else {
                par[parj] = pari;
                csize[pari] += csize[parj];
            }
        }
};

int main() {
    ll q;
    cin >> q;

    UF uf(200'000ll);

    while(q--) {
        string qtype;
        cin >> qtype;

        if(qtype == "SAIKAI") {
            ll u, v;
            cin >> u >> v;
            u--; v--;
            // s.top()->conn(u, v);
            cout << (uf.conn(u, v) ? "SAIKAI" : "KONAI SAIKAI") << "\n";
        } else if(qtype == "BUILD") {
            ll u, v;
            cin >> u >> v;
            u--; v--;
            uf.unify(u, v);
        } else if(qtype == "EXPAND") {
            ll k;
            cin >> k;
            
        } else {
            ll k;
            cin >> k;
            // ! Not supported!
        }
    }

    cout << flush;

    return 0;
}