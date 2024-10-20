#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

struct IdentityAssigner {
    static ll at(ll i) {
        return i;
    }
};

struct UnityAssigner {
    static ll at(ll i) {
        return 1ll;
    }
};

// An Infinite, Persistent Array
template<typename T, typename DEF>
class Array {
    private:
        Array* _odd;
        Array* _even;
        T _v;
        ll _i;
        ll _pow_t_mult;
    
    public:
        Array<T, DEF>(ll a_pow_t_mult, ll a_i, T a_v, Array* a_odd, Array* a_even): _pow_t_mult(a_pow_t_mult), _i(a_i), _v(a_v), _odd(a_odd), _even(a_even) {}

        Array<T, DEF>* odd() {
            if(_odd == nullptr) {
                _odd = new Array<T, DEF>(_pow_t_mult << 1, _i + _pow_t_mult, DEF::at(_i + _pow_t_mult), nullptr, nullptr);
            }
            return _odd;
        }

        Array<T, DEF>* even() {
            if(_even == nullptr) {
                _even = new Array<T, DEF>(_pow_t_mult << 1, _i + (_pow_t_mult << 1), DEF::at(_i + (_pow_t_mult << 1)), nullptr, nullptr);
            }
            return _even;
        }

        T at(ll i) {
            if(i == 0) return _v;
            else if(i&1) return odd()->at((i - 1) >> 1);
            else return even()->at((i - 1) >> 1);
        }

        Array<T, DEF>* set(ll i, T nv) {
            if(i == 0) return new Array<T, DEF>(_pow_t_mult, _i, nv, _odd, _even);
            else if(i&1) return new Array<T, DEF>(_pow_t_mult, _i, _v, odd()->set((i - 1) >> 1, nv), _even); // ! CAREFUL, you initially returned the pointer to the odd partition, but you had to RETURN EVERYTHING
            else return new Array<T, DEF>(_pow_t_mult, _i, _v, _odd, even()->set((i - 1) >> 1, nv));
        }
};

// A Persistent Union Find that uses a Persistent Array
class UnionFind {
    public:
        typedef Array<ll, UnityAssigner> csize_t;
        typedef Array<ll, IdentityAssigner> par_t;
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
            par_t* new_par = _par;
            return new UnionFind(_num_comps + k, _num_nodes + k, _csize, new_par);
        }
};