#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        point3 center;
        double radius;
        color albedo; // fraction of sunlight that is reflected
        bool metal;

    public:
        sphere(const point3& center, double radius, color albedo, bool metal) : center(center), radius(std::fmax(0, radius)), albedo(albedo), metal(metal) {}

        bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius*radius;

            auto discriminant = h*h - a*c;
            if (discriminant < 0)
                return false;
        
            auto sqrtd = std::sqrt(discriminant);

            
            // root: Solving this equation, gives the points where the ray hit the sphere
            auto root = (h - sqrtd) / a;
            if (root < ray_tmin || ray_tmax < root){
                return false;
            }

            // ASK: Not sure why book recommends this
            // if (root <= ray_tmin || ray_tmax <= root) {
            //     root = (h + sqrtd) / a;
            //     if (root <= ray_tmin || ray_tmax <= root)
            //         return false;
            // }

            rec.t = root;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            
            rec.attenuation = albedo;
            vec3 direction;

            if (metal)
            direction = reflect(r.direction(), rec.normal);
            else
                direction = rec.normal + random_unit_vector();
             
            rec.scattered = ray(rec.p, direction);

            return true;

        }
};

#endif