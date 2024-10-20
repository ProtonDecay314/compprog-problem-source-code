#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

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

UnityArray uarrn[10000000];
static int uarrnsz = 0;

UnityArray::UnityArray(ll a_pow_t_mult, ll a_i, ll a_v, int a_odd, int a_even): _pow_t_mult(a_pow_t_mult), _i(a_i), _v(a_v), _odd(a_odd), _even(a_even) {};

int UnityArray::make_new(ll a_pow_t_mult, ll a_i, ll a_v, int a_odd, int a_even) {
    UnityArray newua(a_pow_t_mult, a_i, a_v, a_odd, a_even);
    uarrn[uarrnsz] = newua;
    int ind = uarrnsz;
    uarrnsz++;
    // cout << "MAKING " << ind << endl;
    // uarrn[ind].print();
    return ind;
}

int UnityArray::odd() {
    if(_odd == -1) {
        _odd = UnityArray::make_new(_pow_t_mult << 1ll, _i + _pow_t_mult, 0ll, -1, -1);
    }
    return _odd;
}

int UnityArray::even() {
    if(_even == -1) {
        _even = UnityArray::make_new(_pow_t_mult << 1ll, _i + (_pow_t_mult << 1ll), 0ll, -1, -1);
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

int main() {
    std::random_device dev;
    std::mt19937 rng(dev());
    typedef std::uniform_int_distribution<std::mt19937::result_type> unif_var;
    unif_var dist(0, 999);
    
    typedef UnityArray ua;
    vector<vector<ll>> versions;
    vector<ll> uaversions;
    int uptr = UnityArray::make_new(1, 0, 0, -1, -1);
    uaversions.push_back(uptr);
    vector<ll> first_version(1000, 0ll);
    versions.push_back(first_version);

    ll offset = 1000000000ll;

    for(ll i = 0; i < 2000; i++) {
        int ind = dist(rng);
        int val = dist(rng);
        unif_var verdist(0, versions.size() - 1);
        int ver = verdist(rng);

        versions.push_back(versions[ver]);
        uaversions.push_back(uarrn[uaversions[ver]].set(ind + offset, val));

        versions[versions.size() - 1][ind] = val;
    }

    for(ll j = 0; j < 2000ll; j++) {
        for(ll i = 0; i < 1000; i++) {
            cout << versions[j][i] << "\n";
            if(uarrn[uaversions[j]].at(i + offset) != versions[j][i]) {
                cout << "FAIL: Index " << i << ", " << uarrn[uaversions[j]].at(i + offset) << " != " << versions[j][i] << endl;
            }
        }
    }

    cout << "ok " << 2000 * 1000 << " numbers" << endl;

    return 0;
}