#ifndef FELIX_FOREST_HPP
#define FELIX_FOREST_HPP 1

#include <cassert>
#include <vector>
#include <functional>
#include "felix/graph.hpp"

namespace felix {

template<class T>
class forest : public graph<T> {
public:
	using graph<T>::n;
	using graph<T>::edges;
	using graph<T>::adj;

	std::vector<int> depth, parent, subtree_size;
	std::vector<int> euler, first_occurrence;

	forest() : forest(0) {}

	forest(int _n) : graph<T>(_n), depth(std::vector<int>(_n)), parent(std::vector<int>(_n)), subtree_size(std::vector<int>(_n)), first_occurrence(std::vector<int>(_n)), euler({}) {}

	virtual void add_edge(int from, int to, T cost = 1) {
		assert(0 <= from && from < n);
		assert(0 <= to && to < n);
		int id = int(edges.size());
		assert(id < n - 1);
		adj[from].push_back(id);
		adj[to].push_back(id);
		edges.push_back({from, to, id});
	}

	void build(int root) {
		assert(0 <= root && root < n);
		euler.reserve(n * 2);
		std::function<void(int, int)> dfs = [&](int u, int p) {
			depth[u] = (u == root ? 0 : depth[p] + 1);
			parent[u] = p;
			subtree_size[u] = 1;
			first_occurrence[u] = int(euler.size());
			euler.push_back(u);
			for(const int& id : adj[u]) {
				auto& e = edges[id];
				int v = e.from ^ e.to ^ u;
				if(v == p) {
					continue;
				}
				dfs(v, u);
				euler.push_back(u);
				subtree_size[u] += subtree_size[v];
			}
		};
		dfs(root, -1);
	}

	int find_centroid() {
		build(0);
		std::function<int(int, int)> dfs = [&](int u, int p) -> int {
			for(const int& id : adj[u]) {
				auto& e = edges[id];
				int v = e.from ^ e.to ^ u;
				if(v == p) {
					continue;
				}
				if(subtree_size[v] > (n >> 1)) {
					return dfs(v, u);
				}
			}
			return u;
		};
		return dfs(0, -1);
	}
};

} // namespace felix

#endif // FELIX_FOREST_HPP
