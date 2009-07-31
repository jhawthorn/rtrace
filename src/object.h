#ifndef OBJECT_H
#define OBJECT_H OBJECT_H

#include <limits>

#include "colour.h"
#include "matrix.h"

class Ray;

class Object{
	public:
		Colour colour;
		virtual Vector4 normal(const Vector4 &v) const = 0;
		virtual double intersect(const Ray *r) const = 0;/*{
			return std::numeric_limits<double>::infinity();
		}*/
};

#endif

