#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

const int MAX_ALLOC = 4000000;

class IdentityArray {
    private:
        // int _ptr;
        ll _pow_t_mult, _i, _v;
        int _odd, _even;
    public:
        IdentityArray(): _pow_t_mult(0ll), _i(0ll), _v(0ll), _odd(0), _even(0) {};
        void operator=(const IdentityArray& other) {
            _pow_t_mult = other._pow_t_mult;
            _i = other._i;
            _v = other._v;
            _odd = other._odd;
            _even = other._even;
        };
        IdentityArray(ll a_pow_t_mult, ll a_i, ll a_v, int a_odd, int a_even);

        static int make_new(ll a_pow_t_mult, ll a_i, ll a_v, int a_odd, int a_even);

        int odd();

        int even();

        ll at(ll i);

        int set(ll i, ll nv);

        void print() {
            cout << _pow_t_mult << " " << _i << " " << _v << " " << _odd << " " << _even << endl;
        }

        // ~IdentityArray() {
        //     cout << "Bye Bye ";
        //     print();
        // }
};

IdentityArray iarrn[MAX_ALLOC];
static int iarrnsz = 0;

IdentityArray::IdentityArray(ll a_pow_t_mult, ll a_i, ll a_v, int a_odd, int a_even): _pow_t_mult(a_pow_t_mult), _i(a_i), _v(a_v), _odd(a_odd), _even(a_even) {};

int IdentityArray::make_new(ll a_pow_t_mult, ll a_i, ll a_v, int a_odd, int a_even) {
    IdentityArray newia(a_pow_t_mult, a_i, a_v, a_odd, a_even);
    iarrn[iarrnsz] = newia;
    int ind = iarrnsz;
    iarrnsz++;
    assert(iarrnsz < MAX_ALLOC);
    // cout << "MAKING " << ind << endl;
    // iarrn[ind].print();
    return ind;
}

int IdentityArray::odd() {
    if(_odd == -1) {
        _odd = IdentityArray::make_new(_pow_t_mult << 1ll, _i + _pow_t_mult, _i + _pow_t_mult, -1, -1);
    }
    return _odd;
}

int IdentityArray::even() {
    if(_even == -1) {
        _even = IdentityArray::make_new(_pow_t_mult << 1ll, _i + (_pow_t_mult << 1ll), _i + (_pow_t_mult << 1ll), -1, -1);
    }
    return _even;
}

ll IdentityArray::at(ll i) {
    // cout << "HAHA " << odd() << " " << even() << endl;
    if(i == 0ll) return _v;
    else if(i&1ll) return iarrn[odd()].at((i - 1ll) >> 1ll);
    else return iarrn[even()].at((i - 1ll) >> 1ll);
}

int IdentityArray::set(ll i, ll nv) {
    int to_create;
    if(i == 0ll) to_create = IdentityArray::make_new(_pow_t_mult, _i, nv, _odd, _even);
    else if(i&1ll) {
        int new_odd = iarrn[odd()].set((i - 1ll) >> 1ll, nv);
        to_create = IdentityArray::make_new(_pow_t_mult, _i, _v, new_odd, _even);
    } else { // ! CAREFUL, you initially returned the pointer to the odd partition, but you had to RETURN EVERYTHING
        int new_even = iarrn[even()].set((i - 1ll) >> 1ll, nv);
        // cout << "I'm LOSING BRAINCELLS" << endl;
        // cout << _pow_t_mult << endl;
        to_create = IdentityArray::make_new(_pow_t_mult, _i, _v, _odd, new_even);
    }

    return to_create;
}

// UNITY ARRAY

class UnityArray {
    private:
        // int _ptr;
        ll _pow_t_mult, _i, _v;
        int _odd, _even;
    public:
        UnityArray(): _pow_t_mult(0ll), _i(0ll), _v(0ll), _odd(0), _even(0) {};
        void operator=(const UnityArray& other) {
            _pow_t_mult = other._pow_t_mult;
            _i = other._i;
            _v = other._v;
            _odd = other._odd;
            _even = other._even;
        };
        UnityArray(ll a_pow_t_mult, ll a_i, ll a_v, int a_odd, int a_even);

        static int make_new(ll a_pow_t_mult, ll a_i, ll a_v, int a_odd, int a_even);

        int odd();

        int even();

        ll at(ll i);

        int set(ll i, ll nv);

        void print() {
            cout << _pow_t_mult << " " << _i << " " << _v << " " << _odd << " " << _even << endl;
        }

        // ~UnityArray() {
        //     cout << "Bye Bye ";
        //     print();
        // }
};

UnityArray uarrn[MAX_ALLOC];
static int uarrnsz = 0;

UnityArray::UnityArray(ll a_pow_t_mult, ll a_i, ll a_v, int a_odd, int a_even): _pow_t_mult(a_pow_t_mult), _i(a_i), _v(a_v), _odd(a_odd), _even(a_even) {};

int UnityArray::make_new(ll a_pow_t_mult, ll a_i, ll a_v, int a_odd, int a_even) {
    UnityArray newua(a_pow_t_mult, a_i, a_v, a_odd, a_even);
    uarrn[uarrnsz] = newua;
    int ind = uarrnsz;
    uarrnsz++;
    assert(uarrnsz < MAX_ALLOC);
    // cout << "MAKING " << ind << endl;
    // uarrn[ind].print();
    return ind;
}

int UnityArray::odd() {
    if(_odd == -1) {
        _odd = UnityArray::make_new(_pow_t_mult << 1ll, _i + _pow_t_mult, 1ll, -1, -1);
    }
    return _odd;
}

int UnityArray::even() {
    if(_even == -1) {
        _even = UnityArray::make_new(_pow_t_mult << 1ll, _i + (_pow_t_mult << 1ll), 1ll, -1, -1);
    }
    return _even;
}

ll UnityArray::at(ll i) {
    // cout << "HAHA " << odd() << " " << even() << endl;
    if(i == 0ll) return _v;
    else if(i&1ll) return uarrn[odd()].at((i - 1ll) >> 1ll);
    else return uarrn[even()].at((i - 1ll) >> 1ll);
}

int UnityArray::set(ll i, ll nv) {
    int to_create;
    if(i == 0ll) to_create = UnityArray::make_new(_pow_t_mult, _i, nv, _odd, _even);
    else if(i&1ll) {
        int new_odd = uarrn[odd()].set((i - 1ll) >> 1ll, nv);
        to_create = UnityArray::make_new(_pow_t_mult, _i, _v, new_odd, _even);
    } else { // ! CAREFUL, you initially returned the pointer to the odd partition, but you had to RETURN EVERYTHING
        int new_even = uarrn[even()].set((i - 1ll) >> 1ll, nv);
        // cout << "I'm LOSING BRAINCELLS" << endl;
        // cout << _pow_t_mult << endl;
        to_create = UnityArray::make_new(_pow_t_mult, _i, _v, _odd, new_even);
    }

    return to_create;
}

typedef UnityArray csize_t;
typedef IdentityArray par_t;

// A Persistent Union Find that uses a Persistent Array
class UnionFind {
    private:
        int _csize;
        int _par;
        ll _num_comps;
        ll _num_nodes;
    public:
        static UnionFind* create_uf(ll init_comps) {
            int par_array = par_t::make_new(1ll, 0ll, 0ll, -1, -1);
            int csize_array = csize_t::make_new(1ll, 0ll, 1ll, -1, -1);
            return new UnionFind(init_comps, init_comps, csize_array, par_array);
        }

        UnionFind(ll a_num_comps, ll a_num_nodes, int a_csize, int a_par): _num_comps(a_num_comps), _num_nodes(a_num_nodes), _csize(a_csize), _par(a_par) {
            // cout << "UF: " << a_csize << " " << a_par << endl;
        }

        ll find(ll i) {
            while(i != iarrn[_par].at(i)) {
                i = iarrn[_par].at(i);
                // cout << "E " << i << endl;
            }
            // cout << _par << " " << iarrn.size() << endl;

            return i;
        }

        bool conn(ll i, ll j) {
            return find(i) == find(j);
        }

        UnionFind* unify(ll i, ll j) {
            ll pari = find(i), parj = find(j);
            // uarrn[_csize].print();
            if(pari == parj) return this;

            // cout << "HAHA " << pari << " " << parj << endl;
            ll isize = uarrn[_csize].at(pari), jsize = uarrn[_csize].at(parj);

            int combined_csize = jsize + isize;
            if(isize < jsize) {
                int new_arr = uarrn[_csize].set(parj, combined_csize);
                // uarrn[new_arr].print();
                int new_par = iarrn[_par].set(pari, parj);
                return new UnionFind(_num_comps - 1, _num_nodes, new_arr, new_par);
            } else {
                int new_arr = uarrn[_csize].set(pari, combined_csize);
                // uarrn[new_arr].print();
                int new_par = iarrn[_par].set(parj, pari);
                return new UnionFind(_num_comps - 1, _num_nodes, new_arr, new_par);
            }
        }

        UnionFind* create_vertices(ll k) {
            // par_t* new_par = _par; // ! WARNING: This might bite you back in a bit
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
            cout << (s.top()->conn(u, v) ? "SAIKAI" : "KONAI SAIKAI") << endl;
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

    // cout << num_nodes << "\n";

    cout << flush;

    return 0;
}