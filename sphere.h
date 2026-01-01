#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
    sphere(const point3 &center, double radius) : center(center), radius(std::fmax(0, radius)) {}
    bool hit() const override {}

private:
    point3 center;
    double radius;
};

#endif