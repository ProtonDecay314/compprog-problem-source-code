#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

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

int main() {
    typedef UnityArray* ua;
    ua u = new UnityArray(1, 0, 100, nullptr, nullptr);

    cout << u->at(0) << endl;
    cout << u->at(2) << endl;
    cout << u->at(10) << endl;

    ua u1 = u->set(10, 20);

    cout << u1->at(0) << endl;
    cout << u1->at(2) << endl;
    cout << u1->at(10) << endl;

    ua u2 = u->set(2, 30);

    cout << u2->at(0) << endl;
    cout << u2->at(2) << endl;
    cout << u2->at(10) << endl;

    return 0;
}