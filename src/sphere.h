#ifndef SPHERE_H
#define SPHERE_H SPHERE_H

#include "matrix.h"
#include "object.h"
#include "ray.h"

class Sphere : public Object {
      public:
	Vector4 o;
	double r;
	double r2;
	Sphere(Vector4 o, double r) : o(o), r(r) {
		r2 = r * r;
	}
	Vector4 normal(const Vector4 &v) const {
		Vector4 n;
		n = v - o;
		normalize(n);
		return n;
	}
	double intersect(const Ray *ray) const {
		Vector4 dst = ray->o - o;
		double B = dot(dst, ray->d);
		double C = dot(dst, dst) - r2;
		double D = (B * B) - C;
		return D > 0 ? -B - sqrt(D) : std::numeric_limits<double>::infinity();
	}
};

#endif
