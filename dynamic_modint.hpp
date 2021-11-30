#ifndef FELIX_MODINT_HPP
#define FELIX_MODINT_HPP 1

#include <iostream>
#include <cstring>
#include <cassert>

namespace felix {

template <typename T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while(a != 0) {
        T t = m / a;
        m -= t * a; std::swap(a, m);
        u -= t * v; std::swap(u, v);
    }
    assert(m == 1);
    return u;
}

template<int& MD>
class dynamic_modint {
public:
    static constexpr int& MOD = MD;

    dynamic_modint() : value(0) {}

    template<class T>
    dynamic_modint(const T& x) {
        value = normalize(x);
    }

    template<class T>
    inline int normalize(T x) {
        if(-MOD > x || x >= MOD)
            x %= MOD;
        if(x < 0)
            x += MOD;
        return x;
    }

    inline const int& operator()() const { return value; }
    template<class T> inline explicit operator T() const { return static_cast<T>(value); }

    inline dynamic_modint& operator+=(const dynamic_modint& other) { if((value += other.value) >= MOD) value -= MOD; return *this; }
    inline dynamic_modint& operator-=(const dynamic_modint& other) { if((value -= other.value) < 0) value += MOD; return *this; }
    inline dynamic_modint& operator*=(const dynamic_modint& other) { value = normalize(int64_t(value) * other.value); return *this; }
    inline dynamic_modint& operator/=(const dynamic_modint& other) { return *this *= dynamic_modint(inverse(other.value, MOD)); }
    template<class T> inline dynamic_modint& operator+=(const T& other) { return *this += dynamic_modint(other); }
    template<class T> inline dynamic_modint& operator-=(const T& other) { return *this -= dynamic_modint(other); }
    template<class T> inline dynamic_modint& operator*=(const T& other) { return *this *= dynamic_modint(other); }
    template<class T> inline dynamic_modint& operator/=(const T& other) { return *this /= dynamic_modint(other); }
    inline dynamic_modint& operator++() { return *this += 1; }
    inline dynamic_modint& operator--() { return *this -= 1; }
    inline dynamic_modint operator++(int) { dynamic_modint result(*this); *this += 1; return result; }
    inline dynamic_modint operator--(int) { dynamic_modint result(*this); *this -= 1; return result; }
    inline dynamic_modint operator-() const { return dynamic_modint(-value); }

    inline dynamic_modint& operator<<=(const size_t& N) { value = normalize(int64_t(value) << N); return *this; }
    inline dynamic_modint& operator>>=(const size_t& N) { value = normalize(int64_t(value) >> N); return *this; }

    friend const int& abs(const dynamic_modint& other) { return other.value; }

    template<int& MOD> friend inline bool operator==(const dynamic_modint<MOD>& lhs, const dynamic_modint<MOD>& rhs) { return lhs.value == rhs.value; }
    template<int& MOD, class T> friend inline bool operator==(const dynamic_modint<MOD>& lhs, T rhs) { return lhs.value == dynamic_modint<MOD>(rhs); }
    template<int& MOD, class T> friend inline bool operator==(const T lhs, const dynamic_modint<MOD>& rhs) { return dynamic_modint<MOD>(lhs) == rhs; }

    template<int& MOD> friend inline bool operator!=(const dynamic_modint<MOD>& lhs, const dynamic_modint<MOD>& rhs) { return !(lhs == rhs); }
    template<int& MOD, class T> friend inline bool operator!=(const dynamic_modint<MOD>& lhs, T rhs) { return !(lhs == rhs); }
    template<int& MOD, class T> friend inline bool operator!=(const T lhs, const dynamic_modint<MOD>& rhs) { return !(lhs == rhs); }

    template<int& MOD> friend inline bool operator<(const dynamic_modint<MOD>& lhs, const dynamic_modint<MOD>& rhs) { return lhs.value < rhs.value; }
    template<int& MOD> friend inline bool operator<=(const dynamic_modint<MOD>& lhs, const dynamic_modint<MOD>& rhs) { return lhs.value <= rhs.value; }
    template<int& MOD> friend inline bool operator>(const dynamic_modint<MOD>& lhs, const dynamic_modint<MOD>& rhs) { return lhs.value > rhs.value; }
    template<int& MOD> friend inline bool operator>=(const dynamic_modint<MOD>& lhs, const dynamic_modint<MOD>& rhs) { return lhs.value >= rhs.value; }

    template<int& MOD> dynamic_modint<MOD> friend inline operator+(const dynamic_modint<MOD>& lhs, const dynamic_modint<MOD>& rhs) { return dynamic_modint<MOD>(lhs) += rhs; }
    template<int& MOD, class T> dynamic_modint<MOD> friend inline operator+(const dynamic_modint<MOD>& lhs, T rhs) { return dynamic_modint<MOD>(lhs) += rhs; }
    template<int& MOD, class T> dynamic_modint<MOD> friend inline operator+(T lhs, const dynamic_modint<MOD>& rhs) { return dynamic_modint<MOD>(lhs) += rhs; }

    template<int& MOD> dynamic_modint<MOD> friend inline operator-(const dynamic_modint<MOD>& lhs, const dynamic_modint<MOD>& rhs) { return dynamic_modint<MOD>(lhs) -= rhs; }
    template<int& MOD, class T> dynamic_modint<MOD> friend inline operator-(const dynamic_modint<MOD>& lhs, T rhs) { return dynamic_modint<MOD>(lhs) -= rhs; }
    template<int& MOD, class T> dynamic_modint<MOD> friend inline operator-(T lhs, const dynamic_modint<MOD>& rhs) { return dynamic_modint<MOD>(lhs) -= rhs; }

    template<int& MOD> dynamic_modint<MOD> friend inline operator*(const dynamic_modint<MOD>& lhs, const dynamic_modint<MOD>& rhs) { return dynamic_modint<MOD>(lhs) *= rhs; }
    template<int& MOD, class T> dynamic_modint<MOD> friend inline operator*(const dynamic_modint<MOD>& lhs, T rhs) { return dynamic_modint<MOD>(lhs) *= rhs; }
    template<int& MOD, class T> dynamic_modint<MOD> friend inline operator*(T lhs, const dynamic_modint<MOD>& rhs) { return dynamic_modint<MOD>(lhs) *= rhs; }

    template<int& MOD> dynamic_modint<MOD> friend inline operator/(const dynamic_modint<MOD>& lhs, const dynamic_modint<MOD>& rhs) { return dynamic_modint<MOD>(lhs) /= rhs; }
    template<int& MOD, class T> dynamic_modint<MOD> friend inline operator/(const dynamic_modint<MOD>& lhs, T rhs) { return dynamic_modint<MOD>(lhs) /= rhs; }
    template<int& MOD, class T> dynamic_modint<MOD> friend inline operator/(T lhs, const dynamic_modint<MOD>& rhs) { return dynamic_modint<MOD>(lhs) /= rhs; }

    template<int& MOD> dynamic_modint<MOD> friend inline operator<<(const dynamic_modint<MOD>& lhs, const size_t& rhs) { return dynamic_modint<MOD>(lhs) <<= rhs; }
    template<int& MOD> dynamic_modint<MOD> friend inline operator>>(const dynamic_modint<MOD>& lhs, const size_t& rhs) { return dynamic_modint<MOD>(lhs) >>= rhs; }

    template<int& MOD> friend inline std::string to_string(const dynamic_modint<MOD>& x) { return to_string(x.value); }

    template<int& MOD, class T> inline dynamic_modint<MOD> power(dynamic_modint<MOD> a, T b) { assert(b >= 0); dynamic_modint<MOD> ans = 1; while(b) { if(b & 1) ans *= a; a *= a; b >>= 1; } return ans; }

    template<class T, int& MOD> friend inline T& operator>>(T& in, dynamic_modint<MOD>& x) { int64_t temp; in >> temp; x.value = x.normalize(temp); return in; }

    template<class T, int& MOD> friend inline T& operator<<(T& out, const dynamic_modint<MOD>& x) { return out << x.value; }

private:
    int value;
};

} // namespace felix

#endif // FELIX_MODINT_HPP
