#ifndef FELIX_STRING_HPP
#define FELIX_STRING_HPP 1

#include <vector>
#include <algorithm>
#include <numeric>

namespace felix {

// remember adding a unique character with small ascii after the string

template<class T>
std::vector<int> build_sa(const T& s) { // return the suffix array
    const int n = s.size();
    std::vector<int> sa(n), val(n);
    iota(sa.begin(), sa.end(), 0);
    for(int i = 0; i < n; ++i)
        val[i] = s[i];
    int gap = 1;
    auto cmp = [&](int i, int j) {
        if(val[i] != val[j])
            return val[i] < val[j];
        i += gap;
        j += gap;
        if(i < n && j < n)
            return val[i] < val[j];
        return i > j;
    };
    while(true) {
        std::sort(sa.begin(), sa.end(), cmp);
        std::vector<int> temp(n);
        for(int i = 1; i < n; ++i)
            temp[i] = temp[i - 1] + cmp(sa[i - 1], sa[i]);
        for(int i = 0; i < n; ++i)
            val[sa[i]] = temp[i];
        if(temp[n - 1] == n - 1)
            break;
        gap <<= 1;
    }
    return sa;
}

template<class T>
std::vector<int> build_lcp(const T& s, const std::vector<int>& sa) { // return the lcp array
    const int n = s.size();
    std::vector<int> lcp(n), rev(n);
    for(int i = 0; i < n; ++i)
        rev[sa[i]] = i;
    for(int i = 0, k = 0; i < n; ++i, k ? --k : 0) {
        if(!rev[i]) {
            k = 0;
            continue;
        }
        int j = sa[rev[i] - 1];
        while(i + k < n && j + k < n && s[i + k] == s[j + k])
            ++k;
        lcp[rev[i]] = k;
    }
    return lcp;
}

template<class T>
std::vector<int> build_z(const T& s) { // return the z array
    const int n = s.size();
    std::vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; ++i) {
        if(i > r) {
            l = r = i;
            while(r < n && s[r - l] == s[r])
                ++r;
            --r;
            z[i] = r - l + 1;
        } else {
            int k = i - l;
            if(z[k] < r - i)
                z[i] = z[k];
            else {
                l = i;
                while(r < n && s[r - l] == s[r])
                    ++r;
                --r;
                z[i] = r - l + 1;
            }
        }
    }
    return z;
}

} // namespace felix

#endif // FELIX_STRING_HPP
