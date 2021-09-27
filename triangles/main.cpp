#include <iostream>

#include "Vector3.hpp"
#include "Triangle.hpp"
#include "Line.hpp"
#include "Plane.hpp"


int main () 
{
    Line *line = new Line (* new Vector3{0.f,0.f,0.f}, * new Vector3{1.f,1.f,1.f});
    std::cout << line->getLineLineIntersection (* new Vector3{1.f,1.f,0.f}, * new Vector3{1.f,1.f,1.f}) << std::endl;
}
