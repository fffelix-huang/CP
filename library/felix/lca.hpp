#ifndef FELIX_LCA_HPP
#define FELIX_LCA_HPP 1

#include <cassert>
#include <vector>
#include <functional>
#include <algorithm>
#include "felix/internal_bit.hpp"
#include "felix/forest.hpp"
#include "felix/sparsetable.hpp"

namespace felix {

namespace internal {

inline std::pair<int, int> __lca_op(std::pair<int, int> a, std::pair<int, int> b) {
	return min(a, b);
}

} // namespace internal

template<class T>
class LCA : public forest<T> {
public:
	using forest<T>::n;
	using forest<T>::edges;
	using forest<T>::g;
	using forest<T>::build;
	using forest<T>::parent;
	using forest<T>::depth;
	using forest<T>::sz;
	using forest<T>::pos;
	using forest<T>::order;

private:
	int log;
	std::vector<std::vector<int>> dp;
	sparse_table<std::pair<int, int>, internal::__lca_op> table;

public:
	LCA() : LCA(0) {}

	LCA(int _n) : forest<T>(_n), log(internal::ceil_pow2(_n)) {
		dp = std::vector<std::vector<int>>(_n, std::vector<int>(log + 1));
	}

	void build_lift(int root) {
		build(root);
		for(int i = 0; i < n; ++i)
			dp[i][0] = parent[i];
		dp[root][0] = root;
		for(int j = 1; j <= log; ++j)
			for(int i = 0; i < n; ++i)
				dp[i][j] = dp[dp[i][j - 1]][j - 1];
	}

	inline int lift(int u, int step) const {
		assert(0 <= u && u < n);
		for(int i = 0; step; ++i, step >>= 1)
			if(step & 1)
				u = dp[u][i];
		return u;
	}

	void build_lca(int root) {
		build(root);
		std::vector<std::pair<int, int>> v;
		v.reserve(int(order.size()));
		for(int& u : order)
			v.push_back({depth[u], u});
		table = sparse_table<std::pair<int, int>, internal::__lca_op>(v);
	}

	inline int lca(int a, int b) const {
		assert(0 <= a && a < n);
		assert(0 <= b && b < n);
		int l = pos[a], r = pos[b];
		if(l > r)
			std::swap(l, r);
		return table.prod(l, r).second;
	}
};

} // namespace felix

#endif // FELIX_LCA_HPP
