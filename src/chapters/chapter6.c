#include <stdio.h>
#include "features/world.c"
#include "features/transformations.c"


void main_chapter7()
{

    // -----
    // World
    // -----
    World world;
    create_world(&world);

    Object sphere1;
    create_sphere(&sphere1);
    Tuple color;
    create_color(&color, 1.0, 0.2, 1.0);
    sphere1.material.color = color;
    double t[16];
    translation(t, 0, 0,  0);
    set_transform_object(&sphere1, t);
    add_object(&world, &sphere1);

    // printf("Sphere1 transform obj-> world:\n");
    // display_matrix(sphere1.transform_object_to_world);
    // printf("Sphere1 transform world -> object:\n");
    // display_matrix(sphere1.transform_world_to_object);

    Object sphere2;
    create_sphere(&sphere2);
    // translate sphere2
    scaling(t, 1, 0.35, 0.35);
    set_transform_object(&sphere2, t);
    add_object(&world, &sphere2);

    // -----
    // Light
    // -----
    Light myLight;
    Tuple light_position;
    Tuple light_color_intensity;
    create_point(&light_position, -10, 10, -10);
    create_color(&light_color_intensity, 1, 1, 1);
    create_light(&myLight, &light_position, &light_color_intensity);
    add_light(&world, &myLight);

    // ------------------
    // Camera and canevas
    // ------------------
    double wall_z = 10;
    double wall_size = 7; //square

    double canvas_pixels = 300;
    Canvas myCanvas = create_canvas(canvas_pixels, canvas_pixels);

    double pixel_size = wall_size / canvas_pixels;
    double half = wall_size / 2;

    // ----
    // Ray
    // ----
    Ray myRay;
    Tuple ray_origin;
    create_point(&ray_origin, 0, 0, -5);

    // variables used in the for-loops below:
    double world_x;
    double world_y;
    Tuple ray_target;
    Tuple ray_direction;
    double t0, t1;
    Intersection * all_intersections;
    Intersection xs;
    Tuple hit_point;
    Tuple pixel_color;
    Tuple eye_vector;
    Tuple normal_vector_at_hit_point;

    // ------------------------------------
    // For each row and column of the image
    // ------------------------------------
    for(int y = 0; y < canvas_pixels; y++)
    {
        world_y = half - (pixel_size * y);
        for(int x = 0; x < canvas_pixels; x++)
        {
            // create ray
            world_x = (-1)*half + (pixel_size * x);
            create_point(&ray_target, world_x, world_y, wall_z);
            substracting_tuple(&ray_direction, &ray_target, &ray_origin);
            create_ray(&myRay, &ray_origin, &ray_direction);

            // ----------------------------
            // For each object in the world
            // ----------------------------
            all_intersections = local_intersect_sphere(&sphere1, &myRay);

            // printf("%f ", all_intersections[0].t);
            // printf("%f ", all_intersections[1].t);

            hit(&xs, all_intersections, 2);
            // xs.t = all_intersections[0].t;

            if( xs.t > EPSILON)
            {
                // intersection
                get_point_on_ray(&hit_point, &myRay, xs.t);
                normal_at_sphere(&normal_vector_at_hit_point, &(sphere1), &hit_point);
                negate_tuple(&eye_vector, &(myRay.direction));

                lighting(&pixel_color, &((sphere1).material), &myLight,
                            &hit_point, &eye_vector, &normal_vector_at_hit_point);

                write_pixel(&myCanvas, x, y, &pixel_color);
            }

        }   // x canvas_pixels
        // printf("\n");
    }   // y canvas_pixels
    canvas_to_ppmFile(&myCanvas);

    return;
}