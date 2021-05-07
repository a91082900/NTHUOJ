#include "function.h"
#include <cmath>
#include <iostream>

using namespace oj;

Triangle::Triangle(double edge1, double edge2, double edge3) {
    if(edge1 < 0 || edge2 < 0 || edge3 < 0) {
        setArea(0.0);
        setPerimeter(0.0);
    }
    else if(edge1 + edge2 <= edge3 || edge2 + edge3 <= edge1 || edge3 + edge1 <= edge2) {
        setArea(0.0);
        setPerimeter(0.0);
    }
    else {
        double s = (edge1 + edge2 + edge3) / 2.0;
        double area = sqrt(s * (s-edge1) * (s-edge2) * (s-edge3));
        setArea(area);
        setPerimeter(edge1 + edge2 + edge3);
    }
}

Rectangle::Rectangle(double width, double height) {
    if(width < 0 || height < 0) {
        setArea(0.0);
        setPerimeter(0.0);
    }
    else {
        setArea(width * height);
        setPerimeter((width + height) * 2);
    }
}

Circle::Circle(double radius, double pi) {
    if(radius < 0 || pi < 0) {
        setArea(0.0);
        setPerimeter(0.0);
    }
    else {
        setArea(pi * radius * radius);
        setPerimeter(pi * radius * 2);
    }
}
