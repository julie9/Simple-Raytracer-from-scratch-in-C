#ifndef MATERIAL_C
#define MATERIAL_C



void create_material_default(Material *m)
{
    create_color(&(m->color), 1, 1, 1);
    m->ambient = 0.1;
    m->diffuse = 0.9;
    m->specular = 0.9;
    m->shininess = 200.0;
    m->reflective = 0.0;
    m->transparency = 0.0;
    m->refractive_index = 1.0;

    // for pattern:
    boolean has_a_pattern = FALSE;
    m->color_a = m->color;
    m->color_b = m->color;
    identity4d(m->transform_pattern_to_object);
    identity4d(m->transform_object_to_pattern);
}



void set_transform_pattern(Material *m, double *t)
{
    for(int i= 0; i < 16; i++)
    {
        m->transform_pattern_to_object[i] = t[i];
    }

    invert_matrix_4x4(m->transform_object_to_pattern,
                        m->transform_pattern_to_object);
}



Tuple pattern_at(Material *m, Tuple * pattern_point)
{
    Tuple color;

    if(STRIPE == m->type_of_pattern)
    {
        if(0 == ((int) floor(pattern_point->x) % 2))
        {
            color = m->color_a;
        }
        else
        {
            color = m->color_b;
        }
    }

    else if(GRADIENT == m->type_of_pattern)
    {
        Tuple distance_color;
        substracting_tuple(&distance_color, &(m->color_b), &(m->color_a));

        double fractional_x = pattern_point->x - floor(pattern_point->x);

        Tuple temp;
        multiply_tuple_by_value(&temp, &distance_color, fractional_x);

        adding_tuple(&color, &(m->color_a), &temp);
    }

    else if(RING == m->type_of_pattern)
    {
        if(0 == ((int) floor(sqrt(
                    (pattern_point->x * pattern_point->x) +
                    (pattern_point->z * pattern_point->z)
                    )) % 2))
        {
            color = m->color_a;
        }
        else
        {
            color = m->color_b;
        }
    }

    else if(RADIAL_GRADIENT == m->type_of_pattern)
    {
        Tuple distance_color;
        substracting_tuple(&distance_color, &(m->color_b), &(m->color_a));

        double radius = sqrt((pattern_point->x * pattern_point->x) +
                             (pattern_point->z * pattern_point->z));
        double fractional_radius = radius - floor(radius);

        Tuple temp;
        multiply_tuple_by_value(&temp, &distance_color, fractional_radius);

        adding_tuple(&color, &(m->color_a), &temp);
    }

    else if(CHECKER == m->type_of_pattern)
    {
        if(0 == ((int) (floor(pattern_point->x)
                    + floor(pattern_point->y)
                    + floor(pattern_point->z)) % 2))
        {
            color = m->color_a;
        }
        else
        {
            color = m->color_b;
        }
    }
    return color;
}


#endif /* MATERIAL_C */