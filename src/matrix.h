#ifndef MATRIX_H
#define MATRIX_H MATRIX_H

#include <math.h>

#include <assert.h>

#include <algorithm>
#include <functional>
#include <iostream>

template <unsigned int M, unsigned int N, typename T = double> class matrix {
      protected:
	T m[M][N];

      public:
	typedef T type;
	enum { rows = M, columns = N };
	T *data() {
		return &**m;
	}
	T const *data() const {
		return &**m;
	}

	matrix() {
		matrix(0);
		for (unsigned int i = 0; i < M && i < N; i++)
			m[i][i] = 1;
	}

	matrix(T const &c) {
		std::fill(data(), data() + M * N, c);
	}

	matrix(matrix const &m) {
		std::copy(m.data(), m.data() + M * N, data());
	}

	template <typename U> matrix(matrix<M, N, U> const &m) {
		std::copy(m.data(), m.data() + M * N, data());
	}

	template <typename U> matrix &operator=(matrix<M, N, U> const &m) {
		std::copy(m.data(), m.data() + M * N, data());
		return *this;
	}

	template <class UnaryFunction> matrix &map(UnaryFunction);

	template <class BinaryFunction> matrix &join(matrix const &, BinaryFunction);

	matrix &operator+=(matrix const &m) {
		return join(m, std::plus<T>());
	}

	matrix &operator-=(matrix const &m) {
		return join(m, std::minus<T>());
	}

	matrix &operator*=(T const &c) {
		return map(std::bind2nd(std::multiplies<T>(), c));
	}

	matrix &operator/=(T const &c) {
		return map(std::bind2nd(std::divides<T>(), c));
	}

	matrix &operator%=(T const &c) {
		return map(std::bind2nd(std::modulus<T>(), c));
	}

	matrix operator+(T const &c) const {
		matrix ret = *this;
		return ret += c;
	}

	matrix operator-(T const &c) const {
		matrix ret = *this;
		ret -= c;
		return ret;
	}

	matrix operator*(T const &c) const {
		matrix ret = *this;
		return ret *= c;
	}

	matrix operator/(T const &c) const {
		matrix ret = *this;
		return ret /= c;
	}

	matrix operator%(T const &c) const {
		matrix ret = *this;
		return ret %= c;
	}

	T &operator()(unsigned int i, unsigned int j) {
		return m[i][j];
	}

	T const &operator()(unsigned int i, unsigned int j) const {
		return m[i][j];
	}

	T &operator()(unsigned int i);
	T const &operator()(unsigned int i) const;
};

template <unsigned int M, unsigned int N, typename T>
std::ostream &operator<<(std::ostream &os, const matrix<M, N, T> &mat) {
	for (unsigned int i = 0; i < M; i++) {
		std::cout << (i == 0 ? "[" : " ");
		for (unsigned int j = 0; j < N; j++) {
			std::cout.width(7);
			std::cout << mat(i, j);
			if (j != N - 1)
				std::cout << ", ";
		}
		if (i == M - 1)
			std::cout << "	 ]";
		std::cout << std::endl;
	}
	return os;
}

/* dot product*/
template <unsigned int M, unsigned int N, unsigned int P, typename T>
inline matrix<M, P, T> operator*(matrix<M, N, T> a, matrix<N, P, T> b) {
	matrix<M, N, T> ret(0);
	for (unsigned int m = 0; m < M; m++) {
		for (unsigned int p = 0; p < P; p++) {
			T tmp = 0;
			for (unsigned int n = 0; n < N; n++) {
				tmp += a(m, n) * b(n, p);
			}
			ret(m, p) = tmp;
		}
	}
	return ret;
}

template <unsigned int M, unsigned int N, typename T>
template <class UnaryFunction>
matrix<M, N, T> &matrix<M, N, T>::map(UnaryFunction op) {
	std::transform(data(), data() + M * N, data(), op);
	return *this;
}

template <unsigned int M, unsigned int N, typename T>
template <class BinaryFunction>
matrix<M, N, T> &matrix<M, N, T>::join(matrix const &m, BinaryFunction op) {
	std::transform(data(), data() + M * N, m.data(), data(), op);
	return *this;
}

template <unsigned int M, unsigned int N, typename T>
inline matrix<M, N, T> operator+(matrix<M, N, T> const &m1, matrix<M, N, T> const &m2) {
	matrix<M, N, T> r = m1;
	r += m2;
	return r;
}

template <unsigned int M, unsigned int N, typename T>
inline matrix<M, N, T> operator-(matrix<M, N, T> const &m1, matrix<M, N, T> const &m2) {
	matrix<M, N, T> r = m1;
	r -= m2;
	return r;
}

template <unsigned int M, unsigned int N, typename T>
inline bool operator==(matrix<M, N, T> const &m1, matrix<M, N, T> const &m2) {
	return std::equal(m1.data(), m1.data() + M * N, m2.data());
}

template <unsigned int M, unsigned int N, typename T>
inline bool operator!=(matrix<M, N, T> const &m1, matrix<M, N, T> const &m2) {
	return !std::equal(m1.data(), m1.data() + M * N, m2.data());
}

template <unsigned int M, unsigned int N, typename T = double>
class IdentityMatrix : public matrix<M, N, T> {
      public:
	IdentityMatrix() : matrix<M, N, T>::matrix(0) {
		for (int i = 0; i < M && i < N; i++)
			matrix<M, N, T>::m[i][i] = 1;
	}
};

/* Vector operations */
template <unsigned int M, unsigned int N, typename T>
inline T &matrix<M, N, T>::operator()(unsigned int i) {
	if (N == 1) {
		return m[i][1];
	} else if (M == 1) {
		return m[1][i];
	} else {
		assert(0);
	}
}

#define X 0
#define Y 1
#define Z 2

inline matrix<4, 1> cross(const matrix<4, 1> &b, const matrix<4, 1> &c) {
	matrix<4, 1> a(0);
	a(X, 0) = b(Y, 0) * c(Z, 0) - b(Z, 0) * c(Y, 0);
	a(Y, 0) = b(Z, 0) * c(X, 0) - b(X, 0) * c(Z, 0);
	a(Z, 0) = b(X, 0) * c(Y, 0) - b(Y, 0) * c(X, 0);
	a(3, 0) = 1;
	return a;
}

inline double dot(const matrix<4, 1> &a, const matrix<4, 1> &b) {
	return a(0, 0) * b(0, 0) + a(1, 0) * b(1, 0) + a(2, 0) * b(2, 0) + a(3, 0) * b(3, 0);
}

inline double magnitude(const matrix<4, 1> &v) {
	double ret = 0;
	for (unsigned int i = 0; i < 3; i++) {
		ret += v(i, 0) * v(i, 0);
	}
	return sqrt(ret);
}

inline void normalize(matrix<4, 1> &v) {
	if (magnitude(v) > 0.0001) {
		v /= magnitude(v);
	}
	v(3, 0) = 1;
}

typedef matrix<4, 1> Vector4;
typedef matrix<1, 4> RVector4;
typedef matrix<3, 1> Vector3;
typedef matrix<4, 4> Matrix4;

/* Untemplated methods (due to lazyness)*/

inline Vector4 midpoint(Vector4 a, Vector4 b, double r = 0.5) {
	b -= a;
	b *= r;
	b += a;
	return b;
}

inline Vector4 v4(double x, double y, double z, double w = 1.0) {
	Vector4 v;
	v(0, 0) = x;
	v(1, 0) = y;
	v(2, 0) = z;
	v(3, 0) = w;
	return v;
}

#endif
