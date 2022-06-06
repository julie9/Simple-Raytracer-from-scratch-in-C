#ifndef RAY_C
#define RAY_C

#include "raytracer.h"

void create_ray(Ray *r, Tuple *origin, Tuple *direction)
{
    // TODO(julie): in Lindley, this function gets direclty the pixel
    // coordinate and compute the vector through it.
    r->origin = *origin;
    normalize_tuple(&(r->direction), direction);
}

void compute_position_on_ray(Tuple *position, Ray *r, double t)
{
    Tuple v;
    multiply_tuple_by_value(&v, &(r->direction), t);
    adding_tuple(position, &(r->origin), &v);
}

void get_point_on_ray(Tuple *position, Ray *r, double t)
{
    Tuple temp;
    multiply_tuple_by_value(&temp, &(r->direction), t);
    adding_tuple(position, &(r->origin), &temp);
}

void transform_ray(Ray *transformed_ray, double *transformation_matrix, Ray *original_ray)
{
    transformed_ray->origin = transform_tuple(transformation_matrix, &(original_ray->origin));
    transformed_ray->direction = transform_tuple(transformation_matrix, &(original_ray->direction));
}

#endif /* RAY_C */