#ifndef LIGHT_H
#define LIGHT_H LIGHT_H

#include "matrix.h"
#include "ray.h"

class Light {
      public:
	virtual double lightat(vector<Object *> &objects, Vector4 point, Vector4 normal,
			       Vector4 ref) = 0;
};

class DirectionLight : public Light {
      public:
	double i;
	Vector4 d;
	DirectionLight(double i, Vector4 d) : i(i), d(d) {
		normalize(this->d);
	}
	double lightat(vector<Object *> &objects, Vector4 point, Vector4 normal, Vector4 ref) {
		Object *o;
		double dist;
		double ret = 0, ret2 = 0;
		Ray ray(point, d * -1);
		ray.cast(objects, &dist, &o);
		if (dist == std::numeric_limits<double>::infinity()) {
			ret = (1 - dot(normal, d));
			if (ret < 0 || isnan(ret))
				ret = 0;
			if (ret > 1)
				ret = 1;
			ret *= i;
			// cout << ret << endl;
			/*ret2 = dot(ref, d) * i * -4;
			if(ret2 < 0 || isnan(ret2))
				ret2 = 0;*/
		}

		return ret + ret2;
	}
};

class AmbientLight : public Light {
      public:
	double i;
	AmbientLight(double i) : i(i) {
	}
	double lightat(vector<Object *> &objects, Vector4 point, Vector4 normal, Vector4 ref) {
		return i;
	}
};

#endif
