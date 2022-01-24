#ifndef FELIX_LCA_HPP
#define FELIX_LCA_HPP 1

#include <cassert>
#include <vector>
#include <functional>
#include "felix/internal_bit.hpp"
#include "felix/forest.hpp"

namespace felix {

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

private:
	int log;
	std::vector<std::vector<int>> dp;

public:
	LCA() : LCA(0) {}

	LCA(int _n) : forest<T>(_n), log(internal::ceil_pow2(_n)) {
		dp = std::vector<std::vector<int>>(_n, std::vector<int>(log + 1));
	}

	void build_lca(int root) {
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

	inline int lca(int a, int b) const {
		assert(0 <= a && a < n);
		assert(0 <= b && b < n);
		if(depth[a] > depth[b])
			std::swap(a, b);
		b = lift(b, depth[b] - depth[a]);
		if(a == b)
			return a;
		for(int i = log; ~i; --i) {
			int A = dp[a][i], B = dp[b][i];
			if(A != B) {
				a = A;
				b = B;
			}
		}
		return dp[a][0];
	}
};

} // namespace felix

#endif // FELIX_LCA_HPP
