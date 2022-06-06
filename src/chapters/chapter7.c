#include <stdio.h>
// #include "features/world.c"
// #include "features/transformations.c"
#include "features/raytracer.h"


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
    double A[16];
    translation(A, -0.5, 1, 0.5);
    set_transform_object(&sphere1, A);
    add_object(&world, &sphere1);

    Object floor;
    create_sphere(&floor);
    double s[16];
    scaling(s, 10, 0.1, 10);
    set_transform_object(&floor, s);

    add_object(&world, &floor);

    Object wall_left;
    create_sphere(&wall_left);
    double a[16];
    scaling(a, 10, 10, 0.01);
    double b[16];
    translation(b, 0, 3, 3);
    double c[16];
    multiply_matrices(c, b, a);
    set_transform_object(&wall_left, c);
    add_object(&world, &wall_left);

    Object wall_right;
    create_sphere(&wall_right);
    scaling(a, 0.01, 10, 10);
    translation(b, 3, 3, 0);
    multiply_matrices(c, b, a);
    set_transform_object(&wall_right, c);
    add_object(&world, &wall_right);

    printf("nb of objects in your world : %d\n", world.number_of_objects);

    // -----
    // Light
    // -----
    Tuple light_position;
    Tuple light_color_intensity;

    Light myLight;
    create_point(&light_position, -10, 1, -0.1);
    create_color(&light_color_intensity, 0, 0.05, 0.2);
    create_light(&myLight, &light_position, &light_color_intensity);
    add_light(&world, &myLight);

    Light mySecondLight;
    create_point(&light_position, 2, 6, -4);
    create_color(&light_color_intensity, 1, 1, 1);
    create_light(&mySecondLight, &light_position, &light_color_intensity);
    add_light(&world, &mySecondLight);

    printf("nb of lights : %d\n", world.number_of_lights);

    // Camera and canvas
    Canvas myCanvas;

    Camera cam;
    create_camera(&cam, 400, 200, PI/4);

    Tuple from;
    create_point(&from, -4, 1.5, -10);
    Tuple to;
    create_point(&to, 0, 1, 0);
    Tuple up;
    create_vector(&up, 0, 1, 0);
    view_transform(cam.transform, from, to, up);

    // Render
    render(&myCanvas, &cam, &world);
    canvas_to_ppmFile(&myCanvas);
}