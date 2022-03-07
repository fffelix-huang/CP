#ifndef FELIX_INTERNAL_MATH_HPP
#define FELIX_INTERNAL_MATH_HPP 1

#include <utility>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace felix {

namespace internal {

// @param m `1 <= m`
// @return x mod m
constexpr long long safe_mod(long long x, long long m) {
	x %= m;
	if (x < 0) x += m;
	return x;
}

// Fast modular multiplication by barrett reduction
// Reference: https://en.wikipedia.org/wiki/Barrett_reduction
// NOTE: reconsider after Ice Lake
class barrett {
public:
	unsigned int m;
	unsigned long long im;

	// @param m `1 <= m < 2^31`
	explicit barrett(unsigned int _m) : m(_m), im((unsigned long long)(-1) / _m + 1) {}

	// @return m
	unsigned int umod() const { return m; }

	// @param a `0 <= a < m`
	// @param b `0 <= b < m`
	// @return `a * b % m`
	unsigned int mul(unsigned int a, unsigned int b) const {
		// [1] m = 1
		// a = b = im = 0, so okay

		// [2] m >= 2
		// im = ceil(2^64 / m)
		// -> im * m = 2^64 + r (0 <= r < m)
		// let z = a*b = c*m + d (0 <= c, d < m)
		// a*b * im = (c*m + d) * im = c*(im*m) + d*im = c*2^64 + c*r + d*im
		// c*r + d*im < m * m + m * im < m * m + 2^64 + m <= 2^64 + m * (m + 1) < 2^64 * 2
		// ((ab * im) >> 64) == c or c + 1
		unsigned long long z = a;
		z *= b;
#ifdef _MSC_VER
		unsigned long long x;
		_umul128(z, im, &x);
#else
		unsigned long long x = (unsigned long long)(((unsigned __int128)(z) * im) >> 64);
#endif
		unsigned int v = (unsigned int)(z - x * m);
		if(m <= v)
			v += m;
		return v;
	}
};

// @param n `n < 2^32`
// @param m `1 <= m < 2^32`
// @return sum_{i=0}^{n-1} floor((ai + b) / m) (mod 2^64)
unsigned long long floor_sum_unsigned(unsigned long long n, unsigned long long m, unsigned long long a, unsigned long long b) {
	unsigned long long ans = 0;
	while(true) {
		if(a >= m) {
			ans += n * (n - 1) / 2 * (a / m);
			a %= m;
		}
		if(b >= m) {
			ans += n * (b / m);
			b %= m;
		}
		unsigned long long y_max = a * n + b;
		if(y_max < m)
			break;
		// y_max < m * (n + 1)
		// floor(y_max / m) <= n
		n = (unsigned long long)(y_max / m);
		b = (unsigned long long)(y_max % m);
		std::swap(m, a);
	}
	return ans;
}

} // namespace internal

} // namespace felix

#endif // FELIX_INTERNAL_MATH_HPP
