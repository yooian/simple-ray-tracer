#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"

class triangle : public hittable
{
public:
    triangle(const point3 &v1, const point3 &v2, const point3 &v3, std::shared_ptr<material> mat) : v1(v1), v2(v2), v3(v3), mat(mat) {}

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        return true;
    }

private:
    point3 v1, v2, v3;
    std::shared_ptr<material> mat;
};

#endif