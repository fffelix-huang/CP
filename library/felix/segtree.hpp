#ifndef FELIX_SEGTREE_HPP
#define FELIX_SEGTREE_HPP 1

#include <vector>
#include <cassert>
#include <felix/math>

namespace felix {

// Source: ac-library/atcoder/segtree.hpp
template<class T, T (*unit)(), T (*op)(T, T)>
class segtree {
public:
	segtree() : segtree(0) {}

	segtree(int _n) : segtree(std::vector<T>(_n, unit())) {}
	
	segtree(const std::vector<T>& arr): n(int(arr.size())) {
		log = ceil_pow2(n);
		size = 1 << log;
		st.resize(size << 1, unit());
		for(int i = 0; i < n; ++i)
			st[size + i] = arr[i];
		for(int i = size - 1; i; --i)
			update(i);
	}
	
	void set(int p, T val) {
		assert(0 <= p && p < n);
		p += size;
		st[p] = val;
		for(int i = 1; i <= log; ++i)
			update(p >> i);
	}

	inline T get(int p) const {
		assert(0 <= p && p < n);
		return st[p + size];
	}
	
	T prod(int l, int r) const {
		++r;
		assert(0 <= l && l <= r && r <= n);
		T ans_left = unit(), ans_right = unit();
		l += size;
		r += size;
		while(l < r) {
			if(l & 1)
				ans_left = op(ans_left, st[l++]);
			if(r & 1)
				ans_right = op(st[--r], ans_right);
			l >>= 1;
			r >>= 1;
		}
		return op(ans_left, ans_right);
	}

	inline T all_prod() const { return st[1]; }
	
private:
	int n, size, log;
	std::vector<T> st;

	inline void update(int v) { st[v] = op(st[v << 1], st[v << 1 | 1]); }
};

} // namespace felix

#endif // FELIX_SEGTREE_HPP