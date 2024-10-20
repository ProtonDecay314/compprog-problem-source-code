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
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 99999);
    
    typedef UnityArray ua;
    vector<ll> arr(100000, 0ll);
    int uptr = UnityArray::make_new(1, 0, 0, -1, -1);

    ll offset = 1000000000ll;

    for(ll i = 0; i < 20000; i++) {
        int ind = dist(rng);
        int val = dist(rng);

        uptr = uarrn[uptr].set(ind + offset, val);
        arr[ind] = val;
    }

    for(ll i = 0; i < 100000; i++) {
        if(uarrn[uptr].at(i + offset) != arr[i]) {
            cout << "FAIL: Index " << i << ", " << uarrn[uptr].at(i + offset) << " != " << arr[i] << endl;
        }
    }

    cout << "ok 10000 numbers" << endl;

    return 0;
}