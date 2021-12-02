#ifndef FELIX_RANDOM_HPP
#define FELIX_RANDOM_HPP 1

namespace felix {

class random_t {
public:
    using ull = uint64_t;
    ull x, y, z, w;

    random_t(ull seed = 0) : x(seed), y(10429282927ULL), z(38375863771ULL), w(772983891197ULL) {}

    inline void set_seed(ull seed) {
        x = seed;
        y = (seed * 1000000009) ^ (seed >> 8);
        z = (seed * 976865423) ^ (seed >> 17);
        w = (seed * seed) ^ (seed << 13);
    }

    inline ull next() {
        ull t = x;
        t ^= t << 11;
        t ^= t >> 8;
        x = y, y = z, z = w;
        w ^= w >> 19;
        w ^= t;
        return w;
    }

    inline ull next(ull a) {
        return next() % a;
    }

    inline ull next(ull a, ull b) {
        return a + next(b - a + 1);
    }
};

} // namespace felix

#endif // FELIX_RANDOM_HPP
