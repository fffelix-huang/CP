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

template<int MD>
class static_modint {
public:
    static_assert(MD > 0, "MOD must be positive");

    static constexpr int MOD = MD;

    static_modint() : value(0) {}

    template<class T>
    static_modint(const T& x) {
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

    inline static_modint& operator+=(const static_modint& other) { if((value += other.value) >= MOD) value -= MOD; return *this; }
    inline static_modint& operator-=(const static_modint& other) { if((value -= other.value) < 0) value += MOD; return *this; }
    inline static_modint& operator*=(const static_modint& other) { value = normalize(int64_t(value) * other.value); return *this; }
    inline static_modint& operator/=(const static_modint& other) { return *this *= static_modint(inverse(other.value, MOD)); }
    template<class T> inline static_modint& operator+=(const T& other) { return *this += static_modint(other); }
    template<class T> inline static_modint& operator-=(const T& other) { return *this -= static_modint(other); }
    template<class T> inline static_modint& operator*=(const T& other) { return *this *= static_modint(other); }
    template<class T> inline static_modint& operator/=(const T& other) { return *this /= static_modint(other); }
    inline static_modint& operator++() { return *this += 1; }
    inline static_modint& operator--() { return *this -= 1; }
    inline static_modint operator++(int) { static_modint result(*this); *this += 1; return result; }
    inline static_modint operator--(int) { static_modint result(*this); *this -= 1; return result; }
    inline static_modint operator-() const { return static_modint(-value); }

    inline static_modint& operator<<=(const size_t& N) { value = normalize(int64_t(value) << N); return *this; }
    inline static_modint& operator>>=(const size_t& N) { value = normalize(int64_t(value) >> N); return *this; }

    friend const int& abs(const static_modint& other) { return other.value; }

    template<int MOD> friend inline bool operator==(const static_modint<MOD>& lhs, const static_modint<MOD>& rhs) { return lhs.value == rhs.value; }
    template<int MOD, class T> friend inline bool operator==(const static_modint<MOD>& lhs, T rhs) { return lhs.value == static_modint<MOD>(rhs); }
    template<int MOD, class T> friend inline bool operator==(const T lhs, const static_modint<MOD>& rhs) { return static_modint<MOD>(lhs) == rhs; }

    template<int MOD> friend inline bool operator!=(const static_modint<MOD>& lhs, const static_modint<MOD>& rhs) { return !(lhs == rhs); }
    template<int MOD, class T> friend inline bool operator!=(const static_modint<MOD>& lhs, T rhs) { return !(lhs == rhs); }
    template<int MOD, class T> friend inline bool operator!=(const T lhs, const static_modint<MOD>& rhs) { return !(lhs == rhs); }

    template<int MOD> friend inline bool operator<(const static_modint<MOD>& lhs, const static_modint<MOD>& rhs) { return lhs.value < rhs.value; }
    template<int MOD> friend inline bool operator<=(const static_modint<MOD>& lhs, const static_modint<MOD>& rhs) { return lhs.value <= rhs.value; }
    template<int MOD> friend inline bool operator>(const static_modint<MOD>& lhs, const static_modint<MOD>& rhs) { return lhs.value > rhs.value; }
    template<int MOD> friend inline bool operator>=(const static_modint<MOD>& lhs, const static_modint<MOD>& rhs) { return lhs.value >= rhs.value; }

    template<int MOD> static_modint<MOD> friend inline operator+(const static_modint<MOD>& lhs, const static_modint<MOD>& rhs) { return static_modint<MOD>(lhs) += rhs; }
    template<int MOD, class T> static_modint<MOD> friend inline operator+(const static_modint<MOD>& lhs, T rhs) { return static_modint<MOD>(lhs) += rhs; }
    template<int MOD, class T> static_modint<MOD> friend inline operator+(T lhs, const static_modint<MOD>& rhs) { return static_modint<MOD>(lhs) += rhs; }

    template<int MOD> static_modint<MOD> friend inline operator-(const static_modint<MOD>& lhs, const static_modint<MOD>& rhs) { return static_modint<MOD>(lhs) -= rhs; }
    template<int MOD, class T> static_modint<MOD> friend inline operator-(const static_modint<MOD>& lhs, T rhs) { return static_modint<MOD>(lhs) -= rhs; }
    template<int MOD, class T> static_modint<MOD> friend inline operator-(T lhs, const static_modint<MOD>& rhs) { return static_modint<MOD>(lhs) -= rhs; }

    template<int MOD> static_modint<MOD> friend inline operator*(const static_modint<MOD>& lhs, const static_modint<MOD>& rhs) { return static_modint<MOD>(lhs) *= rhs; }
    template<int MOD, class T> static_modint<MOD> friend inline operator*(const static_modint<MOD>& lhs, T rhs) { return static_modint<MOD>(lhs) *= rhs; }
    template<int MOD, class T> static_modint<MOD> friend inline operator*(T lhs, const static_modint<MOD>& rhs) { return static_modint<MOD>(lhs) *= rhs; }

    template<int MOD> static_modint<MOD> friend inline operator/(const static_modint<MOD>& lhs, const static_modint<MOD>& rhs) { return static_modint<MOD>(lhs) /= rhs; }
    template<int MOD, class T> static_modint<MOD> friend inline operator/(const static_modint<MOD>& lhs, T rhs) { return static_modint<MOD>(lhs) /= rhs; }
    template<int MOD, class T> static_modint<MOD> friend inline operator/(T lhs, const static_modint<MOD>& rhs) { return static_modint<MOD>(lhs) /= rhs; }

    template<int MOD> static_modint<MOD> friend inline operator<<(const static_modint<MOD>& lhs, const size_t& rhs) { return static_modint<MOD>(lhs) <<= rhs; }
    template<int MOD> static_modint<MOD> friend inline operator>>(const static_modint<MOD>& lhs, const size_t& rhs) { return static_modint<MOD>(lhs) >>= rhs; }

    template<int MOD> friend inline std::string to_string(const static_modint<MOD>& x) { return to_string(x.value); }

    template<int MOD, class T> inline static_modint<MOD> power(static_modint<MOD> a, T b) { assert(b >= 0); static_modint<MOD> ans = 1; while(b) { if(b & 1) ans *= a; a *= a; b >>= 1; } return ans; }

    template<class T, int MOD> friend inline T& operator>>(T& in, static_modint<MOD>& x) { int64_t temp; in >> temp; x.value = x.normalize(temp); return in; }

    template<class T, int MOD> friend inline T& operator<<(T& out, const static_modint<MOD>& x) { return out << x.value; }

private:
    int value;
};

} // namespace felix

#endif // FELIX_MODINT_HPP
