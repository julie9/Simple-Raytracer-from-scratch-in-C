
#if 1
// POND WITH WATER AND ROCKS
void trace()
{
    // -----
    // Default world
    // -----
    World world;
    create_world(&world);
    // create_default_world(&world);

    Object* water = create_plane(water);
    water->is_casting_shadow = 0;
    water->material.transparency = 0.75;
    water->material.refractive_index = 1.2;
    Tuple water_color;
    create_color(&water_color, 0, 0.15, 0.1);
    water->material.color = water_color;
    add_object(&world, water);

    Object* floor = create_plane(floor);
    double t_floor[16];
    translation(t_floor, 0, -3, 0);
    set_transform_object(floor, t_floor);
    add_object(&world, floor);

    double A[16];
    Tuple color;
    Object* sphere1;
    for (int i = 0; i < 10; i++ )
    {
        sphere1 = create_sphere();

        create_color(&color, (double)(rand() % 100)/100,
                             (double)(rand() % 100)/100,
                             (double)(rand() % 100)/100);
        sphere1->material.color = color;
        translation(A, (rand() % 10) ,
                        -2, //+ ((rand() % 100)/100),
                        (rand() % 10) );
        set_transform_object(sphere1, A);
        add_object(&world, sphere1);
    }


    printf("nb of objects in your world : %d\n", world.number_of_objects);

    // -----
    // Light
    // -----
    Tuple light_position;
    Tuple light_color_intensity;

    Light myLight;
    create_point(&light_position, -10, 5, -5);
    create_color(&light_color_intensity, 0.5, 0.5, 0.5);
    create_light(&myLight, &light_position, &light_color_intensity);
    add_light(&world, &myLight);

    // Light mySecondLight;
    // create_point(&light_position, 3, 5, 0);
    // create_color(&light_color_intensity, 0.1, 0.1, 0.1);
    // create_light(&mySecondLight, &light_position, &light_color_intensity);
    // add_light(&world, &mySecondLight);

    printf("nb of lights : %d\n", world.number_of_lights);


    // Canvas and Camera
    Canvas myCanvas;
    Camera cam;
    int s = 100;
    create_camera(&cam, 5*s, 5*s, PI/3);

    Tuple from;
    create_point(&from, -4, 4, 1);
    Tuple to;
    create_point(&to, 5, -2, 5);
    Tuple up;
    create_vector(&up, 0, 1, 0);
    view_transform(cam.transform, from, to, up);

    // Render
    render(&myCanvas, &cam, &world);
    canvas_to_ppmFile(&myCanvas);

}
#endif


#if 0

void trace()
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
    translation(A, -1, 1, 1);
    set_transform_object(&sphere1, A);
    add_object(&world, &sphere1);

    Object sphere2;
    create_sphere(&sphere2);
    // Tuple color;
    create_color(&color, 0, 0.2, 0.1);
    sphere2.material.color = color;
    sphere2.material.transparency = 0.9;
    sphere2.material.refractive_index = 1.005;
    sphere2.material.reflective = 1;
    sphere2.material.diffuse = 0.4;
    sphere2.material.shininess = 400;
    double B[16];
    scaling(B, 0.8, 0.8, 0.8);
    set_transform_object(&sphere2, B);
    add_object(&world, &sphere2);

    Object floor;
    create_plane(&floor);
    add_object(&world, &floor);

    printf("nb of objects in your world : %d\n", world.number_of_objects);

    // -----
    // Light
    // -----
    Tuple light_position;
    Tuple light_color_intensity;

    Light myLight;
    create_point(&light_position, -10, 5, -10);
    create_color(&light_color_intensity, 1, 1, 1);
    create_light(&myLight, &light_position, &light_color_intensity);
    add_light(&world, &myLight);

    Light mySecondLight;
    create_point(&light_position, 3, 5, 0);
    create_color(&light_color_intensity, 0.1, 0.1, 0.1);
    create_light(&mySecondLight, &light_position, &light_color_intensity);
    add_light(&world, &mySecondLight);

    printf("nb of lights : %d\n", world.number_of_lights);


    // Canvas and Camera
    Canvas myCanvas;

    Camera cam;
    int s = 1;
    create_camera(&cam, 500*s, 250*s, PI/3);

    Tuple from;
    create_point(&from, 0, 2, -5);
    Tuple to;
    create_point(&to, 0, 1, 0);
    Tuple up;
    create_vector(&up, 0, 1, 0);
    view_transform(cam.transform, from, to, up);

    // Render
    render(&myCanvas, &cam, &world);
    canvas_to_ppmFile(&myCanvas);

}
#endif

#if 0
void trace()
{
    World world;
    create_default_world(&world);

    world.objects[0]->material.ambient = 1.0;
    world.objects[1]->material.transparency = 1.0;
    world.objects[1]->material.refractive_index= 1.5;

    // TEST #20

    Object floor;
    create_plane(&floor);
    double f1[16];
    translation(f1, 0, -1, 0);
    set_transform_object(&floor, f1);
    floor.material.reflective = 1;
    floor.material.transparency = 0.5;
    floor.material.refractive_index = 1.5;
    add_object(&world, &floor);

    Object ball;
    create_sphere(&ball);
    Tuple color_ball;
    create_color(&color_ball, 1, 0, 0);
    ball.material.color = color_ball;
    ball.material.ambient = 0.5;
    double b1[16];
    translation(b1, 0, -3.5, -2);
    set_transform_object(&ball, b1);
    add_object(&world, &ball);


    // Canvas and Camera
    Canvas myCanvas;
    Camera cam;
    int s = 2;
    create_camera(&cam, 200*s, 200*s, PI/3);

    Tuple origin_test;
    create_point(&origin_test, 0, 0, -3.0);
    Tuple direction_test;
    create_vector(&direction_test, 0, -sqrt(2)/2, sqrt(2)/2);
    Ray ray_test;
    create_ray(&ray_test, &origin_test, &direction_test);


    Tuple from;
    create_point(&from, 0, 0, -3);
    Tuple to;
    create_point(&to, 0, -sqrt(2)/2, -3 + sqrt(2)/2);
    Tuple up;
    create_vector(&up, 0, 1, 0);
    view_transform(cam.transform, origin_test, to, up);


    // Render
    render(&myCanvas, &cam, &world);
    canvas_to_ppmFile(&myCanvas);

}
#endif
