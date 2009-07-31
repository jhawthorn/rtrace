#ifndef TRIANGLE_H
#define TRIANGLE_H TRIANGLE_H

#include "object.h"
#include "matrix.h"
#include "ray.h"

class Triangle: public Object{
	public:
		Vector4 v1, v2, v3;
		Triangle(Vector4 v1, Vector4 v2, Vector4 v3): v1(v1), v2(v2), v3(v3){
		}
		Vector4 normal(const Vector4 &v) const{
			Vector4 edge1 = v2 - v1, edge2 = v3 - v1;
			Vector4 N = cross(edge1, edge2);
			normalize(N);
			return N;
		}
		double intersect(const Ray *ray) const{
			Vector4 edge1 = v2 -v1, edge2 = v3 - v1;

			Vector4 pvec = cross(ray->d, edge2);
			double det = dot(edge1, pvec);
			if(det > -.000001 && det < .000001){
				return std::numeric_limits<double>::infinity();
			}

			double invdet = 1.0 / det;

			Vector4 tvec = ray->o - v1;

			double u = dot(tvec, pvec) * invdet;
			if(u < 0 || u > 1){
				return std::numeric_limits<double>::infinity();
			}

			Vector4 qvec = cross(tvec, edge1);
			double v = dot(ray->d, qvec) * invdet;
			if(v < 0 || (u + v) > 1){
				return std::numeric_limits<double>::infinity();
			}

			double distance = dot(edge2, qvec) * invdet;
			if(distance < 0){
				return std::numeric_limits<double>::infinity();
			}

			return distance;
		}
};

#endif


