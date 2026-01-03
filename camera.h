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
    color ray_color(const ray &r, const hittable &world) const {

    };
}

#endif