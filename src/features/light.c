#ifndef LIGHT_C
#define LIGHT_C


void create_light(Light *l, Tuple *position, Tuple *color_intensity)
{
    l->position = *position;
    l->intensity = *color_intensity;
}

// Phong Reflection Model
// INFO: See Lindley(p.135)
void lighting(Tuple *color_result, Object * object, Light *light,
             Tuple *point, Tuple *eye_vector, Tuple *normal_vector, boolean is_in_shadow)
{
    Tuple ambient_reflection;
    Tuple diffuse_reflection;
    Tuple specular_reflection;
    Tuple effective_color;
    Tuple light_vector;
    Tuple color;

    // uniform surface color or pattern
    if(TRUE == object->material.has_a_pattern)
    {
        // from world to local coordinate system:
        Tuple object_point = transform_tuple(object->transform_world_to_object,
                                            point);
        // from object to pattern coordinate
        Tuple pattern_point = transform_tuple(object->material.transform_object_to_pattern,
                                            &object_point);
        color = pattern_at(&(object->material), &pattern_point);
    }
    else
    {
        color = object->material.color;
    }
    // Combining the surface color with the light's color/intensity;
    multiply_color(&effective_color, &color, &(light->intensity));

    // light vector
    substracting_tuple(&light_vector, &(light->position), point);
    normalize_tuple(&light_vector, &light_vector);

    // ambient reflection:
    multiply_tuple_by_value(&ambient_reflection, &effective_color, object->material.ambient);

    double light_dot_normal = dot(&light_vector, normal_vector);

    // if light behind the object
    if(light_dot_normal < 0 )
    {
        create_color(&diffuse_reflection, 0, 0, 0);
        create_color(&specular_reflection, 0, 0, 0);
    }
    else if(is_in_shadow)
    {
        create_color(&diffuse_reflection, 0, 0, 0);
        create_color(&specular_reflection, 0, 0, 0);
    }
    else
    {
        // diffuse reflection
        multiply_tuple_by_value(&diffuse_reflection, &effective_color, object->material.diffuse);
        multiply_tuple_by_value(&diffuse_reflection, &diffuse_reflection, light_dot_normal);

        // specular reflection
        Tuple reflected_light_vector;
        multiply_tuple_by_value(&light_vector, &light_vector, -1.0);
        reflect_vector(&reflected_light_vector, &light_vector, normal_vector);
        double reflect_dot_eye = dot(&reflected_light_vector, eye_vector);

        if(reflect_dot_eye <= 0)
        {
            create_color(&specular_reflection, 0, 0, 0);
        }
        else
        {
            double factor = pow(reflect_dot_eye, object->material.shininess);
            multiply_tuple_by_value(&specular_reflection,
                                    &(light->intensity), object->material.specular);
            multiply_tuple_by_value(&specular_reflection, &specular_reflection, factor);
        }
    }

    adding_tuple(color_result, color_result, &ambient_reflection);
    adding_tuple(color_result, color_result, &diffuse_reflection);
    adding_tuple(color_result, color_result, &specular_reflection);
}

#endif /* LIGHT_C */