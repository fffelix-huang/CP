#ifndef FELIX_SCC_HPP
#define FELIX_SCC_HPP 1

#include <cassert>
#include <vector>
#include <functional>

namespace felix {

// Find all sccs of a graph using Kosaraju's algorithm in O(V + E)
class scc_graph {
public:
	scc_graph() : scc_graph(0) {}

	scc_graph(int _n) : n(_n), adj(n), radj(n) {}

	scc_graph(const std::vector<std::pair<int, int>>& edges) {
		n = 0;
		for(const auto& p : edges)
			n = std::max({n, p.first, p.second});
		++n;
		adj = std::vector<std::vector<int>>(n);
		radj = std::vector<std::vector<int>>(n);
		for(const auto& p : edges)
			add_edge(p.first, p.second);
	}

	scc_graph(const std::vector<std::vector<int>>& edge) : n(int(edge.size())), adj(edge), radj(int(edge.size())) {
		for(int i = 0; i < n; ++i) {
			for(const int& v : edge[i]) {
				assert(v < n);
				radj[v].push_back(i);
			}
		}
	}

	inline void add_edge(int u, int v) {
		assert(0 <= u && u < n);
		assert(0 <= v && v < n);
		adj[u].push_back(v);
		radj[v].push_back(u);
	}

	std::vector<std::vector<int>> get_scc() const {
		std::vector<bool> vis(n);
		std::function<void(std::vector<int>&, int)> topo_dfs = [&](std::vector<int>& topo, int u) {
			vis[u] = true;
			for(const int& v : adj[u])
				if(!vis[v])
					topo_dfs(topo, v);
			topo.push_back(u);
		};
		std::vector<int> topo;
		topo.reserve(n);
		for(int i = 0; i < n; ++i)
			if(!vis[i])
				topo_dfs(topo, i);
		vis = std::vector<bool>(n);
		std::function<void(std::vector<int>&, int)> scc_dfs = [&](std::vector<int>& cur, int u) {
			vis[u] = true;
			cur.push_back(u);
			for(const int& v : radj[u])
				if(!vis[v])
					scc_dfs(cur, v);
		};
		std::vector<std::vector<int>> groups;
		for(int i = n - 1; ~i; --i) {
			if(!vis[topo[i]]) {
				std::vector<int> cur;
				scc_dfs(cur, topo[i]);
				groups.push_back(cur);
			}
		}
		return groups;
	}

private:
	int n;
	std::vector<std::vector<int>> adj, radj;
};

} // namespace felix

#endif // FELIX_SCC_HPP
