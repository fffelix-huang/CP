#ifndef FELIX_FENWICK_HPP
#define FELIX_FENWICK_HPP 1

#include <cassert>
#include <vector>

namespace felix {

template<class T>
class fenwick {
public:
    fenwick() : fenwick(0) {}

    fenwick(int _n) : n(_n), data(_n + 1) {}

    void add(int p, T x) {
        assert(0 < p && p <= n);
        while(p <= n) {
            data[p] += x;
            p += p & -p;
        }
    }

    T sum(int l, int r) const {
        assert(0 < l && l <= r && r <= n);
        return sum(r) - sum(l - 1);
    }

private:
    int n;
    std::vector<T> data;

    T sum(int r) const {
        T s = 0;
        while(r > 0) {
            s += data[r];
            r -= r & -r;
        }
        return s;
    }
};

} // namespace felix

#endif // FELIX_FENWICK_HPP
