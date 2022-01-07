#ifndef FELIX_LCA_HPP
#define FELIX_LCA_HPP 1

#include <cassert>
#include <vector>
#include <functional>
#include <felix/math>
#include <felix/tree>

namespace felix {

template<class T>
class LCA : public tree<T> {
public:
	using tree<T>::n;
	using tree<T>::edges;
	using tree<T>::g;
	using tree<T>::build_tree;
	using tree<T>::parent;
	using tree<T>::depth;

	int log;
	std::vector<std::vector<int>> dp;

	LCA() : LCA(0) {}

	LCA(int _n) : tree<T>(_n), log(ceil_pow2(_n)) {
		dp = std::vector<std::vector<int>>(_n, std::vector<int>(log + 1));
	}

	void build_lca(int root) {
		build_tree(root);
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
