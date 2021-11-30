#ifndef FELIX_SPARSETABLE_HPP
#define FELIX_SPARSETABLE_HPP 1

#include <vector>
#include <cassert>
#include <functional>

namespace felix {

// usage:
//   auto cmp = [&](int i, int j) { return min(i, j); };
//   SparseTable<int, decltype(cmp)> st(a, cmp);
// or:
//   SparseTable<int> st(a, [&](int i, int j) { return min(i, j); });
template<class T, class F = std::function<T(const T&, const T&)>>
class sparse_table {
public:
    int n;
    std::vector<std::vector<T>> mat;
    F func;
    
    sparse_table(const std::vector<T>& a, const F& f) : func(f) {
        n = static_cast<int>(a.size());
        int max_log = 32 - __builtin_clz(n);
        mat.resize(max_log);
        mat[0] = a;
        for(int j = 1; j < max_log; ++j) {
            mat[j].resize(n - (1 << j) + 1);
            for(int i = 0; i <= n - (1 << j); ++i)
                mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
        }
    }

    T prod(int from, int to) const {
        assert(0 <= from && from <= to && to <= n - 1);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
    }
};

} // namespace felix

#endif // FELIX_SPARSETABLE_HPP
