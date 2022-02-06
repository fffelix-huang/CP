#ifndef FELIX_MATH_HPP
#define FELIX_MATH_HPP 1

#include <cassert>
#include "felix/internal_math.hpp"

namespace felix {

template<class T>
T power(T a, unsigned long long b) {
	assert(b >= 0);
	T ans = 1;
	while(b) {
		if(b & 1)
			ans *= a;
		a *= a;
		b >>= 1;
	}
	return ans;
}

long long floor_sum(long long n, long long m, long long a, long long b) {
    assert(0 <= n && n < (1LL << 32));
    assert(1 <= m && m < (1LL << 32));
    unsigned long long ans = 0;
    if (a < 0) {
        unsigned long long a2 = internal::safe_mod(a, m);
        ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);
        a = a2;
    }
    if (b < 0) {
        unsigned long long b2 = internal::safe_mod(b, m);
        ans -= 1ULL * n * ((b2 - b) / m);
        b = b2;
    }
    return ans + internal::floor_sum_unsigned(n, m, a, b);
}

} // namespace felix

#endif // FELIX_MATH_HPP
