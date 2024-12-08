#include <iostream>
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "rtweekend.h"

#include <vector>
#include <memory>

using std::make_shared;
using std::shared_ptr;


color ray_color(const ray& r, const std::vector<shared_ptr<sphere>> world){

    hit_record rec;
    bool hit_anything = false;
    double closest_hit_so_far = infinity;
    
    // For each ray, we will loop through all the objects and see the closest object.
    // We only color the ray to the closest pixel.
    for (const auto& object: world){
        hit_record temp_rec;
        if(object->hit(r, 0, closest_hit_so_far, temp_rec)){
            hit_anything = true;
            closest_hit_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    if (hit_anything) {
        vec3 N = unit_vector(r.at(rec.t) - vec3(0,0,-1));
        return 0.5*(rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

    // Image

    auto aspect_ration = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's atleast 1
    // width/height = 16/9
    int image_height = int(image_width / aspect_ration);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0,0,0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta from pixel to pixel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Create a world of spheres
    std::vector<shared_ptr<sphere>> world;
    world.push_back(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.push_back(make_shared<sphere>(point3(0,-100.5,-1), 100));


    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            // ASK: Why do we need ray_direction
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
            
        }
    }
    std::clog << "\rDone.           \n";
}