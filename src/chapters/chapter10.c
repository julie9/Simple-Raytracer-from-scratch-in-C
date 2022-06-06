
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
    sphere1.material.shininess = 10;

    add_object(&world, &sphere1);


    Object sphere2;
    create_sphere(&sphere2);
    // Tuple color;
    create_color(&color, 0.1, 0, 0.9);
    sphere2.material.color = color;
    double B[16];
    scaling(B, 0.8, 0.8, 0.8);
    set_transform_object(&sphere2, B);
    // Tuple color_a1;
    // create_color(&color_a1, 0.1, 0, 0.9);
    // sphere2.material.color_a = color_a1;
    // double C[16];
    // scaling(C, 0.1, 0.1, 0.1);
    // set_transform_pattern(&(sphere2.material), C);
    // sphere2.material.has_a_pattern = TRUE;
    // sphere2.material.type_of_pattern = STRIPE;
    add_object(&world, &sphere2);

    Object floor;
    create_plane(&floor);
    Tuple color_a;
    create_color(&color_a, 0.1, 0.1, 0.1);
    floor.material.color_a = color_a;
    floor.material.has_a_pattern = TRUE;
    floor.material.type_of_pattern = CHECKER;
    floor.material.reflective = 0.5;

    add_object(&world, &floor);

    printf("nb of objects in your world : %d\n", world.number_of_objects);

    // -----
    // Light
    // -----
    Tuple light_position;
    Tuple light_color_intensity;

    Light myLight;
    create_point(&light_position, -10, 5, -10);
    create_color(&light_color_intensity, .5, .5, .5);
    create_light(&myLight, &light_position, &light_color_intensity);
    add_light(&world, &myLight);

    Light mySecondLight;
    create_point(&light_position, 2, 3, -2);
    create_color(&light_color_intensity, .5, .5, .5);
    create_light(&mySecondLight, &light_position, &light_color_intensity);
    add_light(&world, &mySecondLight);

    printf("nb of lights : %d\n", world.number_of_lights);

    // Camera and canvas
    Canvas myCanvas;

    Camera cam;
    int s = 2;
    create_camera(&cam, 500*s, 250*s, PI/3);

    Tuple from;
    create_point(&from, -8, 5, -10);
    Tuple to;
    create_point(&to, 0, 1, 0);
    Tuple up;
    create_vector(&up, 0, 1, 0);
    view_transform(cam.transform, from, to, up);


    // Render
    render(&myCanvas, &cam, &world);
    canvas_to_ppmFile(&myCanvas);

}