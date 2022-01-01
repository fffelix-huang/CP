#ifndef FELIX_ALGEBRA_HPP
#define FELIX_ALGEBRA_HPP 1

#include <vector>
#include <tuple>
#include <cmath>
#include <numeric>

namespace felix {

// for ax + by = c, return {a, b, c}
std::tuple<long long, long long, long long> ext_gcd(long long x, long long y) {
	if(y == 0)
		return {1, 0, x};
	std::tuple<long long, long long, long long> result = ext_gcd(y, x % y);
	return {std::get<1>(result), std::get<0>(result) - std::get<1>(result) * (x / y), std::get<2>(result)};
}

// Calculate x is prime or not in O(sqrt(n))
bool is_prime(long long x) {
	if(x & 1) {
		for(long long i = 3; i * i <= x; i += 2)
			if(x % i == 0)
				return false;
		return true;
	} else
		return x == 2;
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

inline long long mod_inv(long long d, long long m) {
	return std::get<0>(ext_gcd(d, m));
}

// Calculate modular inverse for mod m up to n in O(n)
std::vector<int> mod_inv_in_range(int m, int n = -1) {
	assert(n < m);
	if(n == -1)
		n = m - 1;
	std::vector<int> inv(n + 1);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = m - (m / i) * inv[m % i] % m;
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

} // namespace felix

#endif // FELIX_ALGEBRA_HPP
