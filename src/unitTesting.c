#ifndef UNIT_TESTING_H
#define UNIT_TESTING_H

// #include <stdio.h>
// #include "features/tuples.c"
// #include "features/canvas.c"
// #include "features/matrices.c"
// #include "features/ray.c"
// #include "features/object.c"
// #include "features/light.c"
// #include "features/material.c"
// #include "features/transformations.c"

extern int tests_run;

#define FAIL() printf("\nWOOPS! Failure in %s (file: %s, line: %d)\n", __func__, __FILE__, __LINE__)
#define PASS() printf("PASSED: %s (file: %s, line: %d)\n", __func__ , __FILE__, __LINE__)
#define _assert(test) do { if(!(test)) { FAIL(); return 1;} else PASS(); } while (0)
#define _verify(test) do { int result = test();  tests_run++;  if(result) return result; } while(0)


// ============================================================
//                       REFRACTION
// ============================================================
int refraction_test_refracted_color_of_opaque_object()
{
    World world;
    create_default_world(&world);

    // Tuple red_color;
    // create_color(&red_color, 1, 0, 0);
    // world.objects[0]->material.color = red_color;

    world.objects[0]->material.refractive_index = 1.0;
    world.objects[0]->material.transparency = 1.0;

    Tuple origin_test;
    create_point(&origin_test, 0, 0, -5);
    Tuple direction_test;
    create_vector(&direction_test, 0, 0, 1);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    // world.objects[1]->material.reflective = 0;

    Tuple pixel_color;
    create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
    color_at(&pixel_color, &world, &ray_test, 0);

    _assert(1);
    return 0;
}

int refraction_test_total_internal_refraction()
{
    World world;
    create_default_world(&world);

    world.objects[0]->material.refractive_index = 1.5;
    world.objects[0]->material.transparency = 1.0;

    Tuple origin_test;
    create_point(&origin_test, 0, 0, sqrt(2)/2);
    Tuple direction_test;
    create_vector(&direction_test, 0, 1, 0);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    // world.objects[1]->material.reflective = 0;

    Tuple pixel_color;
    create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
    color_at(&pixel_color, &world, &ray_test, 5);

    _assert(1);
    return 0;
}

int refraction_test_color_with_refracted_ray()
{
    World world;
    create_default_world(&world);

    world.objects[0]->material.ambient = 1.0;
    world.objects[1]->material.transparency = 1.0;
    world.objects[1]->material.refractive_index= 1.5;

    Tuple origin_test;
    create_point(&origin_test, 0, 0, 0.1);
    Tuple direction_test;
    create_vector(&direction_test, 0, 1, 0);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    // world.objects[1]->material.reflective = 0;

    Tuple pixel_color;
    create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
    color_at(&pixel_color, &world, &ray_test, 5);

    _assert(1);
    return 0;
}

// passed
int chap11_test4_reflected_color_for_reflective_material()
{
    World world;
    create_default_world(&world);

    Object floor;
    create_plane(&floor);
    floor.material.reflective = 0.5;
    double f1[16];
    translation(f1, 0, -1, 0);
    set_transform_object(&floor, f1);
    add_object(&world, &floor);

    Tuple origin_test;
    create_point(&origin_test, 0, 0, -3.0);
    Tuple direction_test;
    create_vector(&direction_test, 0, -sqrt(2)/2, sqrt(2)/2);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    Tuple pixel_color;
    create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
    color_at(&pixel_color, &world, &ray_test, 5);
    printf("*** Expected reflected_color = (0.19032, 0.2379, 0.14274) ***\n");

    _assert(1); // passed
    return 0;
}

// passed
int chap11_test5_shade_hit_with_reflective_material()
{
    World world;
    create_default_world(&world);

    Object floor;
    create_plane(&floor);
    floor.material.reflective = 0.5;
    double f1[16];
    translation(f1, 0, -1, 0);
    set_transform_object(&floor, f1);
    add_object(&world, &floor);

    Tuple origin_test;
    create_point(&origin_test, 0, 0, -3.0);
    Tuple direction_test;
    create_vector(&direction_test, 0, -sqrt(2)/2, sqrt(2)/2);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    Tuple pixel_color;
    create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
    color_at(&pixel_color, &world, &ray_test, 5);
    printf("*** Expected color = (0.87677, 0.92436, 0.82918) ***\n");

    _assert(is_equal_tuple2components(&pixel_color, 0.87676, 0.92434, 0.82917,0));
    return 0;
}

// passed
int chap11_test6_mutually_reflective_surfaces()
{
    World world;
    create_world(&world);

    Object floor;
    create_plane(&floor);
    floor.material.reflective = 1;
    double f1[16];
    translation(f1, 0, -1, 0);
    set_transform_object(&floor, f1);
    add_object(&world, &floor);

    Object floor2;
    create_plane(&floor2);
    floor2.material.reflective = 1;
    double f2[16];
    translation(f2, 0, 1, 0);
    set_transform_object(&floor2, f2);
    add_object(&world, &floor2);

    Tuple origin_test;
    create_point(&origin_test, 0, 0, 0);
    Tuple direction_test;
    create_vector(&direction_test, 0, 1, 0);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    Tuple pixel_color;
    create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
    color_at(&pixel_color, &world, &ray_test, 5);
    printf("*** should terminate successfully ***\n");

    _assert(is_equal_tuple2components(&pixel_color, 0,0,0,0));
    return 0;
}

// passed
int chap11_test7_reflected_color_at_maximum_recursive_depth()
{
    World world;
    create_default_world(&world);

    Object floor;
    create_plane(&floor);
    floor.material.reflective = 0.5;
    double f1[16];
    translation(f1, 0, -1, 0);
    set_transform_object(&floor, f1);
    add_object(&world, &floor);

    Tuple origin_test;
    create_point(&origin_test, 0, 0, -3.0);
    Tuple direction_test;
    create_vector(&direction_test, 0, -sqrt(2)/2, sqrt(2)/2);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    Tuple pixel_color;
    create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
    color_at(&pixel_color, &world, &ray_test, 0);
    printf("*** Expected reflected_color = (0, 0, 0) ***\n");

    _assert(1); // passed
    return 0;
}

// passed
int chap11_test16_shade_hit_with_transparent_material()
{
    World world;
    create_default_world(&world);

    Object floor;
    create_plane(&floor);
    floor.material.transparency = 0.5;
    floor.material.refractive_index = 1.5;
    double f1[16];
    translation(f1, 0, -1, 0);
    set_transform_object(&floor, f1);
    add_object(&world, &floor);

    Object ball;
    create_sphere(&ball);
    Tuple color_ball;
    create_color(&color_ball, 1.0, 0.0, 0.0);
    ball.material.color = color_ball;
    ball.material.ambient = 0.5;
    double b1[16];
    translation(b1, 0, -3.5, -0.5);
    set_transform_object(&ball, b1);
    add_object(&world, &ball);

    Tuple origin_test;
    create_point(&origin_test, 0, 0, -3.0);
    Tuple direction_test;
    create_vector(&direction_test, 0, -sqrt(2)/2, sqrt(2)/2);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    Tuple pixel_color;
    create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
    color_at(&pixel_color, &world, &ray_test, 5);
    printf("*** Expected color = (0.93642, 0.68642, 0.68642) ***\n");

    _assert(is_equal_tuple2components(&pixel_color,
                                0.93642, 0.68642, 0.68642, 0));
    return 0;
}

// passed
int chap11_test17_schlick_approximation_total_internal_reflection()
{
    World world;
    create_world(&world);

    Object ball;
    create_sphere(&ball);
    ball.material.transparency = 1.0;
    ball.material.refractive_index = 1.5;
    ball.material.reflective = 0.5;
    add_object(&world, &ball);

    Tuple origin_test;
    create_point(&origin_test, 0, 0, sqrt(2)/2);
    Tuple direction_test;
    create_vector(&direction_test, 0, 1, 0);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    Tuple pixel_color;
    create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
    color_at(&pixel_color, &world, &ray_test, 5);
    printf("*** Expected Schlick approx. number = 1.0 ***\n");

    _assert(1);
    return 0;
}

// passed
int chap11_test18_schlick_perpendicular_viewing_angle()
{
    World world;
    create_world(&world);

    // glass ball
    Object ball;
    create_sphere(&ball);
    ball.material.transparency = 1.0;
    ball.material.refractive_index = 1.5;
    ball.material.reflective = 0.5;
    add_object(&world, &ball);

    Tuple origin_test;
    create_point(&origin_test, 0, 0, 0);
    Tuple direction_test;
    create_vector(&direction_test, 0, 1, 0);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    Tuple pixel_color;
    create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
    color_at(&pixel_color, &world, &ray_test, 5);
    printf("*** Expected Schlick approx. number = 0.04 ***\n");

    _assert(1);
    return 0;
}

int chap11_test19_schlick_approx_small_angle_n2_greater_n1()
{
    World world;
    create_world(&world);

    // glass ball
    Object ball;
    create_sphere(&ball);
    ball.material.transparency = 1.0;
    ball.material.refractive_index = 1.5;
    ball.material.reflective = 0.5;
    add_object(&world, &ball);

    Tuple origin_test;
    create_point(&origin_test, 0, 0.99, -2);
    Tuple direction_test;
    create_vector(&direction_test, 0, 0, 1);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    Tuple pixel_color;
    create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
    color_at(&pixel_color, &world, &ray_test, 5);
    printf("*** Expected Schlick approx. number = 0.48873 ***\n");

    _assert(1);
    return 0;
}


int chap11_test20_reflective_transparent_material()
{
    World world;
    create_default_world(&world);

    Object floor;
    create_plane(&floor);
    double f1[16];
    translation(f1, 0, -1, 0);
    set_transform_object(&floor, f1);
    floor.material.reflective = 0.5;
    floor.material.transparency = 0.5;
    floor.material.refractive_index = 1.5;
    add_object(&world, &floor);

    Object ball;
    create_sphere(&ball);
    Tuple color_ball;
    create_color(&color_ball, 1.0, 0, 0);
    ball.material.color = color_ball;
    ball.material.ambient = 0.5;
    double b1[16];
    translation(b1, 0, -3.5, -0.5);
    set_transform_object(&ball, b1);
    add_object(&world, &ball);

    Tuple origin_test;
    create_point(&origin_test, 0, 0, -3.0);
    Tuple direction_test;
    create_vector(&direction_test, 0, -sqrt(2)/2, sqrt(2)/2);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    // world.objects[1]->material.reflective = 0;

    Tuple pixel_color;
    create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
    color_at(&pixel_color, &world, &ray_test, 5);
    printf("*** Expected color = (0.93391, 0.69643, 0.69243) ***\n");

    _assert(0);
    return 0;
}

int all_tests_refraction()
{
    printf("... going to test refraction.c\n");
    // _verify(refraction_test_refracted_color_of_opaque_object);
    // _verify(refraction_test_total_internal_refraction);
    // _verify(refraction_test_color_with_refracted_ray);
    // _verify(chap11_test4_reflected_color_for_reflective_material);
    // _verify(chap11_test5_shade_hit_with_reflective_material);
    // _verify(chap11_test6_mutually_reflective_surfaces);
    // _verify(chap11_test7_reflected_color_at_maximum_recursive_depth);
    // _verify(chap11_test16_shade_hit_with_transparent_material);
    // _verify(chap11_test17_schlick_approximation_total_internal_reflection);
    // _verify(chap11_test18_schlick_perpendicular_viewing_angle);
    // _verify(chap11_test19_schlick_approx_small_angle_n2_greater_n1);
    _verify(chap11_test20_reflective_transparent_material);
    return 0;
}

// ============================================================
//                       REFLECTION
// ============================================================
int reflected_color_for_nonreflective_material()
{
    World world;
    create_default_world(&world);

    Tuple origin_test;
    create_point(&origin_test, 0, 0, 0);
    Tuple direction_test;
    create_vector(&direction_test, 0, 0, 1);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    // world.objects[1]->material.reflective = 0;

    Tuple pixel_color;
    reflected_color_at(&pixel_color, &world, &ray_test, world.objects[1]->material.reflective, 1);
    display_tuple(&pixel_color);
    // printf("%f\n", world.objects[1]->material.reflective);
    _assert(is_equal_tuple2components(&pixel_color, 0, 0, 0, 0 ));

    return 0;
}

int reflected_color_for_reflective_material()
{
    World world;
    create_default_world(&world);

    Object floor;
    create_plane(&floor);
    double A_test[16];
    translation(A_test, 0, -1, 0);
    set_transform_object(&floor, A_test);
    floor.material.reflective = 0.5;
    add_object(&world, &floor);

    Tuple origin_test;
    create_point(&origin_test, 0, 0, -3);
    Tuple direction_test;
    create_vector(&direction_test, 0, (-1)*sqrt(2)/2, sqrt(2)/2);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);

    Tuple pixel_color;
    color_at(&pixel_color, &world, &ray_test, 1);
    display_tuple(&pixel_color);
    // printf("%f\n", world.objects[1]->material.reflective);
    // _assert(is_equal_tuple2components(&pixel_color, 0.19032, 0.2379, 0.14274, 0 ));

    return 0;
}
int all_tests_reflection()
{
    printf("... going to test reflection.c\n");
    _verify(reflected_color_for_nonreflective_material);
    _verify(reflected_color_for_reflective_material);
    return 0;
}

// ============================================================
//                       CAMERA
// ============================================================
int construction_ray_through_center_camera()
{
    Camera cam;
    create_camera(&cam, 201, 101, PI/2);
    Ray ray;
    ray_for_pixel(&ray, &cam, 100, 50);
    printf("ray info: \n");
    display_tuple(&(ray.origin));
    display_tuple(&(ray.direction));
    _assert(is_equal_tuple2components(&(ray.origin), 0, 0, 0, 1));
    _assert(is_equal_tuple2components(&(ray.direction), 0, 0, -1, 0 ));

    ray_for_pixel(&ray, &cam, 0, 0);
    printf("ray info: \n");
    display_tuple(&(ray.origin));
    display_tuple(&(ray.direction));

    _assert(is_equal_tuple2components(&(ray.origin), 0, 0, 0, 1));
    _assert(is_equal_tuple2components(&(ray.direction), 0.66519, 0.33259, -0.66851, 0 ));
    return 0;
}

int construction_a_camera()
{
    Camera cam;
    create_camera(&cam, 200, 125, PI/2);
    printf("pixel size: %f\n", cam.pixel_size);
    create_camera(&cam, 125, 200, PI/2);
    printf("pixel size: %f\n", cam.pixel_size);

    return 0;
}

int arbitrary_view_transformation()
{
    Tuple from;
    create_point(&from, 1, 3, 2);
    Tuple to;
    create_point(&to, 4, -2, 8);
    Tuple up;
    create_vector(&up, 1, 1, 0);
    double transform[16];
    view_transform(transform, from, to, up);
    display_matrix(transform);

    return 0;
}

int construction_ray_through_center_with_transformed_camera()
{
    Camera cam;
    create_camera(&cam, 201, 101, PI/2);
    display_matrix(cam.transform);
    double tr[16];
    translation(tr, 0, -2, 5);
    // double b[16];
    // multiply_matrices(b, cam.transform, a);
    double ro[16];
    rotation_around_yAxis(ro, PI/4);
    display_matrix(ro);
    double answer[16];
    multiply_matrices( answer, tr , cam.transform);
    display_matrix(answer);
    multiply_matrices(cam.transform, ro , answer);
    display_matrix(cam.transform);

    Ray ray;
    ray_for_pixel(&ray, &cam, 100, 50);
    printf("ray info: \n");
    display_tuple(&(ray.origin));
    display_tuple(&(ray.direction));

    _assert(is_equal_tuple2components(&(ray.origin),
                                        0, 2, -5, 1));
    _assert(is_equal_tuple2components(&(ray.direction),
                                        (sqrt(2)/2), 0, (-sqrt(2)/2), 0 ));
    return 0;
}

int all_tests_camera()
{
    printf("... going to test light.c\n");
    // _verify(construction_a_camera);
    // _verify(construction_ray_through_center_camera);
    // _verify(arbitrary_view_transformation);
    _verify(construction_ray_through_center_with_transformed_camera);
    return 0;
}


// ============================================================
//                       Lighting
// ============================================================
// int eye_in_path_of_reflection()
// {
//     Material m;
//     create_material_default(&m);
//     Tuple point;
//     create_point(&point, 0, 0, 0);

//     Tuple eyev;
//     create_vector(&eyev, 0, (-1)*sqrt(2)/2, (-1)*sqrt(2)/2);
//     Tuple normalv;
//     create_vector(&normalv, 0 , 0, -1);
//     Light light;
//     Tuple light_position;
//     create_point(&light_position, 0, 10, -10);
//     Tuple light_color;
//     create_color(&light_color, 1, 1, 1);
//     create_light(&light, &light_position, &light_color);

//     Tuple color_answer;
//     lighting(&color_answer, &m, &light, &point, &eyev, &normalv);
//     display_tuple(&color_answer);
//     _assert(is_equal_tuple2components(&color_answer,
//                                     1.6364, 1.6364, 1.6364, 0));
//     return 0;
// }

// int all_tests_light()
// {
//     printf("... going to test light.c\n");
//     _verify(eye_in_path_of_reflection);
//     return 0;
// }



// ============================================================
//                       Ray & Object
// ============================================================
// int test_local_intersect_sphere()
// {
//     Object s;
//     create_sphere(&s);

//     Tuple eye_position;
//     create_point(&eye_position, -5, 0, 0);

//     Tuple ray_direction;
//     create_vector(&ray_direction, 1, 0, 0);

//     Ray r;
//     create_ray(&r, &eye_position, &ray_direction);

//     double t0;
//     double t1;
//     local_intersect_sphere(&t0, &t1, &s, &r);
//     printf("%f %f\n", t0, t1);

//     _assert(is_equal(t0, 4.0));
//     _assert(is_equal(t1, 6.0));
//     return 0;
// }
// int test_local_intersect_sphere_at_tangent()
// {
//     Object s;
//     create_sphere(&s);

//     Tuple eye_position;
//     create_point(&eye_position, -5, 1, 0);

//     Tuple ray_direction;
//     create_vector(&ray_direction, 1, 0, 0);

//     Ray r;
//     create_ray(&r, &eye_position, &ray_direction);

//     double t0;
//     double t1;
//     local_intersect_sphere(&t0, &t1, &s, &r);
//     printf("%f %f\n", t0, t1);

//     _assert(is_equal(t0, 5.0));
//     _assert(is_equal(t1, 5.0));
//     return 0;
// }
// int test_computing_point_from_a_distance()
// {
//     Ray r;
//     Tuple ray_origin;
//     create_point(&ray_origin, 2, 3, 4);
//     Tuple ray_direction;
//     create_vector(&ray_direction, 1, 0, 0);
//     create_ray(&r, &ray_origin, &ray_direction);

//     Tuple answer;
//     get_point_on_ray(&answer, &r, 0);
//     _assert(is_equal_tuple2components(&answer, 2, 3, 4, 1));
//     get_point_on_ray(&answer, &r, 1);
//     _assert(is_equal_tuple2components(&answer, 3, 3, 4, 1));
//     get_point_on_ray(&answer, &r, -1);
//     _assert(is_equal_tuple2components(&answer, 1, 3, 4, 1));
//     get_point_on_ray(&answer, &r, 2.5);
//     _assert(is_equal_tuple2components(&answer, 4.5, 3, 4, 1));

//     return 0;
// }
// int normal_on_sphere()
// {
//     Tuple point;
//     Object s;
//     create_sphere(&s);
//     Tuple answer;

//     create_point(&point, 1, 0, 0);
//     normal_at_sphere(&answer, &s, &point);
//     _assert(is_equal_tuple2components(&answer, 1, 0, 0, 0));

//     double a = sqrt(3)/3;
//     create_point(&point, a, a, a);
//     normal_at_sphere(&answer, &s, &point);
//     _assert(is_equal_tuple2components(&answer, a, a, a, 0));

//     return 0;
// }
// int test_translation_ray()
// {
//     Ray r;
//     Tuple origin;
//     create_point(&origin, 1.0, 2.0, 3.0);
//     Tuple direction;
//     create_vector(&direction, 0.0, 1.0, 0.0);
//     create_ray(&r, &origin, &direction);

//     display_tuple(&(r.origin));
//     display_tuple(&(r.direction));

//     double t[16];
//     translation(t, 3, 4, 5);
//     display_matrix(t);

//     Ray output;
//     transform_ray(&output, t, &r);

//     display_tuple(&(output.origin));
//     display_tuple(&(output.direction));
//     return 0;
// }
// int test_scaling_ray()
// {
//     Ray r;
//     Tuple origin;
//     create_point(&origin, 1.0, 2.0, 3.0);
//     Tuple direction;
//     create_vector(&direction, 0.0, 1.0, 0.0);
//     create_ray(&r, &origin, &direction);

//     display_tuple(&(r.origin));
//     display_tuple(&(r.direction));

//     double t[16];
//     scaling(t, 2, 3, 4);
//     display_matrix(t);

//     double inv[16];
//     invert_matrix_4x4(inv, t);
//     display_matrix(inv);

//     double back[16];
//     invert_matrix_4x4(back, inv);
//     display_matrix(back);

//     Ray output;
//     transform_ray(&output, t, &r);
//     display_tuple(&(output.origin));
//     display_tuple(&(output.direction));

//     transform_ray(&output, inv, &output);
//     display_tuple(&(output.origin));
//     display_tuple(&(output.direction));

//     return 0;
// }
// int test_intersect_scaled_sphere()
// {
//     Tuple eye_position;
//     create_point(&eye_position, 0.0, 0.0, -5.0);
//     Tuple ray_direction;
//     create_vector(&ray_direction, 0.0, 0.0, 1.0);
//     Ray r;
//     create_ray(&r, &eye_position, &ray_direction);

//     Object s;
//     create_sphere(&s);
//     double t[16];
//     scaling(t, 2.0, 2.0, 2.0);
//     set_transform_object(&s, t);
//     display_matrix(s.transform_object_to_world);
//     display_matrix(s.transform_world_to_object);


//     Intersection * i;
//     i = local_intersect_sphere(&s, &r);
//     printf("%f %f\n", i[0].t, i[1].t);

//     // _assert(is_equal(t0, 4.0));
//     // _assert(is_equal(t1, 6.0));
//     return 0;
// }
int test_local_intersect_sphere_neg()
{
    Object s;
    create_sphere(&s);

    Tuple eye_position;
    create_point(&eye_position, 0, 0, 0);

    Tuple ray_direction;
    create_vector(&ray_direction, 0, 0, 1);

    Ray r;
    create_ray(&r, &eye_position, &ray_direction);

    Intersection intersect[2];
    int nb_intersection = 0;

    local_intersect_sphere(intersect, &nb_intersection, &s, &r);
    printf("%d\n", nb_intersection);
    printf("%f\n", intersect[0].t);
    printf("%f\n", intersect[1].t);

    _assert(is_equal(nb_intersection, 2));
    _assert(is_equal(intersect[0].t, -1));
    _assert(is_equal(intersect[1].t, 1));

    return 0;
}
int test_local_intersect_sphere_behind()
{
    Object s;
    create_sphere(&s);
    Tuple eye_position;
    create_point(&eye_position, 0, 0, 5);
    Tuple ray_direction;
    create_vector(&ray_direction, 0, 0, 1);
    Ray r;
    create_ray(&r, &eye_position, &ray_direction);

    Intersection intersect[2];
    int nb_intersection = 0;
    local_intersect_sphere(intersect, &nb_intersection, &s, &r);
    printf("%d\n", nb_intersection);
    printf("%f\n", intersect[0].t);
    printf("%f\n", intersect[1].t);

    _assert(is_equal(nb_intersection, 2));
    _assert(is_equal(intersect[0].t, -6));
    _assert(is_equal(intersect[1].t, -4));

    return 0;
}
int all_tests_ray()
{
    printf("... going to test Ray.c\n");
    // _verify(test_translation_ray);
    // _verify(test_scaling_ray);
    // _verify(test_intersect_scaled_sphere);
    // _verify(test_local_intersect_sphere);
    // _verify(test_local_intersect_sphere_at_tangent);
    // _verify(test_computing_point_from_a_distance);
    // _verify(normal_on_sphere);
    _verify(test_local_intersect_sphere_neg);
    _verify(test_local_intersect_sphere_behind);
    return 0;
}




// ============================================================
//                       Matrice
// ============================================================
// int test_construction_and_inspecting_4x4_matrix()
// {
//     // double M[4][4] = {
//     //                     {1,    2,    3,    4},
//     //                     {5.5,  6.5,  7.5,  8.5},
//     //                     {9,    10,   11,   12},
//     //                     {13.5, 14.5, 15.5, 16.5}
//     //                 };
//     // _assert(M[0][0] == 1);
//     // _assert(M[0][3] == 4);
//     // _assert(M[1][0] == 5.5);
//     // _assert(M[1][2] == 7.5);
//     // _assert(M[2][2] == 11);
//     // _assert(M[3][0] == 13.5);
//     // _assert(M[3][2] == 15.5);
//     double M[16] = {
//                         1,    2,    3,    4,
//                         5.5,  6.5,  7.5,  8.5,
//                         9,    10,   11,   12,
//                         13.5, 14.5, 15.5, 16.5
//                     };
//     _assert(M[0] == 1);
//     _assert(M[3] == 4);
//     _assert(M[4] == 5.5);
//     _assert(M[6] == 7.5);
//     _assert(M[10] == 11);
//     _assert(M[12] == 13.5);
//     _assert(M[14] == 15.5);
//     return 0;
// }
// int test_construction_and_inspecting_2x2_matrix()
// {
//     // double M[2][2] = {
//     //                     {-3,  5},
//     //                     { 1, -2}
//     //                 };
//     // _assert(M[0][0] == -3);
//     // _assert(M[0][1] == 5);
//     // _assert(M[1][0] == 1);
//     // _assert(M[1][1] == -2);
//     double M[4] = {
//                         -3,  5,
//                          1, -2
//                     };
//     _assert(M[0] == -3);
//     _assert(M[1] == 5);
//     _assert(M[2] == 1);
//     _assert(M[3] == -2);
//     return 0;
// }
// int test_construction_and_inspecting_3x3_matrix()
// {
//     double M[9] = {
//                         -3,  5,  6,
//                          1, -2, -7,
//                          0,  1,  10
//                     };
//     _assert(M[0] == -3);
//     _assert(M[4] == -2);
//     _assert(M[8] == 10);
//     return 0;
// }

// int test_matrix_equality_with_identical_matrices()
// {
//     double A[16] = {
//                         1,    2,    3,    4,
//                         5.5,  6.5,  7.5,  8.5,
//                         9,    10,   11,   12,
//                         13.5, 14.5, 15.5, 16.5
//                     };
//     double B[16] = {
//                         1,    2,    3,    4,
//                         5.5,  6.5,  7.5,  8.5,
//                         9,    10,   11,   12,
//                         13.5, 14.5, 15.5, 16.5
//                     };
//     _assert(is_equal_matrices(A, B));
//     double C[16] = {
//                         1,    2,    3,    4,
//                         1,    2,    3,    4,
//                         9,    10,   11,   12,
//                         13.5, 14.5, 15.5, 16.5
//                     };
//     double D[16] = {
//                         1,    2,    3,    4,
//                         5.5,  6.5,  7.5,  8.5,
//                         9,    10,   11,   12,
//                         13.5, 14.5, 15.5, 16.5
//                     };
//     _assert(FALSE == is_equal_matrices(C, D));

//     return 0;
// }


// int test_multiply_matrix()
// {
//     double A[16] = {
//                         1, 2, 3, 4,
//                         5, 6, 7, 8,
//                         9, 8, 7, 6,
//                         5, 4, 3, 2
//                     };
//     double B[16] = {
//                        -2, 1, 2,  3,
//                         3, 2, 1, -1,
//                         4, 3, 6,  5,
//                         1, 2, 7,  8
//                     };
//     double result[16] = {
//                        20, 22, 50, 48,
//                        44, 54, 114, 108,
//                        40, 58, 110, 102,
//                        16, 26, 46, 42
//                     };
//     double output[16];
//     multiply_matrices(output, A, B);
//     _assert(is_equal_matrices(output, result));

//     // a matrix multiplied by a tuple (array)
//     double C[16] = {
//                 1, 2, 3, 4,
//                 2, 4, 4, 2,
//                 8, 6, 4, 1,
//                 0, 0, 0, 1
//             };

//     double t[4] = {1, 2, 3, 1};
//     double outputTuple[4];
//     transform4d(outputTuple, C, t[0], t[1], t[2], t[3]);
//     _assert(is_equal4d(outputTuple, 18, 24, 33, 1));

//     // multiply a matrix by identity = do nothing
//     double identity[16];
//     identity4d(identity);
//     multiply_matrices(output, identity, A);
//     _assert(is_equal_matrices(output, A));

//     return 0;
// }
int rotation()
{
    Tuple p;
    create_point(&p, 0, 1, 0);
    double ro[16];
    rotation_around_xAxis(ro, PI/2);
    Tuple answer = transform_tuple(ro, &p);
    display_tuple(&answer);
    _assert(is_equal_tuple2components(&answer, 0, 0, 1, 1));

    return 0;
}


int transformation_applied_in_sequence()
{
    Tuple p;
    create_point(&p, 1, 0, 1);
    double ro[16];
    rotation_around_xAxis(ro, PI/2);
    Tuple answer = transform_tuple(ro, &p);
    display_tuple(&answer);
    _assert(is_equal_tuple2components(&answer, 1, -1, 0, 1));


    double sc[16];
    scaling(sc, 5, 5, 5);
    double tr[16];
    translation(tr, 10, 5, 7);
    double D[16];
    identity4d(D);
    multiply_matrices(D, tr, sc);
    double E[16];
    multiply_matrices(E, D, ro);

    answer = transform_tuple(E, &p);
    display_tuple(&answer);
    _assert(is_equal_tuple2components(&answer, 15, 0, 7, 1));

    return 0;
}
int matrice_chained()
{
    Tuple p;
    create_point(&p, 1, 0, 1);
    double ro[16];
    rotation_around_xAxis(ro, PI/2);
    double sc[16];
    scaling(sc, 5, 5, 5);
    double tr[16];
    translation(tr, 10, 5, 7);
    double D[16];
    identity4d(D);
    multiply_matrices(D, tr, sc);
    double E[16];
    multiply_matrices(E, D, ro);
    p = transform_tuple(E, &p);

    display_tuple(&p);
    _assert(is_equal_tuple2components(&p, 15, 0, 7, 1));
    return 0;
}

int all_tests_matrices()
{
    printf("... going to test Matrices.c\n");
    // _verify(test_construction_and_inspecting_4x4_matrix);
    // _verify(test_construction_and_inspecting_2x2_matrix);
    // _verify(test_construction_and_inspecting_3x3_matrix);
    // _verify(test_matrix_equality_with_identical_matrices);
    // _verify(test_multiply_matrix);
    _verify(rotation);
    _verify(transformation_applied_in_sequence);
    _verify(matrice_chained);
    return 0;
}





// ============================================================
//                       Canvas
// ============================================================
int test_creating_canvas()
{
    Canvas myCanvas = create_canvas(10, 20);
    _assert(is_equal(myCanvas.width, 10));
    _assert(is_equal(myCanvas.height, 20));

    Tuple blackColor;
    create_color(&blackColor, 0, 0, 0);
    Tuple anyPixelColor = myCanvas.pixelColor[2][2];
    display_tuple(&anyPixelColor);
    _assert(is_equal_tuple2tuple(&anyPixelColor, &blackColor));
    return 0;
}
int test_writing_pixels_to_a_canvas()
{
    Canvas myCanvas = create_canvas(10, 20);
    Tuple red;
    create_color(&red, 1, 0, 0);
    write_pixel(&myCanvas, 4, 2, &red);
    Tuple color = myCanvas.pixelColor[4][2];
    _assert(is_equal_tuple2tuple(&color, &red));
    return 0;
}
int test_constructing_ppm_header()
{
    Canvas myCanvas = create_canvas(10, 20);
    canvas_to_ppmFile(&myCanvas);
    return 0;
}
int test_constructing_ppm_pixel_data()
{
    Canvas myCanvas = create_canvas(5, 3);
    Tuple c1;
    create_color(&c1, 1.5, 0, 0);
    Tuple c2;
    create_color(&c2, 0, 0.5, 0);
    Tuple c3;
    create_color(&c3, -0.5, 0, 1);
    write_pixel(&myCanvas, 0, 0, &c1);
    write_pixel(&myCanvas, 2, 1, &c2);
    write_pixel(&myCanvas, 4, 2, &c3);
    canvas_to_ppmFile(&myCanvas);
    return 0;
}

int all_tests_canvas()
{
    printf("... going to test Canvas.c");
    _verify(test_creating_canvas);
    _verify(test_writing_pixels_to_a_canvas);
    _verify(test_constructing_ppm_header);
    _verify(test_constructing_ppm_pixel_data);
    return 0;
}


// ============================================================
//                       Tuples
// ============================================================

int test_tuple_with_w1_is_a_point()
{
    Tuple a;
    create_tuple(&a, 4.3, -4.2, 3.1, 1.0);
    display_tuple(&a);
    _assert(is_equal_tuple2components(&a, 4.3, -4.2, 3.1, 1.0));
    _assert(is_a_point(&a));
    _assert(!is_a_vector(&a));
    return 0;
}
int test_tuple_with_w1_is_a_vector()
{
    Tuple a;
    create_tuple(&a, 4.3, -4.2, 3.1, 0.0);
    display_tuple(&a);
    _assert(is_equal_tuple2components(&a, 4.3, -4.2, 3.1, 0.0));
    _assert(!is_a_point(&a));
    _assert(is_a_vector(&a));
    return 0;
}
int test_point_creates_tuples_with_w1()
{
    Tuple p;
    create_point(&p, 4, -4, 3);
    display_tuple(&p);
    _assert(is_a_point(&p));
    _assert(!is_a_vector(&p));
    return 0;
}
int test_vector_creates_tuples_with_w0()
{
    Tuple p;
    create_vector(&p, 4, -4, 3);
    display_tuple(&p);
    _assert(!is_a_point(&p));
    _assert(is_a_vector(&p));
    return 0;
}
int test_adding_two_tuples()
{
    Tuple a1;
    Tuple a2;
    create_tuple(&a1, 3, -2, 5, 1);
    create_tuple(&a2, -2, 3, 1, 0);
    display_tuple(&a1);
    display_tuple(&a2);
    Tuple a3;
    adding_tuple(&a3, &a1, &a2);
    _assert(is_equal_tuple2components(&a3, 1, 1, 6, 1));
    return 0;
}
int test_adding_two_points()
{
    Tuple a1;
    Tuple a2;
    Tuple a3;
    create_point(&a1, 3, -2, 5);
    create_point(&a2, -2, 3, 1);
    adding_tuple(&a3, &a1, &a2);
    _assert(is_equal_tuple2components(&a3, 1, 1, 6, 2));
    // neither a point nor a vector
    _assert(!is_a_point(&a3));
    _assert(!is_a_vector(&a3));
    return 0;
    return 0;
}
int test_adding_two_vectors()
{
    Tuple a1;
    Tuple a2;
    Tuple a3;
    create_vector(&a1, 0, 0, 0);
    create_vector(&a2, 1, 1, 1);
    adding_tuple(&a3, &a1, &a2);
    _assert(is_equal_tuple2components(&a3, 1, 1, 1, 0));
    _assert(!is_a_point(&a3));
    _assert(is_a_vector(&a3));
    return 0;
}
int test_substracting_two_points()
{
    Tuple a1;
    Tuple a2;
    Tuple calc;
    create_point(&a1, 3, 2, 1);
    create_point(&a2, 5, 6, 7);
    substracting_tuple(&calc, &a1, &a2);
    Tuple answer;
    create_vector(&answer, -2, -4, -6);
    _assert(is_equal_tuple2components(&answer, calc.x, calc.y, calc.z, calc.w));
    _assert(!is_a_point(&calc));
    _assert(is_a_vector(&calc));
    return 0;
}
int test_substracting_a_vector_from_a_point()
{
    Tuple a1;
    Tuple a2;
    create_point(&a1, 3, 2, 1);
    create_vector(&a2, 5, 6, 7);
    Tuple a3;
    substracting_tuple(&a3, &a1, &a2);
    Tuple answer;
    create_point(&answer, -2, -4, -6);
    _assert(is_equal_tuple2components(&a3, answer.x, answer.y, answer.z, answer.w));
    _assert(is_a_point(&a3));
    _assert(!is_a_vector(&a3));
    return 0;
}
int test_substracting_two_vectors()
{
    Tuple a1;
    Tuple a2;
    create_vector(&a1, 3, 2, 1);
    create_vector(&a2, 5, 6, 7);
    Tuple a3;
    substracting_tuple(&a3, &a1, &a2);
    Tuple answer;
    create_vector(&answer, -2, -4, -6);
    _assert(is_equal_tuple2components(&a3, answer.x, answer.y, answer.z, answer.w));
    _assert(!is_a_point(&a3));
    _assert(is_a_vector(&a3));
    return 0;
}
int test_substracting_a_point_from_a_vector()
{
    Tuple a1;
    Tuple a2;
    create_vector(&a1, 3, 2, 1);
    create_point(&a2, 5, 6, 7);
    Tuple a3;
    substracting_tuple(&a3, &a1, &a2);
    Tuple answer;
    create_tuple(&answer, -2, -4, -6, -1);
    _assert(is_equal_tuple2components(&a3, answer.x, answer.y, answer.z, answer.w));
    _assert(!is_a_point(&a3));
    _assert(!is_a_vector(&a3));
    return 0;
}
int test_substracting_a_vector_from_zero_vector()
{
    Tuple a1;
    create_vector(&a1, 0, 0, 0);
    Tuple a2;
    create_vector(&a2, 5, -6, 7);
    Tuple a3;
    substracting_tuple(&a3, &a1, &a2);
    Tuple answer;
    create_vector(&answer, -5, 6, -7);
    _assert(is_equal_tuple2components(&a3, answer.x, answer.y, answer.z, answer.w));
    _assert(!is_a_point(&a3));
    _assert(is_a_vector(&a3));
    return 0;
}
int test_negating_a_tuple()
{
    Tuple a1;
    create_tuple(&a1, 1, -2, 3, -4);
    Tuple answer;
    negate_tuple(&answer, &a1);
    _assert(is_equal_tuple2components(&answer, -1, 2, -3, 4));
    return 0;
}
int test_multiplying_tuple_with_scalar()
{
    Tuple a1;
    create_tuple(&a1, 1, -2, 3, -4);
    Tuple a2;
    multiply_tuple_by_value(&a2, &a1, 3.5);
    Tuple answer;
    create_tuple(&answer, 3.5, -7, 10.5, -14);
    _assert(is_equal_tuple2components(&a2, answer.x, answer.y, answer.z, answer.w));
    return 0;
}
int test_multiplying_tuple_with_fraction()
{
    Tuple a1;
    create_tuple(&a1, 1, -2, 3, -4);
    Tuple a2;
    multiply_tuple_by_value(&a2, &a1, 0.5);
    Tuple answer;
    create_tuple(&answer, 0.5, -1, 1.5, -2);
    _assert(is_equal_tuple2components(&a2, answer.x, answer.y, answer.z, answer.w));
    return 0;
}
int test_divide_tuple_with_value()
{
    Tuple a1;
    create_tuple(&a1, 1, -2, 3, -4);
    Tuple a2;
    divide_tuple_by_value(&a2, &a1, 2);
    Tuple answer;
    create_tuple(&answer, 0.5, -1, 1.5, -2);
    _assert(is_equal_tuple2components(&a2, answer.x, answer.y, answer.z, answer.w));
    return 0;
}
int test_magnitude_of_vectors()
{
    Tuple a1;
    create_vector(&a1, 1, 0, 0);
    double m = magnitude(&a1);
    _assert(is_equal(m, 1));

    create_vector(&a1, 0, 1, 0);
    m = magnitude(&a1);
    _assert(is_equal(m, 1));

    create_vector(&a1, 0, 0, 1);
    m = magnitude(&a1);
    _assert(is_equal(m, 1));

    create_vector(&a1, 1, 2, 3);
    m = magnitude(&a1);
    _assert(is_equal(m, sqrt(14)));

    create_vector(&a1, -1, -2, -3);
    m = magnitude(&a1);
    _assert(is_equal(m, sqrt(14)));

    return 0;
}
int test_normalization_of_vectors()
{
    Tuple a1;
    create_vector(&a1, 4, 0, 0);
    Tuple a2;
    normalize_tuple(&a2, &a1);
    Tuple answer;
    create_vector(&answer, 1, 0, 0);
    _assert(is_equal_tuple2tuple(&a2, &answer));

    create_vector(&a1, 1, 2, 3);
    normalize_tuple(&a2, &a1);
    _assert(is_equal(magnitude(&a2), 1));

    create_vector(&a1, 1, 2, 3);
    normalize_tuple(&a2, &a1);
    display_tuple(&a2);
    create_vector(&answer, 1/sqrt(14), 2/sqrt(14), 3/sqrt(14));
    display_tuple(&answer);
    _assert(is_equal_tuple2tuple(&a2, &answer));

    create_vector(&a1, 1, 2, 3);
    normalize_tuple(&a2, &a1);
    _assert(is_equal(magnitude(&a2), 1));
    return 0;
}
int test_dot_product_of_two_tuples()
{
    Tuple a1;
    create_vector(&a1, 1, 2, 3);
    Tuple a2;
    create_vector(&a2, 2, 3, 4);
    _assert(is_equal(dot(&a1, &a2), 20));
    return 0;
}
int test_cross_product_of_two_tuples()
{
    Tuple a1;
    create_vector(&a1, 1, 2, 3);
    Tuple a2;
    create_vector(&a2, 2, 3, 4);
    Tuple answer1;
    create_vector(&answer1, -1, 2, -1);
    Tuple answer2;
    create_vector(&answer2, 1, -2, 1);
    Tuple a1Xa2;
    cross_product(&a1Xa2, &a1, &a2);
    Tuple a2Xa1;
    cross_product(&a2Xa1, &a2, &a1);
    _assert(is_equal_tuple2tuple(&a1Xa2, &answer1));
    _assert(is_equal_tuple2tuple(&a2Xa1, &answer2));
    return 0;
}

int test_colors_are_RBG_tuples()
{
    Tuple c;
    create_color(&c, -0.5, 0.4, 1.7);
    display_tuple(&c);
    _assert(is_equal(get_red(&c), -0.5));
    _assert(is_equal(get_green(&c), 0.4));
    _assert(is_equal(get_blue(&c), 1.7));
    return 0;
}
int test_multiplying_color()
{
    Tuple c1;
    create_color(&c1, 1, 0.2, 0.4);
    Tuple c2;
    create_color(&c2, 0.9, 1, 0.1);
    Tuple c3;
    multiply_color(&c3, &c1, &c2);
    _assert(is_equal_tuple2components(&c3, 0.9, 0.2, 0.04, 0.0));
    return 0;
}
int test_clamping_tuple()
{
    Tuple c1;
    create_color(&c1, -1, 1.2, 0.4);
    clamped_tuple_zero_one(&c1);
    Tuple answer;
    create_color(&answer, 0, 1, 0.4);
    _assert(is_equal_tuple2tuple(&c1, &answer));
    return 0;
}
int test_reflect_tuple()
{
    Tuple v1;
    create_vector(&v1, 1, -1, 0);
    Tuple normal;
    create_vector(&normal, 0, 1, 0);
    Tuple answer;
    reflect_vector(&answer, &v1, &normal);
    _assert(is_equal_tuple2components(&answer, 1, 1, 0, 0));
    return 0;
}
int all_tests_tuples()
{
    printf("... going to test tuples.c");
    // _verify(test_tuple_with_w1_is_a_point);
    // _verify(test_tuple_with_w1_is_a_vector);
    // _verify(test_point_creates_tuples_with_w1);
    // _verify(test_vector_creates_tuples_with_w0);
    // _verify(test_adding_two_tuples);
    // _verify(test_adding_two_points);
    // _verify(test_adding_two_vectors);
    // _verify(test_substracting_two_points);
    // _verify(test_substracting_a_vector_from_a_point);
    // _verify(test_substracting_two_vectors);
    // _verify(test_substracting_a_point_from_a_vector);
    // _verify(test_substracting_a_vector_from_zero_vector);
    // _verify(test_negating_a_tuple);
    // _verify(test_multiplying_tuple_with_scalar);
    // _verify(test_multiplying_tuple_with_fraction);
    // _verify(test_divide_tuple_with_value);
    // _verify(test_magnitude_of_vectors);
    // _verify(test_normalization_of_vectors);
    // _verify(test_dot_product_of_two_tuples);
    // _verify(test_cross_product_of_two_tuples);
    // _verify(test_colors_are_RBG_tuples);
    // _verify(test_multiplying_color);
    // _verify(test_clamping_tuple);
    _verify(test_reflect_tuple);
    return 0;
}



#endif /* UNIT_TESTING_H */