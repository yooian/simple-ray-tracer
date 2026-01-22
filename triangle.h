#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"

class triangle : public hittable
{
public:
    triangle(const point3 &v1, const point3 &v2, const point3 &v3, std::shared_ptr<material> mat) : v1(v1), v2(v2), v3(v3), mat(mat)
    {
        // Equation of plane is Ax + By + Cz + D = 0
        // Where A, B, C are the components of the normal N
        // and x, y, z are the coords of any point on the plane
        // D is offset.

        // Need normal of plane the triangle sits on
        vec3 v1v2 = v1 - v2; // might need to flip for culling?
        vec3 v1v3 = v1 - v3;
        N = unit_vector(cross(v1v2, v1v3)); // N = plane normal
        D = -dot(N, v1)
    }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        // Calculate P

        // Check interval of t
        vec3 t = -(dot(N, r.orig) + D) / dot(N, r.dir);
        if (!ray_t.surrounds(t))
        {
            return false;
        }

        // Inside-outside test
        vec3 v1v2 = v2 - v1;
        vec3 v2v3 = v3 - v2;
        vec3 v3v1 = v1 - v3;

        // Test edge v1 -> v2
        vec3 v1p = rec.p - v1;
        if (dot(N, cross(v1v2, v1p)) < 0)
            return false; // point not in tri

        // Test edge v2 -> v3
        vec3 v2p = rec.p - v2;
        if (dot(N, cross(v2v3, v2p)) < 0)
            return false;

        // Test edge v3 -> v1
        vec3 v3p = rec.p - v3;
        if (dot(N, cross(v3v1, v3p)) < 0)
            return false;

        // Write to hit record after all checks pass
        rec.t = t;
        rec.p = r.at(rec.t);
        rec.set_face_normal(r, N);
        rec.mat = mat;

        return true;
    }

private:
    point3 v1, v2, v3; // Gotta assume counter clockwise winding
    vec3 N;
    vec3 D;
    std::shared_ptr<material> mat;
};

#endif