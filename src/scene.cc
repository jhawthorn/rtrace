
#include <iostream>
#include <fstream>
using namespace std;

#include <limits>

#include "scene.h"
#include "light.h"

Scene::Scene(int width, int height): width(width), height(height), bgcolour(0,0,0){
}

Colour Scene::rayeval(const Ray &ray, int count = 5){
	double dist;
	Object *o;
	ray.cast(objects, &dist, &o);
	if(dist == std::numeric_limits<double>::infinity()){
		return bgcolour;
	}else{
		Vector4 point = ray.o + (ray.d * dist);
		point(3,0) = 1;
		Vector4 N = o->normal(point);

		Vector4 R = N * 2 + ray.d;
		normalize(R);

		double light = 0.0;
		for(unsigned int i = 0; i < lights.size(); i++){
			light += lights[i]->lightat(objects, point, N, R);
		}
		if(count){
			Ray rray(point, R);
			Colour reflection = rayeval(rray, count - 1);
			return reflection * 0.3 + o->colour * light;
		}else{
			return o->colour * light;
		}
	}
}

#define SUPERSAMPLE 2.0

#define FACT 0.001

void Scene::render(){
	ofstream img;
	img.open("output.ppm");
	img << "P6" << endl;
	img << width << " " << height << endl;
	img << 255 << endl;
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
      Colour colour;
      for(int yi = 0; yi < SUPERSAMPLE; yi++){
        for(int xi = 0; xi < SUPERSAMPLE; xi++){
          Ray ray(v4(0,0,0), v4((x - width / 2.0 + xi / SUPERSAMPLE) * FACT, (y - height / 2.0 + yi / SUPERSAMPLE) * FACT, -1));
          colour += rayeval(ray);
        }
      }
      colour /= SUPERSAMPLE * SUPERSAMPLE;
      colour.write(img);
		}
	}
}

