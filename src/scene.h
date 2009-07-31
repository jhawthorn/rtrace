#ifndef SCENE_H
#define SCENE_H SCENE_H

#include <vector>
using namespace std;

#include "object.h"
#include "colour.h"

class Light;

class Scene{
  public:
    vector<Object *> objects;
    vector<Light *> lights;
    int width, height;
	Colour bgcolour;
    Scene(int width, int height);
	Colour rayeval(const Ray &, int count);
	void render();
};

#endif

