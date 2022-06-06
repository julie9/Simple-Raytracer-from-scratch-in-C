#ifndef OBJECT_C
#define OBJECT_C

#include <stdio.h>
#include <math.h>
#include "raytracer.h"



// -------------------------------
// ------- OBJECT CREATION -------
// -------------------------------
Object* create_sphere()
{
    Object* object = malloc(sizeof(Object));
    object->transform_object_to_world = malloc(16 * sizeof(double));
    object->transform_world_to_object = malloc(16 * sizeof(double));

    // in local coordinate, the sphere always have
    // center at (0,0,0) and radius=1.
    object->type_of_object = SPHERE;
    create_point(&object->center, 0.0, 0.0, 0.0);
    object->radius = 1.0;

    object->is_casting_shadow = 1; // TRUE;

    create_material_default(&(object->material));
    identity4d(object->transform_object_to_world);
    identity4d(object->transform_world_to_object);

    return object;
}



Object* create_plane()
{
    // TODO: 1 big chunk of heap, instead of multiple malloc. Better?
    Object* object = malloc(sizeof(Object));
    object->transform_object_to_world = malloc(16 * sizeof(double));
    object->transform_world_to_object = malloc(16 * sizeof(double));

    // in local coordinate, the plane is always
    // in the xz-plane, passing through the origin.
    object->type_of_object = PLANE;
    object->is_casting_shadow = 1; // TRUE;

    create_material_default(&(object->material));
    identity4d(object->transform_object_to_world);
    identity4d(object->transform_world_to_object);

    return object;
}



void create_glass_sphere(Object *object)
{
    create_sphere(object);
    object->material.transparency = 1.0;
    object->material.refractive_index = 1.5;
    object->is_casting_shadow = 0; // FALSE;

}



void set_transform_object(Object *obj, double *t)
{
    for(int i= 0; i < 16; i++)
    {
        obj->transform_object_to_world[i] = t[i];
    }

    // inverse of the transform, i.e. from world back to object coord.
    invert_matrix_4x4(obj->transform_world_to_object,
                        obj->transform_object_to_world);

}



// ------------------------------
// ------- OBJECT NORMALS -------
// ------------------------------
void normal_at(Tuple *world_normal, Object *object, Tuple *world_point)
{
    // from world to local coordinate system:
    Tuple local_point;
    local_point = transform_tuple(object->transform_world_to_object, world_point);

    // Calling local_normal function for each type of object:
    Tuple local_normal;
    if(SPHERE == object->type_of_object)
    {
        local_normal_at_sphere(&local_normal, object, &local_point);
    }
    else if(PLANE == object->type_of_object)
    {
        create_vector(&local_normal, 0, 1, 0);
    }

    // from local to world coordinate system:
    double transposed_transform_world_to_object[16];
    transpose_matrix(transposed_transform_world_to_object, object->transform_world_to_object);
    *world_normal = transform_tuple(transposed_transform_world_to_object,
                                    &local_normal);
    world_normal->w = 0.0;
    normalize_tuple(world_normal, world_normal);

    // display_matrix(transposed_transform_world_to_object);
    // display_tuple(&local_normal);
    // display_tuple(world_normal);
}

void local_normal_at_sphere(Tuple *local_normal, Object *object, Tuple *local_point)
{
    // object->center = (0,0,0) in local coordinate
    substracting_tuple(local_normal, local_point, &(object->center));
}



// -----------------------------------
// ------- OBJECT INTERSECTION -------
// -----------------------------------
void create_intersection(Intersection * i, double t, Object * o)
{
    i->t = t;
    i->object = o;
}



void hit(Intersection * hit, boolean * is_there_a_hit,
            Intersection * grouped_intersections, int * nb_intersections)
{
    //  bubble sorting by t value
    Intersection temp;
    for(int i = 0; i < (*nb_intersections - 1); i++)
    {
        for(int j = 0; j < (*nb_intersections - i - 1); j++)
        { // up to the second-to-last, and then up to the one before that...
            if(grouped_intersections[j].t > grouped_intersections[j+1].t)
            {
                temp = grouped_intersections[j];
                grouped_intersections[j] = grouped_intersections[j+1];
                grouped_intersections[j+1] = temp;
            }

        }
    }

    // return the first non-negative hit
    *is_there_a_hit = FALSE;
    for(int i = 0; i < *nb_intersections; i++)
    {
        *hit = grouped_intersections[i];
        if(hit->t > 0)
        { // ignore all intersection with negative t values
            *is_there_a_hit = TRUE;
            return;
        }
    }
    return;
}



void intersect(Intersection * all_intersections,
                      int * nb_intersections, Object *object, Ray *world_ray)
{
    Ray local_ray;
    transform_ray(&local_ray, object->transform_world_to_object, world_ray);

    if(SPHERE == object->type_of_object)
    {
        local_intersect_sphere(all_intersections, nb_intersections, object, &local_ray);
    }
    else if(PLANE == object->type_of_object)
    {
        // printf("intersect plane");
        local_intersect_plane(all_intersections, nb_intersections, object, &local_ray);
    }
}



void local_intersect_sphere(Intersection * all_intersections,
                      int * nb_intersections, Object *object, Ray *local_ray)
{
    double t0, t1;

    // Geometry method:
    Tuple vector_origin2center;
    // object->center = (0,0,0) in local coordinate
    substracting_tuple(&vector_origin2center, &(object->center), &(local_ray->origin));

    double mag_transformed_ray_dir = magnitude(&(local_ray->direction));

    Tuple direction_unit;
    normalize_tuple(&direction_unit, &(local_ray->direction));
    double t_middle = dot(&vector_origin2center, &direction_unit);

    double l_middle_square = (dot(&vector_origin2center, &vector_origin2center))
                            - (t_middle * t_middle);
    double sphere_radius_square = 1.0;

    if( l_middle_square > sphere_radius_square)
    {   // no hit
        t0 = 0.0;
        t1 = 0.0;
        *nb_intersections = 0;
    }
    else
    {
        double delta_t = sqrt(sphere_radius_square - l_middle_square);
        t0 = (t_middle - delta_t) / mag_transformed_ray_dir;
        t1 = (t_middle + delta_t / mag_transformed_ray_dir);

        static Intersection intersect0;
        static Intersection intersect1;
        create_intersection(&intersect0, t0, object);
        create_intersection(&intersect1, t1, object);
        all_intersections[0] = intersect0;
        all_intersections[1] = intersect1;
        *nb_intersections = 2;
    }
}


void local_intersect_plane(Intersection * all_intersections,
                      int * nb_intersections, Object *object, Ray *local_ray)
{
    if(fabs(local_ray->direction.y) < EPSILON)
    {
        // parallel or coplanar.
        // printf("coplanar");
        *nb_intersections = 0;
        return;
    }

    double t = (-1) * local_ray->origin.y / local_ray->direction.y;

    static Intersection intersect;
    create_intersection(&intersect, t, object);
    all_intersections[0] = intersect;
    *nb_intersections = 1;
}


#endif /* OBJECT_C */