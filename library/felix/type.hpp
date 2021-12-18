#ifndef FELIX_TYPE_HPP
#define FELIX_TYPE_HPP 1

#include <set>
#include <map>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>

namespace felix {

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
template<class T> using pair2 = std::pair<T, T>;
using pii = pair2<int>;
using pll = pair2<ll>;
using pdd = pair2<ld>;
using tiii = std::tuple<int, int, int>;
template<class T, size_t S> using ar = std::array<T, S>;
template<class T> using mset = std::multiset<T>;
template<class T> using vt = std::vector<T>;
template<class T> using oset = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
template<class T> using omset = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less_equal<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

struct custom_hash {
	static ull splitmix64(ull x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
 
	ull operator()(ull x) const {
		static const ull FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}

	template <class T, class U>
	ull operator()(const std::pair<T, U>& p) const {
		static const ull FIXED_RANDOM1 = std::chrono::steady_clock::now().time_since_epoch().count();
		static const ull FIXED_RANDOM2 = std::chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(p.first + FIXED_RANDOM1) ^ splitmix64(p.second + FIXED_RANDOM2);
	}

	template <class A, class B, class C>
	ull operator()(const std::tuple<A, B, C>& tp) const {
		static const ull FIXED_RANDOM1 = std::chrono::steady_clock::now().time_since_epoch().count();
		static const ull FIXED_RANDOM2 = std::chrono::steady_clock::now().time_since_epoch().count();
		static const ull FIXED_RANDOM3 = std::chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(std::get<0>(tp) + FIXED_RANDOM1) ^ splitmix64(std::get<1>(tp) + FIXED_RANDOM2) ^ splitmix64(std::get<2>(tp) + FIXED_RANDOM3);
	}

	template <class A, class B, class C, class D>
	ull operator()(const std::tuple<A, B, C, D>& tp) const {
		static const ull FIXED_RANDOM1 = std::chrono::steady_clock::now().time_since_epoch().count();
		static const ull FIXED_RANDOM2 = std::chrono::steady_clock::now().time_since_epoch().count();
		static const ull FIXED_RANDOM3 = std::chrono::steady_clock::now().time_since_epoch().count();
		static const ull FIXED_RANDOM4 = std::chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(std::get<0>(tp) + FIXED_RANDOM1) ^ splitmix64(std::get<1>(tp) + FIXED_RANDOM2) ^ splitmix64(std::get<2>(tp) + FIXED_RANDOM3) ^ splitmix64(std::get<3>(tp) + FIXED_RANDOM4);
	}
};

template<class T> using uset = std::unordered_set<T, custom_hash>;
template<class T, class U> using umap = std::unordered_map<T, U, custom_hash>;

} // namespace felix

#endif // FELIX_TYPE_HPP
