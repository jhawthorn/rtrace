#ifndef COLOUR_H
#define COLOUR_H COLOUR_H

#include <iostream>
#include <fstream>
using namespace std;

#include "matrix.h"

class Colour: public Vector4{
	public:
		Colour(double r, double g, double b){
			m[0][0] = r;
			m[1][0] = g;
			m[2][0] = b;
		}
		Colour(Vector4 v): Vector4(v){
		}
		Colour(): Vector4(0){
		}
		unsigned char clip(double v){
			return v > 255 ? 255 : int(v);
		}
		void write(ofstream &f){
			f.put(clip(m[0][0]));
			f.put(clip(m[1][0]));
			f.put(clip(m[2][0]));
		}
};

#endif

