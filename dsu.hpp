#ifndef FELIX_DSU_HPP
#define FELIX_DSU_HPP 1

#include <vector>
#include <cassert>

namespace felix {

// 0-based index
class dsu {
public:
    int n, groups;
    std::vector<int> _size;
    
    dsu() {}

    dsu(int _n) : n(_n), groups(_n), _size(std::vector<int>(n, -1)) {}
    
    inline int leader(int u) {
        assert(0 <= u && u < n);
        return (_size[u] < 0 ? u : (_size[u] = leader(_size[u])));
    }
    
    bool merge(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        a = leader(a);
        b = leader(b);
        if(a == b)
            return false;
        if(-_size[a] < -_size[b])
            std::swap(a, b);
        _size[a] += _size[b];
        _size[b] = a;
        --groups;
        return true;
    }
    
    inline int size(int u) {
        assert(0 <= u && u < n);
        return -_size[leader(u)];
    }

    inline int group() {
        return groups;
    }

    inline bool same(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        return leader(a) == leader(b);
    }
};

} // namespace felix

#endif // FELIX_DSU_HPP
