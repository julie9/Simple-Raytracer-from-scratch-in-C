#ifndef TRANSFORMATIONS_C
#define TRANSFORMATIONS_C

#include <math.h>

void translation(double *matrix, double x, double y, double z)
{
    matrix[0] = 1;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = x;

    matrix[4] = 0;
    matrix[5] = 1;
    matrix[6] = 0;
    matrix[7] = y;

    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = 1;
    matrix[11] = z;

    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

void scaling(double *matrix, double x, double y, double z)
{
    matrix[0] = x;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;

    matrix[4] = 0;
    matrix[5] = y;
    matrix[6] = 0;
    matrix[7] = 0;

    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = z;
    matrix[11] = 0;

    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

void rotation_around_xAxis(double *matrix, double rotation_in_radians)
{
    matrix[0] = 1;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;

    matrix[4] = 0;
    matrix[5] = cos(rotation_in_radians);
    matrix[6] = (-1)*sin(rotation_in_radians);
    matrix[7] = 0;

    matrix[8] = 0;
    matrix[9] = sin(rotation_in_radians);
    matrix[10] = cos(rotation_in_radians);
    matrix[11] = 0;

    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

void rotation_around_yAxis(double *matrix, double rotation_in_radians)
{
    matrix[0] = cos(rotation_in_radians);
    matrix[1] = 0;
    matrix[2] = sin(rotation_in_radians);
    matrix[3] = 0;

    matrix[4] = 0;
    matrix[5] = 1;
    matrix[6] = 0;
    matrix[7] = 0;

    matrix[8] = (-1)*sin(rotation_in_radians);
    matrix[9] = 0;
    matrix[10] = cos(rotation_in_radians);
    matrix[11] = 0;

    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

void rotation_around_zAxis(double *matrix, double rotation_in_radians)
{
    matrix[0] = cos(rotation_in_radians);
    matrix[1] = (-1)*sin(rotation_in_radians);
    matrix[2] = 0;
    matrix[3] = 0;

    matrix[4] = sin(rotation_in_radians);
    matrix[5] = cos(rotation_in_radians);
    matrix[6] = 0;
    matrix[7] = 0;

    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = 1;
    matrix[11] = 0;

    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

void shearing(double *matrix, double x_y, double x_z,
                            double y_x, double y_z,
                            double z_x, double z_y)
{
    // where x_y means "x moved in proportion to y", etc.

    matrix[0] = 1;
    matrix[1] = x_y;
    matrix[2] = x_z;
    matrix[3] = 0;

    matrix[4] = y_x;
    matrix[5] = 1;
    matrix[6] = y_z;
    matrix[7] = 0;

    matrix[8] = z_x;
    matrix[9] = z_y;
    matrix[10] = 1;
    matrix[11] = 0;

    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

void view_transform(double * view_transform_matrix,
                    Tuple view_from, Tuple view_to, Tuple view_up)
{
    // Info: the vector up does not need to be 90deg with forward.
    Tuple forward;
    Tuple left;
    Tuple true_up;

    substracting_tuple(&forward, &view_to, &view_from);
    normalize_tuple(&forward, &forward);
    // printf("forward:\n");
    // display_tuple(&forward);

    normalize_tuple(&view_up, &view_up);
    // printf("view_up:\n");
    // display_tuple(&view_up);

    cross_product(&left, &forward, &view_up);
    cross_product(&true_up, &left, &forward);

    double orientation[16] = {
                    left.x,             left.y,             left.z,             0.0,
                    true_up.x,          true_up.y,          true_up.z,          0.0,
                    ((-1)  * forward.x), ((-1) * forward.y), ((-1) * forward.z), 0.0,
                    0.0,                0.0,                0.0,                1.0};
    // printf("orientation:\n");
    // display_matrix(orientation);

    double t[16];
    translation(t, ((-1) * view_from.x), ((-1) * view_from.y), ((-1) * view_from.z));
    // printf("t:\n");
    // display_matrix(t);

    multiply_matrices(view_transform_matrix, orientation, t);
    // printf("view_transform_matrix:\n");
    // display_matrix(view_transform_matrix);
}

#endif /* TRANSFORMATIONS_C */