#ifndef FELIX_RANDOM_HPP
#define FELIX_RANDOM_HPP 1

#include <chrono>

namespace felix {

class random_t {
public:
	uint64_t x, y, z, w, seed;

	random_t() : random_t(std::chrono::steady_clock::now().time_since_epoch().count()) {}

	random_t(uint64_t s) : x(s), y(10429282927ULL), z(38375863771ULL), w(772983891197ULL), seed(s) {}

	inline void set_seed(uint64_t s) {
		*this = random_t(s);
	}

	inline void reset() {
		set_seed(seed);
	}

	inline uint64_t next() {
		uint64_t t = x;
		t ^= t << 11;
		t ^= t >> 8;
		x = y, y = z, z = w;
		w ^= w >> 19;
		w ^= t;
		return w;
	}

	inline uint64_t next(uint64_t a) {
		return next() % a;
	}

	inline uint64_t next(uint64_t a, uint64_t b) {
		return a + next(b - a + 1);
	}

	inline long double nextDouble() {
		return ((unsigned int) next()) / 4294967295.0;
	}

	inline long double nextDouble(long double a) {
		return nextDouble() * a;
	}

	inline long double nextDouble(long double a, long double b) {
		return a + nextDouble() * (b - a);
	}

	template<class T>
	void shuffle(std::vector<T>& a) {
		for(int i = int(a.size()) - 1; i; --i)
			std::swap(a[i], a[next(i + 1)]);
	}
};

random_t rnd;

} // namespace felix

#endif // FELIX_RANDOM_HPP
