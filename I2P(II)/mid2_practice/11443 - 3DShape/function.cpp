#include "function.h"

using namespace oj;
	
Sphere::Sphere(double radius, double pi) {
	if(radius > 0 && pi > 0)
		setVolume(4.0/3.0 * radius * radius * radius * pi);
	else
		setVolume(0.0);
}

Cone::Cone(double radius, double height, double pi) {
	if(radius > 0 && height > 0 && pi > 0)
		setVolume(1.0/3.0 * radius * radius * height * pi);
	else
		setVolume(0.0);
}

Cuboid::Cuboid(double length, double width, double height) {
	if(length * width * height > 0)
		setVolume(length * width * height);
	else
		setVolume(0.0);
}

Cube::Cube(double length) : Cuboid::Cuboid(length, length, length) {
	/*if(length > 0)
		setVolume(length * length * length);
	else
		setVolume(0.0);*/
}