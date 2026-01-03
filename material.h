#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material
{
public:
    virtual ~material() = default;

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
    {
        return false;
    };
}

/*
 * Lambertian (diffuse) reflectance can either
 * always scatter and attenuate light according to its reflectance 𝑅,
 * or it can sometimes scatter (with probability 1−𝑅) with no attenuation
 * (where a ray that isn't scattered is just absorbed into the material).
 * It could also be a mixture of both those strategies.
 *
 * Here we are choosing to just always scatter to keep it simple
 * We could also scatter with probability p and attenuation = albedo / p
 */

class lambertian : public material
{
public:
    lambertian(const color &albedo) : albedo(albedo) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        auto scatter_direction = rec.normal + random_unit_vector();
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

#endif