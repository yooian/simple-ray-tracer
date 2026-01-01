#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

// Struct to store information about hit
class hit_record
{
public:
    point3 p;
    vec3 normal;
    double t;
};

class hittable
{
public:
    virtual ~hittable() = default; // virtual destructor with default cleanup operation
    virtual bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const = 0;
    // const = 0 ensures hittable object cannot exist as itself, must be defined by children
};

#endif