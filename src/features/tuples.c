#ifndef TUPLES_C
#define TUPLES_C

#include <math.h>
#include "raytracer.h"



void create_tuple(Tuple *t, double x_input, double y_input, double z_input, double w_input)
{
    t->x = x_input;
    t->y = y_input;
    t->z = z_input;
    t->w = w_input;
}

void create_point(Tuple *t, double x_input, double y_input, double z_input)
{
    create_tuple(t,
                x_input, y_input, z_input,
                1.0);
}

void create_vector(Tuple *t, double x_input, double y_input, double z_input)
{
    create_tuple(t,
                x_input, y_input, z_input,
                0.0);
}

void create_color(Tuple *t, double red, double green, double blue)
{
    create_tuple(t,
                red, green, blue,
                0.0);  // w=0, as for points.
}

double get_red(Tuple *t)
{
    return t->x;
}

double get_green(Tuple *t)
{
    return t->y;
}

double get_blue(Tuple *t)
{
    return t->z;
}

void display_tuple(Tuple *t)
{
    printf("Your tuple is:\t");
    printf("[ x, y, z, w ] = [ %f, %f, %f, %f ]\n", t->x, t->y, t->z, t->w);
}

void adding_tuple(Tuple *t3, Tuple *t1, Tuple *t2)
{
    t3->x = t1->x + t2->x;
    t3->y = t1->y + t2->y;
    t3->z = t1->z + t2->z;
    t3->w = t1->w + t2->w;
}

void substracting_tuple(Tuple *t3, Tuple *t1, Tuple *t2)
{
    t3->x = t1->x - t2->x;
    t3->y = t1->y - t2->y;
    t3->z = t1->z - t2->z;
    t3->w = t1->w - t2->w;
}

void negate_tuple(Tuple *result, Tuple *t)
{
    result->x = (-1) * t->x;
    result->y = (-1) * t->y;
    result->z = (-1) * t->z;
    result->w = (-1) * t->w;
}
void negate_vector(Tuple *result, Tuple *t)
{
    result->x = (-1) * t->x;
    result->y = (-1) * t->y;
    result->z = (-1) * t->z;
    result->w = t->w;
}

// TODO(julie): should this really by unary or it should take the output as parameters.
// unary operator that clamped every element between 0 to 1
void clamped_tuple_zero_one(Tuple * t)
{
    // x component
    if(t->x < 0)
        t->x = 0;
    else if(t->x > 1)
        t->x = 1;

    // y component
    if(t->y < 0)
        t->y = 0;
    else if(t->y > 1)
        t->y = 1;

    // z component
    if(t->z < 0)
        t->z = 0;
    else if(t->z > 1)
        t->z = 1;

    // w component
    if(t->w < 0)
        t->w = 0;
    else if(t->w > 1)
        t->w = 1;
}

void multiply_tuple_by_value(Tuple *answer, Tuple *t, double value)
{
    answer->x = t->x * value;
    answer->y = t->y * value;
    answer->z = t->z * value;
    answer->w = t->w * value;
}

void divide_tuple_by_value(Tuple *answer, Tuple *t, double value)
{
    answer->x = t->x / value;
    answer->y = t->y / value;
    answer->z = t->z / value;
    answer->w = t->w / value;
}

// element-wise product, or Hadamard product, or Schur product.
void multiply_color(Tuple *answer, Tuple *c1, Tuple *c2)
{
    answer->x = c1->x * c2->x;
    answer->y = c1->y * c2->y;
    answer->z = c1->z * c2->z;
    answer->w = 0.0;
}

double magnitude(Tuple *t)
{
    return sqrt(t->x * t->x +
                 t->y * t->y +
                 t->z * t->z +
                 t->w * t->w);
}

void normalize_tuple(Tuple *answer, Tuple *t)
{
    double mag = magnitude(t);
    if(mag < EPSILON)
    {
        printf("Warning: possible division by zero");
    }
    divide_tuple_by_value(answer, t, mag);

    // INFO: For vector, w-component = 0, so
    //       it won't be modified by the normalization.
}

double dot(Tuple *t1, Tuple *t2)
{
    if(!is_equal(0.0, t1->w) || !is_equal(0.0, t2->w))
    {
        printf("Warning: trying to perform dot product on the following",
                "tuples but dot product are for vectors only (w=0): \n");
        display_tuple(t1);
        display_tuple(t2);
        printf("\n");
    }
    return t1->x * t2->x +
           t1->y * t2->y +
           t1->z * t2->z +
           t1->w * t2->w;
}

void cross_product(Tuple *answer, Tuple *t1, Tuple *t2)
{
    create_vector(answer,
                ((t1->y * t2->z) - (t1->z * t2->y)),
         (-1) * ((t1->x * t2->z) - (t1->z * t2->x)),
                ((t1->x * t2->y) - (t1->y * t2->x))
                );
}

void reflect_vector(Tuple *result, Tuple *input, Tuple *normal)
{
    multiply_tuple_by_value(result, normal, (2)*dot(input, normal));
    substracting_tuple(result, input, result);
}

// ============================================================
//              Utilities
// ============================================================

boolean is_equal(double a, double b)
{
    // printf("%12.12f\n", fabs(a - b));
    if(fabs(a - b)  < EPSILON)
    {
        // TODO: or fabs(x-y)  <= fabs(EPSILON * y)  ... cs.yale.edu/homes/aspnes/pinewiki/C(2f) doubleingPoint.html
        return TRUE;
    }
    else
        return FALSE;
}

boolean is_equal4d(double *t, double x, double y, double z, double w)
{
    return is_equal(t[0], x) && is_equal(t[1], y) && is_equal(t[2], z) && is_equal(t[3], w);
}

boolean is_equal_tuple2components(Tuple *t, double x_input, double y_input, double z_input, double w_input)
{
    return is_equal(t->x, x_input)  &&
            is_equal(t->y, y_input)  &&
            is_equal(t->z, z_input)  &&
            is_equal(t->w, w_input);
}

boolean is_equal_tuple2tuple(Tuple *t1, Tuple *t2)
{
    return is_equal(t1->x, t2->x)  &&
            is_equal(t1->y, t2->y)  &&
            is_equal(t1->z, t2->z)  &&
            is_equal(t1->w, t2->w);
}

boolean is_a_point(Tuple *a)
{
    return is_equal(a->w, 1);
}

boolean is_a_vector(Tuple *a)
{
    return is_equal(a->w, 0);
}

#endif /* TUPLES_C */