#include "features/raytracer.h"


void main_chapter8()
{
    // -----
    // Default world
    // -----
    World world;
    create_world(&world);
    // create_default_world(&world);


    Object sphere1;
    create_sphere(&sphere1);
    Tuple color;
    create_color(&color, 1.0, 0.2, 1.0);
    sphere1.material.color = color;
    double A[16];
    translation(A, 0, 1, 1);
    set_transform_object(&sphere1, A);
    add_object(&world, &sphere1);

    Object sphere2;
    create_sphere(&sphere2);
    // Tuple color;
    create_color(&color, 0, 0.8, 0.5);
    sphere2.material.color = color;
    double B[16];
    translation(B, -1, 0, 1);
    set_transform_object(&sphere2, B);
    add_object(&world, &sphere2);

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
    create_point(&light_position, -10, 10, -10);
    create_color(&light_color_intensity, 1, 0.5, 0);
    create_light(&myLight, &light_position, &light_color_intensity);
    add_light(&world, &myLight);

    Light mySecondLight;
    create_point(&light_position, 2, 2, -2);
    create_color(&light_color_intensity, 1, 1, 1);
    create_light(&mySecondLight, &light_position, &light_color_intensity);
    add_light(&world, &mySecondLight);

    printf("nb of lights : %d\n", world.number_of_lights);

    // Camera and canvas
    Canvas myCanvas;

    Camera cam;
    create_camera(&cam, 200, 100, PI/3);

    Tuple from;
    create_point(&from, -8, 3, -10);
    Tuple to;
    create_point(&to, 0, 1, 0);
    Tuple up;
    create_vector(&up, 0, 1, 0);
    view_transform(cam.transform, from, to, up);


    // Render
    render(&myCanvas, &cam, &world);
    canvas_to_ppmFile(&myCanvas);


    // World w;
    // create_default_world(&w);
    // Tuple point;
    // boolean is_it;

    // create_point(&point, 0, 10, 0);
    // is_it = is_shadowed(&w, 0, &point);
    // printf("nothing collinear\n");
    // printf("Shadowed? false : %d\n", is_it);

    // create_point(&point, 10, -10, 10);
    // is_it = is_shadowed(&w, 0, &point);
    // printf("object between point and light\n");
    // printf("Shadowed? true : %d\n", is_it);

    // create_point(&point, -20, 20, -20);
    // is_it = is_shadowed(&w, 0, &point);
    // printf("No shadow, object behing the light\n");
    // printf("Shadowed? false : %d\n", is_it);

    // create_point(&point, -2, 2, -2);
    // is_it = is_shadowed(&w, 0, &point);
    // printf("Object behind the point.\n");
    // printf("shadowed? false : %d\n", is_it);

}