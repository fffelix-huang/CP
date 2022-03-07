#ifndef FELIX_ALGEBRA_HPP
#define FELIX_ALGEBRA_HPP 1

#include <vector>
#include <tuple>
#include <cmath>
#include <numeric>
#include <cassert>
#include <algorithm>
#include "felix/math.hpp"
#include "felix/modint.hpp"

namespace felix {

// for ax + by = gcd(a, b), return {a, b, gcd(a, b)}
std::tuple<long long, long long, long long> ext_gcd(long long x, long long y) {
	if(y == 0)
		return {1, 0, x};
	std::tuple<long long, long long, long long> result = ext_gcd(y, x % y);
	return {std::get<1>(result), std::get<0>(result) - std::get<1>(result) * (x / y), std::get<2>(result)};
}

template<class T>
T mod_inv(T a, T m) {
	T u = 0, v = 1;
	while(a != 0) {
		T t = m / a;
		m -= t * a; std::swap(a, m);
		u -= t * v; std::swap(u, v);
	}
	assert(m == 1);
	return u;
}

// Calculate modular inverse for mod m up to n in O(n)
std::vector<int> mod_inv_in_range(int m, int n = -1) {
	assert(n < m);
	if(n == -1)
		n = m - 1;
	std::vector<int> inv(n + 1);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = m - (long long) (m / i) * inv[m % i] % m;
	return inv;
}

// Calculate euler's totient function in O(sqrt(n))
long long phi_function(long long n) {
	long long ans = n;
	if(!(n & 1)) {
		do
			n >>= 1;
		while(!(n & 1));
		ans /= 2;
	}
	for(long long i = 3; i * i <= n; i += 2) {
		if(n % i == 0) {
			do
				n /= i;
			while(n % i == 0);
			ans -= ans / i;
		}
	}
	if(n > 1)
		ans -= ans / n;
	return ans;
}

// Calculate Euler's totient function using sieve in O(n * log(log(n)))
std::vector<int> phi_sieve(int n) {
	std::vector<int> phi(n + 1);
	std::iota(phi.begin(), phi.end(), 0);
	for(int i = 2; i <= n; ++i)
		if(phi[i] == i)
			for(int j = i; j <= n; j += i)
				phi[j] -= phi[j] / i;
	return phi;
}

// Miller Rabin Primality Test
template<class T>
bool is_prime(T n, const std::vector<T>& bases) {
	if(n <= 2)
		return n == 2;
	std::vector<short> small_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
	for(const T& x : small_primes)
		if(n % x == 0)
			return n == x;
	if(n < 37 * 37)
		return true;
	int s = __builtin_ctz(n - 1);
	T d = (n - 1) >> s;
	using mint = dynamic_modint<1283842941>;
	mint::set_mod(n);
	for(const T& a : bases) {
		if(a % n == 0)
			continue;
		mint cur = a;
		cur = power(cur, d);
		if(int(cur()) == 1)
			continue;
		bool witness = true;
		for(int rep = 0; rep < s; ++rep) {
			if(int(cur()) == n - 1) {
				witness = false;
				break;
			}
			cur *= cur;
		}
		if(witness)
			return false;
	}
	return true;
}

bool is_prime(int n) {
	return is_prime(n, {2, 7, 61});
}

bool is_prime(long long n) {
	return is_prime(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}

// Run Sieve of Eratosthenes up to n in O(n * log(log(n)))
std::vector<bool> prime_sieve(int n) {
	const int m = sqrt(n) + 1;
	std::vector<bool> isprime(n + 1, true);
	isprime[0] = isprime[1] = false;
	for(int i = 4; i <= n; i += 2)
		isprime[i] = false;
	for(int i = 3; i <= m; i += 2)
		if(isprime[i])
			for(int j = i * i; j <= n; j += i << 1)
				isprime[j] = false;
	return isprime;
}

} // namespace felix

#endif // FELIX_ALGEBRA_HPP
