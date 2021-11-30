#ifndef FELIX_HASH_HPP
#define FELIX_HASH_HPP 1

#include <vector>
#include <cassert>
#include <felix/modint>

namespace felix {

// A - multiple
// B - modulo
// sample prime pairs:
/*
998244679 1000003133
998246189 1000001917
998257303 1000099297
998258507 1000022081
1000095983 1000096913
1000104517 1000111103
1000119821 1000122007
1000122727 1000122737
1000123247 1000124627
1000127417 1000130011
*/
// it's safer to use mutiple hash values
template<int A, int B>
class Hashed_String {
public:
    using Mint = felix::Modint<B>;
    int n;
    std::string str;
    std::vector<Mint> value, pows;

    Hashed_String() {}

    Hashed_String(std::string _s): n(int(_s.size())), str(_s), value(std::vector<Mint>(n)), pows(std::vector<Mint>(n)) {
        value[0] = str[0];
        pows[0] = 1;
        for(int i = 1; i < n; ++i) {
            value[i] = value[i - 1] * A + str[i];
            pows[i] = pows[i - 1] * A;
        }
    }
    
    inline Mint get(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        if(!l)
            return value[r];
        return value[r] - value[l - 1] * pows[r - l + 1];
    }
    
    inline Mint id() {
        return value.back();
    }
};

} // namespace felix

#endif // FELIX_HASH_HPP
