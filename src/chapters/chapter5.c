#include "features/canvas.c"
#include "features/ray.c"
#include "features/tuples.c"
#include "features/light.c"
#include "features/constant.c"


void trace()
{
    // Camera and canevas
    Tuple ray_origin;
    create_point(&ray_origin, 0, 0, -5);

    double wall_z = 10;
    double wall_size = 7; //square

    double canvas_pixels = 100;
    Canvas myCanvas = create_canvas(canvas_pixels, canvas_pixels);

    double pixel_size = wall_size / canvas_pixels;
    double half = wall_size / 2;

    // scene
    Sphere mySphere;
    create_sphere(&mySphere);

    Tuple sphere_color;
    create_color(&sphere_color, 0, 0.8, 0.8);
    mySphere.material.color = sphere_color;



    Tuple pixel_color;
    Tuple eye_vector;
    Tuple normal_vector_at_hit_point;

    for(int y = 0; y < canvas_pixels; y++)
    {
        world_y = half - (pixel_size * y);

        for(int x = 0; x < canvas_pixels; x++)
        {
            world_x = (-1)*half + (pixel_size * x);

            // ray_target
            create_point(&ray_target, world_x, world_y, wall_z);
            // ray_direction
            substracting_tuple(&ray_direction, &ray_target, &ray_origin);
            // ray
            create_ray(&myRay, &ray_origin, &ray_direction);
            local_intersect_sphere(&t0, &t1, &mySphere, &myRay);

            if(t0 > EPSILON)
            {
                get_point_on_ray(&hit_point, &myRay, t0);
                normal_at_sphere(&normal_vector_at_hit_point, &mySphere, &hit_point);
                negate_tuple(&eye_vector, &(myRay.direction));

                lighting(&pixel_color, &(mySphere.material), &myLight,
                            &hit_point, &eye_vector, &normal_vector_at_hit_point);

                write_pixel(&myCanvas, x, y, &pixel_color);
            }
        }
    }
    canvas_to_ppmFile(&myCanvas);
}