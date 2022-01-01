#ifndef FELIX_MATH_HPP
#define FELIX_MATH_HPP 1

// #include <>

namespace felix {

inline int ceil_pow2(int n) {
	int x = 0;
	while((1U << x) < (unsigned int)(n))
		x++;
	return x;
}

} // namespace felix

#endif // FELIX_MATH_HPP
