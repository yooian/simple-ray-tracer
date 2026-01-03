#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera
{
public:
    /* Public Camera Parameters Here */
    // we're keeping it simple and having public parameters so the code that
    // uses camera can directly set the parameters. no complicated constructor

    void render(const hittable &world)
    {
    }

private:
    /* Private Camera Variables Here */

    void initialize()
    {
    }

    // we're moving ray_color() here
    color ray_color(const ray &r, const hittable &world) const
    {
        hit_record rec;
        if (world.hit(r, interval(0, infinity), rec))
        {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);                          // want to scale unit_d [-1,1] to [0,1] range
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0); // linear interpolation white, blue
    }
};
}

#endif