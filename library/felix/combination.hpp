#ifndef FELIX_COMBINATION_HPP
#define FELIX_COMBINATION_HPP 1

#include <vector>
#include <felix/modint>

namespace felix {

template<int MOD>
class combination {
public:
    using mint = felix::static_modint<MOD>;

    std::vector<mint> fact, inv_fact;

    inline void update(int n) {
        while(int(fact.size()) <= n) {
            fact.push_back(fact.back() * int(fact.size()));
            inv_fact.push_back(1 / fact.back());
        }
    }

    combination() : fact(std::vector<mint>(1, 1)), inv_fact(std::vector<mint>(1, 1)) {}

    combination(int n) {
        assert(n >= 0);
        fact.reserve(n + 1);
        inv_fact.reserve(n + 1);
        fact.push_back(1);
        inv_fact.push_back(1);
        update(n);
    }

    inline mint C(int n, int k) const {
        assert(n >= 0);
        if(k < 0 || k > n)
            return 0;
        update(n);
        return fact[n] * inv_fact[k] * inv_fact[n - k];
    }

    inline mint P(int n, int k) const {
        assert(n >= 0);
        if(k < 0 || k > n)
            return 0;
        update(n);
        return fact[n] * inv_fact[n - k];
    }

    inline int size() const {
        return int(fact.size());
    }
};

} // namespace felix

#endif // FELIX_COMBINATION_HPP
