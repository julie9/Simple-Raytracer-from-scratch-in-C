#ifndef WORLD_C
#define WORLD_C

#include "raytracer.h"



void create_world(World* w)
{
    w->number_of_objects = 0;
    w->number_of_lights = 0;

    // w->objects = malloc(sizeof(*Object) * MAX_N_OBJECT_WORLD);
    // w->lights = malloc(sizeof(*Light) * MAX_N_LIGHT_WORLD);
}



void add_object(World* w, Object* object)
{
    // QUESTION: do we need a pointer to the object here????
    // TODO: very prone to SEGFAULT :S
    if ((w->number_of_objects) < MAX_N_OBJECT_WORLD)
    {
        w->objects[w->number_of_objects] = object;
        (w->number_of_objects)++;
    }
    else
    {
        printf("Warning: adding no more object. Increase MAX_N_OBJECT_WORLD\n");

    }

}



void add_light(World* w, Light* light)
{
    w->lights[w->number_of_lights] = *light;
    (w->number_of_lights)++;
}



void create_default_world(World* world)
{
    world->number_of_objects = 0;
    world->number_of_lights = 0;

    Tuple light_position;
    Tuple light_color_intensity;

    Light myLight;
    create_point(&light_position, -10, 10, -10);
    create_color(&light_color_intensity,  1, 1, 1);
    create_light(&myLight, &light_position, &light_color_intensity);
    add_light(world, &myLight);
    // printf("nb of lights : %d\n", world->number_of_lights);

    Object sphere1;
    create_sphere(&sphere1);
    Tuple color;
    create_color(&color, 0.8, 1.0, 0.6);
    sphere1.material.color = color;
    sphere1.material.diffuse = 0.7;
    sphere1.material.specular = 0.2;
    add_object(world, &sphere1);

    Object sphere2;
    create_sphere(&sphere2);
    double A[16];
    scaling(A, 0.5, 0.5, 0.5);
    set_transform_object(&sphere2, A);
    add_object(world, &sphere2);
    // printf("nb of objects in your world : %d\n", world->number_of_objects);
}



void intersect_world_with_ray(Intersection * all_intersections, int * nb_intersections,
                              World * w, Ray * r)
{
    *nb_intersections = 0;

    Intersection intersection_per_object[MAX_N_INTERSECTION_RAY_OBJ];
    int nb_intersections_per_object;

    // for each object in the world
    // if sphere, call intersect_sphere() etc
    for(int i = 0; i < (w->number_of_objects); i++)
    {
        nb_intersections_per_object = 0;

        intersect(intersection_per_object, &nb_intersections_per_object,
                            (w->objects[i]), r);
        for(int j = 0; j < nb_intersections_per_object; j++)
        {
            all_intersections[*nb_intersections] = intersection_per_object[j];
            (*nb_intersections)++;
        }
    }
}



boolean is_shadowed(World *world, int no_light, Tuple *point)
{
    boolean is_in_shadow;

    Tuple toward_light_vector;
    double distance_with_light;
    Tuple light_vector_unit_vector;
    Ray toward_light_ray;

    // distance from point to light
    substracting_tuple(&toward_light_vector,
                        &(world->lights[no_light].position), point);
    distance_with_light = magnitude(&toward_light_vector);

    // ray from point toward the light
    normalize_tuple(&light_vector_unit_vector, &toward_light_vector);
    create_ray(&toward_light_ray, point, &light_vector_unit_vector);

    int nb_intersections_light = 0;
    Intersection all_intersections_light[NB_INTERSECTION_PER_RAY];
    intersect_world_with_ray(all_intersections_light, &nb_intersections_light,
                            world, &toward_light_ray);


    if(0 == nb_intersections_light)
    {
        is_in_shadow = FALSE;
        return is_in_shadow;
    }

    Intersection intersection_hit_light;
    boolean is_there_a_hit = FALSE;
    hit(&intersection_hit_light, &is_there_a_hit, all_intersections_light, &nb_intersections_light);

    if(TRUE == is_there_a_hit && intersection_hit_light.t < distance_with_light
        && intersection_hit_light.object->is_casting_shadow)
    {
        is_in_shadow = TRUE;
    }
    else
    {
        is_in_shadow = FALSE;
    }

    return is_in_shadow;
}



void reflected_color_at(Tuple* reflected_color, World* world, Ray* reflection_ray,
                        double hit_object_material_reflective_value, int remaining_recursive_call)
{
    if (remaining_recursive_call <= 0)
    {
        create_color(reflected_color, 0.0, 0.0, 0.0);
    }
    else if (is_equal(0, hit_object_material_reflective_value))
    {
        create_color(reflected_color, 0.0, 0.0, 0.0);
    }
    else
    {
        color_at(reflected_color, world, reflection_ray, remaining_recursive_call - 1);
        multiply_tuple_by_value(reflected_color,
                                reflected_color, hit_object_material_reflective_value);
    }
}



void color_at(Tuple* pixel_color, World* world, Ray* ray, int remaining_recursive_call)
{
    // 1. Intersect() function:
    Intersection all_intersections[NB_INTERSECTION_PER_RAY];
    int nb_intersections = 0;
    intersect_world_with_ray(all_intersections, &nb_intersections, world, ray);

    if(0 == nb_intersections)
    {
        return;
    }

    // 2. Find the hit from the resulting intersections.
    Intersection intersection_hit;
    boolean is_there_a_hit = FALSE;
    hit(&intersection_hit, &is_there_a_hit, all_intersections, &nb_intersections);

    // 3. If there is no such intersection, return the color black
    if(FALSE == is_there_a_hit)
    {
        create_color(pixel_color, 0.0, 0.0, 0.0); // default black
        return;
    }


    // ------------------------------------------
    // ----> prepare_computation() function <----
    // ------------------------------------------
    // 4. If there is an intersection
    // intersection point
    Tuple hit_point;
    get_point_on_ray(&hit_point, ray, intersection_hit.t);

    Tuple normal_vector_at_hit_point;
    normal_at(&normal_vector_at_hit_point, intersection_hit.object, &hit_point);

    // lighting
    Tuple eye_vector;
    negate_vector(&eye_vector, &(ray->direction));

    // initialize the refrative ratio
    double eta1; // refractive indice of the material before the hit
    double eta2; // refractive indice of the material after the hit
    double ratio_eta2_over_eta1;
    double n_ratio;

    // check if the ray hits inside the object
    if(dot(&normal_vector_at_hit_point, &eye_vector) < EPSILON)
    {   // from inside
        negate_vector(&normal_vector_at_hit_point, &normal_vector_at_hit_point);

        // set refractive ratio Snell Law
        eta1 = intersection_hit.object->material.refractive_index;
        eta2 = WORLD_REFRACTIVE_INDEX;
    }
    else
    {
        // set refractive ratio Snell Law
        eta1 = WORLD_REFRACTIVE_INDEX;
        eta2 = intersection_hit.object->material.refractive_index;
    }
    ratio_eta2_over_eta1 = eta2 / eta1;
    n_ratio = eta1 / eta2;  // p.157

    // offset the point in or out by a small amount
    Tuple small_normal_offset;
    multiply_tuple_by_value(&small_normal_offset, &normal_vector_at_hit_point, EPSILON);
    Tuple over_hit_point;
    adding_tuple(&over_hit_point, &hit_point, &small_normal_offset);
    Tuple under_hit_point;
    substracting_tuple(&under_hit_point, &hit_point, &small_normal_offset);


    // -----------------------------------------
    // --------> shade_hit() function <---------
    // -----------------------------------------
    // 5. Shade hit to find the color at the hit point.
    Tuple surface_color;
    create_color(&surface_color, 0, 0, 0);
    // initialize default canvas color
    boolean is_in_shadow;
    for(int no_light = 0; no_light < (world->number_of_lights); no_light++)
    {
        is_in_shadow = is_shadowed(world, no_light, &over_hit_point);
        // is_in_shadow = TRUE;
        lighting(&surface_color, intersection_hit.object, &(world->lights[no_light]),
            &over_hit_point, &eye_vector, &normal_vector_at_hit_point, is_in_shadow);


    }

    // compute reflection vector
    Tuple reflection_vector;
    reflect_vector(&reflection_vector, &(ray->direction), &normal_vector_at_hit_point);
    Ray reflection_ray;
    create_ray(&reflection_ray, &over_hit_point, &reflection_vector);

    // Reflected color at hit point. Recursive process.
    Tuple reflected_color;
    reflected_color_at(&reflected_color, world, &reflection_ray,
                        intersection_hit.object->material.reflective,
                        remaining_recursive_call);


    // compute refractive indexes around the hit point
    // TODO: already done above both does not support overlapping object

    // -----------------------------------------
    // ----> refracted_color_at() function <----
    // -----------------------------------------
    // Refracted (transmitted) color if the material is transparent
    Tuple refracted_color;
    if(remaining_recursive_call <= 0)
    {
        // no more recurvice call available
        create_color(&refracted_color, 0.0, 0.0, 0.0); // default black
    }
    else if (intersection_hit.object->material.transparency <= 0.0)
    {
        // Material is not transparent
        create_color(&refracted_color, 0.0, 0.0, 0.0); // default black
    }
    else
    {
        Ray refract_ray;
        double cos_i = dot(&normal_vector_at_hit_point, &eye_vector);
        double sin2_t = n_ratio * n_ratio * (1.0 - (cos_i * cos_i));

        if(sin2_t > 1.0)
        {   // total internal reflection, reflection color = black
            create_color(&refracted_color, 0.0, 0.0, 0.0); // black
        }
        else
        {
            double cos_t = sqrt(1.0 - sin2_t);

            Tuple refracted_direction;
            multiply_tuple_by_value(&refracted_direction, &normal_vector_at_hit_point,
                                    (n_ratio * cos_i) - cos_t);
            Tuple temp;
            multiply_tuple_by_value(&temp, &eye_vector, n_ratio);
            substracting_tuple(&refracted_direction, &refracted_direction, &temp);

            create_ray(&refract_ray, &under_hit_point, &refracted_direction);
            color_at(&refracted_color, world, &refract_ray, remaining_recursive_call - 1.0);
            multiply_tuple_by_value(&refracted_color, &refracted_color,
                                    intersection_hit.object->material.transparency);
        }
    }




    if(intersection_hit.object->material.transparency > 0.0 &&
        intersection_hit.object->material.reflective > 0.0)
    {
        // ---> Schlick function ----
        double reflectance = 0.0; // Schlick approximation for reflectance (Fresnel effect)
        double cos = dot(&normal_vector_at_hit_point, &eye_vector);
        double sin2_t = n_ratio * n_ratio * (1.0 - (cos * cos));
        if(eta1 > eta2 && sin2_t > 1.0)
        {
            // total internal reflection
            reflectance = 1.0;
        }
        else
        {
            if (eta1 > eta2 )
            {
                double cos_t = sqrt(1.0 - sin2_t);
                cos = cos_t;
            }
            double temp = (eta1 - eta2) / (eta1 + eta2);
            double r0 =  temp * temp;
            reflectance = r0 + (1.0 - r0) * pow((1.0 - cos), 5);
        }
#if DEBUG
    printf("reflectance: %f\n", reflectance);
#endif
        // --- Schlick function end <----

        multiply_tuple_by_value(&reflected_color, &reflected_color, reflectance);
        multiply_tuple_by_value(&refracted_color, &refracted_color, (1.0 - reflectance));
    }


    // adding the surface, reflected, and refracted colors to the surface color;
    adding_tuple(pixel_color, pixel_color, &surface_color);
    adding_tuple(pixel_color, pixel_color, &reflected_color);
    adding_tuple(pixel_color, pixel_color, &refracted_color);


#if DEBUG
    printf("color_at(): remaining_recursive_call: %d\n", remaining_recursive_call);
    printf("color_at(): intersection t: %f\n", intersection_hit.t );
    printf("color_at(): pixel_color    \t");
    display_tuple(pixel_color);
    printf("color_at(): surface_color  \t");
    display_tuple(&surface_color);
    printf("color_at(): reflected_color\t");
    display_tuple(&reflected_color);
    printf("color_at(): refracted_color\t");
    display_tuple(&refracted_color);
#endif

    return;

}   /* end of color_at() */


#endif /* WORLD_C */