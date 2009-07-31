#include <iostream>
using namespace std;

#include "scene.h"
#include "sphere.h"
#include "light.h"
#include "triangle.h"

int main(int argc, char *argv[]){
	Scene scene(800, 600);
	Sphere *s1 = new Sphere(v4(-2, 0 , -10), 1.5);
	s1->colour = Colour(0, 0, 255);
	Sphere *s3 = new Sphere(v4(2, 0, -10), 1.5);
	s3->colour = Colour(0, 255, 0);
	/*Sphere *s2 = new Sphere(v4(3, 0, -20.0), 1.5);
	s2->colour = Colour(255, 0, 0);*/
	scene.lights.push_back(new DirectionLight(0.5, v4(-1, 1, 0)));
	//scene.lights.push_back(new DirectionLight(0.3, v4(-1, 1, 0)));
	scene.lights.push_back(new AmbientLight(0.2));
	scene.objects.push_back(s1);
	//scene.objects.push_back(s2);
	scene.objects.push_back(s3);

	Triangle *t1 = new Triangle(v4(-10,2,-8), v4(0, -2, -20), v4(10, 2, -8));
	t1->colour = Colour(100, 100, 100);
	scene.objects.push_back(t1);

  
  /*Colour colour1(0xcc, 0xcc, 0xcc);
  Colour colour2(0x22, 0x22, 0x22);
  for(int y = -14; y > -16; y-=2){
  for(int x = 3; x < 5; x+=2){
    Triangle *t = new Triangle(v4(3, 3, -14), v4(3, 3, -16), v4(5, 3, -14));
    Triangle *t2 = new Triangle(v4(5, 3, -14), v4(3, 3, -16), v4(5, 3, -16));
    //if(((x + y)/2) % 2){
      t->colour = t2->colour = colour1;
    //}else{
    //  t->colour = t2->colour = colour2;
    //}
    scene.objects.push_back(t);
    scene.objects.push_back(t2);
  }
  }*/

	scene.render();
	return 0;
}
