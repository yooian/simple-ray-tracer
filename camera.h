#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera
{
public:
    /* Public Camera Parameters Here */
    // we're keeping it simple and having public parameters so the code that
    // uses camera can directly set the parameters. no complicated constructor

    double aspect_ratio = 1.0; // Ratio image width/height
    int image_width = 100;     // In pixels

    void render(const hittable &world)
    {
        initialize();

        // Render
        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j)
        {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                auto ray_direction = pixel_center - camera_center;
                ray r(camera_center, ray_direction);

                color pixel_color = ray_color(r, world);
                write_color(std::cout, pixel_color);
            }
        }

        std::clog << "\rDone.		\n";
    }

private:
    /* Private Camera Variables Here */
    int image_height;     // Rendered image height
    point3 camera_center; // Camera center
    point3 pixel00_loc;   // Location of pixel 0, 0
    vec3 pixel_delta_u;   // Offset to pixel to the right
    vec3 pixel_delta_v;   // Offset to pixel below

    void initialize()
    {
        // Calculate image height, at least 1
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        // Camera
        auto focal_length = 1.0;
        camera_center = point3(0, 0, 0);

        // Viewport calculation (VP is real-valued, so need actual aspec ratio calculated)
        auto viewport_height = 2.0; // arbitrary
        auto viewport_width = viewport_height * (double(image_width) / image_height);

        // Horizontal/Vertical viewport edge vectors
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Horizontal/Vertical delta vectors from pixel to pixel
        auto pixel_delta_u = viewport_u / image_width;
        auto pixel_delta_v = viewport_v / image_height;

        // Calculat location of upper-left pixel
        auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
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