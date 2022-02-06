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

template<class T>
class LCA : public forest<T> {
public:
	using forest<T>::n;
	using forest<T>::edges;
	using forest<T>::adj;
	using forest<T>::build;
	using forest<T>::parent;
	using forest<T>::depth;
	using forest<T>::subtree_size;
	using forest<T>::first_occurrence;
	using forest<T>::euler;

	static std::pair<int, int> __lca_op(std::pair<int, int> a, std::pair<int, int> b) {
		return min(a, b);
	}

private:
	int log;
	std::vector<std::vector<int>> bin_lift;
	sparse_table<std::pair<int, int>, __lca_op> table;

public:
	LCA() : LCA(0) {}

	LCA(int _n) : forest<T>(_n), log(internal::ceil_pow2(_n)) {
		bin_lift = std::vector<std::vector<int>>(_n, std::vector<int>(log + 1));
	}

	void build_lca(int root) {
		build(root);
		for(int i = 0; i < n; ++i)
			bin_lift[i][0] = parent[i];
		bin_lift[root][0] = root;
		for(int j = 1; j <= log; ++j) {
			for(int i = 0; i < n; ++i) {
				bin_lift[i][j] = bin_lift[bin_lift[i][j - 1]][j - 1];
			}
		}
		std::vector<std::pair<int, int>> v;
		v.reserve(int(euler.size()));
		for(int& u : euler) {
			v.push_back({depth[u], u});
		}
		table = sparse_table<std::pair<int, int>, __lca_op>(v);
	}

	inline int kth_ancestor(int u, int k) const {
		assert(0 <= u && u < n);
		for(int i = 0; k; ++i, k >>= 1) {
			if(k & 1) {
				u = bin_lift[u][i];
			}
		}
		return u;
	}

	inline int lca(int a, int b) const {
		assert(0 <= a && a < n);
		assert(0 <= b && b < n);
		int l = first_occurrence[a], r = first_occurrence[b];
		if(l > r) {
			std::swap(l, r);
		}
		return table.prod(l, r).second;
	}

	inline int distance(int a, int b) const {
		assert(0 <= a && a < n);
		assert(0 <= b && b < n);
		return depth[a] + depth[b] - 2 * depth[lca(a, b)];
	}
};

} // namespace felix

#endif // FELIX_LCA_HPP
