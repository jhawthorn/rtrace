#ifndef RAY_H
#define RAY_H RAY_H

#include "matrix.h"

#include <iostream>
#include <vector>
using namespace std;

#include "object.h"

class Ray {
      public:
	Vector4 o;
	Vector4 d;
	Ray(Vector4 o, Vector4 d) : o(o), d(d) {
		normalize(this->d);
	}
	void cast(const vector<Object *> &objects, double *dist, Object **o) const {
		*dist = std::numeric_limits<double>::infinity();
		*o = NULL;
		for (unsigned int i = 0; i < objects.size(); i++) {
			double d = objects[i]->intersect(this);
			if (d < *dist && d > 0.01) {
				*o = objects[i];
				*dist = d;
			}
		}
	}
};

#endif
