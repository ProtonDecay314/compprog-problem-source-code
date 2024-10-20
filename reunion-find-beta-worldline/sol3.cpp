#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

// An Infinite, Persistent Array
class IdentityArray {
    private:
        IdentityArray* _odd;
        IdentityArray* _even;
        ll _v;
        ll _i;
        ll _pow_t_mult;
    
    public:
        IdentityArray(ll a_pow_t_mult, ll a_i, ll a_v, IdentityArray* a_odd, IdentityArray* a_even): _pow_t_mult(a_pow_t_mult), _i(a_i), _v(a_v), _odd(a_odd), _even(a_even) {}

        IdentityArray* odd() {
            if(_odd == nullptr) {
                _odd = new IdentityArray(_pow_t_mult << 1, _i + _pow_t_mult, _i + _pow_t_mult, nullptr, nullptr);
            }
            return _odd;
        }

        IdentityArray* even() {
            if(_even == nullptr) {
                _even = new IdentityArray(_pow_t_mult << 1, _i + (_pow_t_mult << 1), _i + (_pow_t_mult << 1), nullptr, nullptr);
            }
            return _even;
        }

        ll at(ll i) {
            if(i == 0) return _v;
            else if(i&1) return odd()->at((i - 1) >> 1);
            else return even()->at((i - 1) >> 1);
        }

        IdentityArray* set(ll i, ll nv) {
            if(i == 0) return new IdentityArray(_pow_t_mult, _i, nv, odd(), even());
            else if(i&1) return new IdentityArray(_pow_t_mult, _i, _v, odd()->set((i - 1) >> 1, nv), even()); // ! CAREFUL, you initially returned the pointer to the odd partition, but you had to RETURN EVERYTHING
            else return new IdentityArray(_pow_t_mult, _i, _v, odd(), even()->set((i - 1) >> 1, nv));
        }
};

class UnityArray {
    private:
        UnityArray* _odd;
        UnityArray* _even;
        ll _v;
        ll _i;
        ll _pow_t_mult;
    
    public:
        UnityArray(ll a_pow_t_mult, ll a_i, ll a_v, UnityArray* a_odd, UnityArray* a_even): _pow_t_mult(a_pow_t_mult), _i(a_i), _v(a_v), _odd(a_odd), _even(a_even) {}

        UnityArray* odd() {
            if(_odd == nullptr) {
                _odd = new UnityArray(_pow_t_mult << 1, _i + _pow_t_mult, 1ll, nullptr, nullptr);
            }
            return _odd;
        }

        UnityArray* even() {
            if(_even == nullptr) {
                _even = new UnityArray(_pow_t_mult << 1, _i + (_pow_t_mult << 1), 1ll, nullptr, nullptr);
            }
            return _even;
        }

        ll at(ll i) {
            if(i == 0) return _v;
            else if(i&1) return odd()->at((i - 1) >> 1);
            else return even()->at((i - 1) >> 1);
        }

        UnityArray* set(ll i, ll nv) {
            if(i == 0) return new UnityArray(_pow_t_mult, _i, nv, odd(), even());
            else if(i&1) return new UnityArray(_pow_t_mult, _i, _v, odd()->set((i - 1) >> 1, nv), even()); // ! CAREFUL, you initially returned the pointer to the odd partition, but you had to RETURN EVERYTHING
            else return new UnityArray(_pow_t_mult, _i, _v, odd(), even()->set((i - 1) >> 1, nv));
        }
};

// A Persistent Union Find that uses a Persistent Array
class UnionFind {
    public:
        typedef UnityArray csize_t;
        typedef IdentityArray par_t;
    private:
        csize_t* _csize;
        par_t* _par;
        ll _num_comps;
        ll _num_nodes;
    public:
        static UnionFind* create_uf(ll init_comps) {
            par_t* par_array = new par_t(1, 0, 0, nullptr, nullptr);
            return new UnionFind(init_comps, init_comps, new csize_t(1, 0, 1, nullptr, nullptr), par_array);
        }

        UnionFind(ll a_num_comps, ll a_num_nodes, csize_t* a_csize, par_t* a_par): _num_comps(a_num_comps), _num_nodes(a_num_nodes), _csize(a_csize), _par(a_par) {}

        ll find(ll i) {
            while(i != _par->at(i)) {
                i = _par->at(i);
                // cout << "E " << i << endl;
            }
            return i;
        }

        bool conn(ll i, ll j) {
            return find(i) == find(j);
        }

        UnionFind* unify(ll i, ll j) {
            ll pari = find(i), parj = find(j);
            if(pari == parj) return this;

            ll isize = _csize->at(i), jsize = _csize->at(j);

            if(isize < jsize) {
                return new UnionFind(_num_comps - 1, _num_nodes, _csize->set(parj, _csize->at(parj) + _csize->at(pari)), _par->set(pari, parj));
            } else {
                return new UnionFind(_num_comps - 1, _num_nodes, _csize->set(pari, _csize->at(parj) + _csize->at(pari)), _par->set(parj, pari));
            }
        }

        UnionFind* create_vertices(ll k) {
            // par_t* new_par = _par;
            return new UnionFind(_num_comps + k, _num_nodes + k, _csize, _par);
        }
};

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    // Create Persistent UF
    stack<UnionFind*> s;
    s.push(UnionFind::create_uf(0));

    // Input Queries
    ll q;
    cin >> q;

    while(q--) {
        string qtype;
        cin >> qtype;

        if(qtype == "SAIKAI") {
            ll u, v;
            cin >> u >> v;
            u--; v--;
            // s.top()->conn(u, v);
            cout << (s.top()->conn(u, v) ? "SAIKAI" : "KONAI SAIKAI") << "\n";
        } else if(qtype == "BUILD") {
            ll u, v;
            cin >> u >> v;
            u--; v--;
            s.push(s.top()->unify(u, v));
        } else if(qtype == "EXPAND") {
            ll k;
            cin >> k;
            s.push(s.top()->create_vertices(k));
        } else {
            ll k;
            cin >> k;
            for(ll i = 0; i < k; i++) {
                s.pop();
            }
        }
    }

    cout << flush;

    return 0;
}