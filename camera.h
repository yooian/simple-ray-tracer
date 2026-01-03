#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera
{
public:
    /* Public Camera Parameters Here */
    // we're keeping it simple and having public parameters so the code that
    // uses camera can directly set the parameters. no complicated constructor

    double aspect_ratio = 1.0;  // Ratio image width/height
    int image_width = 100;      // In pixels
    int samples_per_pixel = 10; // Count of random samples for each pixel
    int max_depth = 10;         // Max number of ray bounces into scene

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
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; ++sample)
                {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }

        std::clog << "\rDone.		\n";
    }

private:
    /* Private Camera Variables Here */
    int image_height;           // Rendered image height
    double pixel_samples_scale; // Color scale factor for a sum of pixel samples
    point3 camera_center;       // Camera center
    point3 pixel00_loc;         // Location of pixel 0, 0
    vec3 pixel_delta_u;         // Offset to pixel to the right
    vec3 pixel_delta_v;         // Offset to pixel below

    void initialize()
    {
        // Calculate image height, at least 1
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

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
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculat location of upper-left pixel
        auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j) const
    {
        // Construct a camera ray from origin to a randomly sampled point around pixel loc [i,j]
        auto offset = sample_square(); // returns a ray pointing to a unit square around origin

        // Translating the sample region to pixel loc using the offset x and y
        // We basically inserted the sampling offset to the normal pixel_center calculation:
        //      auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        //      auto ray_direction = pixel_center - camera_center;
        auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const
    {
        // Returns the vector to a random point in a [-0.5,-0.5]-[+0.5,+0.5] unit square
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    // we're moving ray_color() here
    color ray_color(const ray &r, int depth, const hittable &world) const
    {
        // Base case for ray bounce depth
        if (depth <= 0)
            return color(0, 0, 0);

        hit_record rec;
        if (world.hit(r, interval(0, infinity), rec))
        {
            vec3 direction = random_on_hemisphere(rec.normal);
            return 0.5 * ray_color(ray(rec.p, direction), depth - 1, world);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);                          // want to scale unit_d [-1,1] to [0,1] range
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0); // linear interpolation white, blue
    }
};

#endif