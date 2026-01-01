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

#endif