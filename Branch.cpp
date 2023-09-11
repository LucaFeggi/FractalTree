#include "Branch.hpp"

#include <cmath>

Branch::Branch(int StartX, int StartY, float Length, float Angle){
	this->x = StartX + Length*sin(Angle);
	this->y = StartY - Length*cos(Angle);
}
