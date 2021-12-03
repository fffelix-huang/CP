#ifndef FELIX_HASH_HPP
#define FELIX_HASH_HPP 1

#include <vector>
#include <cassert>
#include <felix/modint>

namespace felix {

template<int A, int B>
class Hashed_String {
public:
    using mint = felix::static_modint<B>;
    int n;
    std::string str;
    std::vector<mint> value, pows;

    Hashed_String() {}

    Hashed_String(std::string _s): n(int(_s.size())), str(_s), value(std::vector<mint>(n)), pows(std::vector<mint>(n)) {
        value[0] = str[0];
        pows[0] = 1;
        for(int i = 1; i < n; ++i) {
            value[i] = value[i - 1] * A + str[i];
            pows[i] = pows[i - 1] * A;
        }
    }
    
    inline mint get(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        if(!l)
            return value[r];
        return value[r] - value[l - 1] * pows[r - l + 1];
    }
    
    inline mint id() const {
        return value.back();
    }
};

} // namespace felix

#endif // FELIX_HASH_HPP
