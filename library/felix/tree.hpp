#ifndef FELIX_TREE_HPP
#define FELIX_TREE_HPP 1

#include <cassert>
#include <vector>
#include <functional>
#include <felix/graph>

namespace felix {

template<class T>
class tree : public graph<T> {
public:
	using graph<T>::n;
	using graph<T>::edges;
	using graph<T>::g;

	std::vector<int> depth, parent, sz;

	tree() : tree(0) {}

	tree(int _n) : graph<T>(_n), depth(std::vector<int>(_n)), parent(std::vector<int>(_n)), sz(std::vector<int>(_n)) {}

	virtual void add_edge(int from, int to, T cost = 1) {
		assert(0 <= from && from < n);
		assert(0 <= to && to < n);
		int id = int(edges.size());
		g[from].push_back(id);
		g[to].push_back(id);
		edges.push_back({from, to, id});
	}

	void clear() {
		depth.clear();
		parent.clear();
		sz.clear();
	}

	void build_tree(int root) {
		assert(0 <= root && root < n);
		std::function<void(int, int)> dfs = [&](int u, int p) {
			depth[u] = (u == root ? 0 : depth[p] + 1);
			parent[u] = p;
			sz[u] = 1;
			for(const int& id : g[u]) {
				auto& e = edges[id];
				int v = e.from ^ e.to ^ u;
				if(v == p)
					continue;
				dfs(v, u);
				sz[u] += sz[v];
			}
		};
		dfs(root, -1);
	}
};

} // namespace felix

#endif // FELIX_TREE_HPP
