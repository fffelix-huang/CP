#ifndef FELIX_GEOMETRY_HPP
#define FELIX_GEOMETRY_HPP 1

#include <cassert>
#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>

namespace felix {

template<class T>
class point {
public:
	T x, y;

	point() : x(0), y(0) {}

	point(const T& a, const T& b) : x(a), y(b) {}

	template<class U>
	explicit point(const point<U>& p) : x(static_cast<T>(p.x)), y(static_cast<T>(p.y)) {}

	point(const std::pair<T, T>& p) : x(p.first), y(p.second) {}

	point(const std::complex<T>& p) : x(real(p)), y(imag(p)) {}

	explicit operator std::pair<T, T>() const {
		return std::pair<T, T>(x, y);
	}

	explicit operator std::complex<T>() const {
		return std::complex<T>(x, y);
	}

	point& operator+=(const point& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	point& operator-=(const point& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	point& operator*=(const T& rhs) {
		x *= rhs;
		y *= rhs;
		return *this;
	}

	point& operator/=(const T& rhs) {
		x /= rhs;
		y /= rhs;
		return *this;
	}

	template<class U>
	point& operator+=(const point<U>& rhs) {
		return *this += point<T>(rhs);
	}

	template<class U>
	point& operator-=(const point<U>& rhs) {
		return *this -= point<T>(rhs);
	}

	point operator+() const {
		return *this;
	}

	point operator-() const {
		return point(-x, -y);
	}

	point operator+(const point& rhs) {
		return point(*this) += rhs;
	}

	point operator-(const point& rhs) {
		return point(*this) -= rhs;
	}

	point operator*(const T& rhs) {
		return point(*this) *= rhs;
	}

	point operator/(const T& rhs) {
		return point(*this) /= rhs;
	}

	inline bool operator==(const point& rhs) {
		return x == rhs.x && y == rhs.y;
	}

	inline bool operator!=(const point& rhs) {
		return !(*this == rhs);
	}

	T dist2() const {
		return x * x + y * y;
	}

	long double dist() const {
		return std::sqrt(dist2());
	}

	point unit() const {
		return *this / this->dist();
	}

	long double angle() const {
		return std::atan2(y, x);
	}

	friend T dot(const point& lhs, const point& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	friend T cross(const point& lhs, const point& rhs) {
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}

	friend point dot_cross(const point& lhs, const point& rhs) {
		return point(dot(lhs, rhs), cross(lhs, rhs));
	}
};

template<class T>
class polygon {
	using P = point<T>;

public:
	polygon() {}

	polygon(const std::vector<P>& p) : n(int(p.size())), points(p) {}

	// Sort points counter-clockwise with G centered
	void sort_points() {
		P g;
		for(const P& p : points)
			g += p;
		g /= n;
		std::sort(points.begin(), points.end(), [&](P a, P b) {
			return (a - g).angle() < (b - g).angle();
		});
	}

	T area2() {
		T sum = 0;
		for(int i = 0; i < n; ++i) {
			int j = i + 1;
			if(j == n)
				j = 0;
			sum += points[i].x * points[j].y - points[i].y * points[j].x;
		}
		return std::abs(sum);
	}

private:
	int n;
	std::vector<P> points;
};

} // namespace felix

#endif // FELIX_GEOMETRY_HPP
