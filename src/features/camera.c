#ifndef CAMERA_C
#define CAMERA_C

#include <math.h>
#include "raytracer.h"



void create_camera(Camera *c, double hsize, double vsize,
                    double field_of_view_in_radians)
{
    // Camera ray_origin is (0, 0, 0)
    c->hsize = hsize;
    c->vsize = vsize;
    c->field_of_view_in_radians = field_of_view_in_radians;

    double half_view = tan(c->field_of_view_in_radians / 2);
    double aspect = c->hsize / c->vsize;

    if(aspect >= 1.0)
    {
        c->half_width = half_view;
        c->half_height = half_view / aspect;
    }
    else
    {
        c->half_width = half_view * aspect;
        c->half_height = half_view;
    }

    // default transformation = none.
    // Transformation are to be applied to the world.
    // Use view_transform() function to initialize.
    identity4d(c->transform);

    c->pixel_size = (c->half_width * 2) / c->hsize;
}



void ray_for_pixel(Ray *ray, Camera *cam, double pixel_x, double pixel_y)
{
    double x_offset = (pixel_x + 0.5) * cam->pixel_size;
    double y_offset = (pixel_y + 0.5) * cam->pixel_size;

    double world_x = cam->half_width - x_offset;
    double world_y = cam->half_height - y_offset;

    double inverse_cam_transform[16];
    invert_matrix_4x4(inverse_cam_transform, cam->transform);
    // display_matrix(inverse_cam_transform);

    Tuple pixel_coord;
    create_point(&pixel_coord, world_x, world_y, -1);
    pixel_coord = transform_tuple(inverse_cam_transform, &pixel_coord);


    Tuple ray_origin;
    create_point(&ray_origin, 0.0, 0.0, 0.0);
    ray_origin = transform_tuple(inverse_cam_transform, &ray_origin);

    Tuple ray_direction;
    substracting_tuple(&ray_direction, &pixel_coord, &ray_origin);
    normalize_tuple(&ray_direction, &ray_direction);

    create_ray(ray, &ray_origin, &ray_direction);
}



void render(Canvas *canvas, Camera *cam, World *world)
{
    *canvas = create_canvas(cam->hsize, cam->vsize);

    Ray ray;
    Tuple pixel_color;

    // For each row and column of the image
    for(int y = 0; y < cam->vsize; y++)
    {
        for(int x = 0; x < cam->hsize; x++)
        {
            create_color(&pixel_color, 0.0, 0.0, 0.0); // default black
            ray_for_pixel(&ray, cam, x, y);
            color_at(&pixel_color, world, &ray, NB_RECURSIVE_CALL);
            write_pixel(canvas, x, y, &pixel_color);
        }   /* x canvas_pixels */
    }   /* y canvas_pixels */
}


#endif /* CAMERA_C */
