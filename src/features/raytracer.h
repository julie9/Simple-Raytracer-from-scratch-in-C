#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <stdio.h>

// ------- CONSTANTS --------
#define EPSILON 0.00001
#define PI 3.141592654

typedef int boolean;
#define FALSE 0
#define TRUE 1


double pseudo_random(int index)
{
	index = (index << 13) ^ index;
	return (((index * (index * index * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0) * 0.5;
}

// ------- GLOBALS --------
boolean debug = FALSE;

// ------- TUPLE --------
typedef struct
{
    double x;
    double y;
    double z;
    double w;
} Tuple;

void create_tuple(Tuple *t, double x_input, double y_input, double z_input, double w_input);
void create_point(Tuple *t, double x_input, double y_input, double z_input);
void create_vector(Tuple *t, double x_input, double y_input, double z_input);
void create_color(Tuple *t, double red, double green, double blue);
double get_red(Tuple *t);
double get_green(Tuple *t);
double get_blue(Tuple *t);
void display_tuple(Tuple *t);
void adding_tuple(Tuple *t3, Tuple *t1, Tuple *t2);
void substracting_tuple(Tuple *t3, Tuple *t1, Tuple *t2);
void negate_tuple(Tuple *result, Tuple *t);
void negate_vector(Tuple *result, Tuple *t);
void clamped_tuple_zero_one(Tuple * t);
void multiply_tuple_by_value(Tuple *answer, Tuple *t, double value);
void divide_tuple_by_value(Tuple *answer, Tuple *t, double value);
void multiply_color(Tuple *answer, Tuple *c1, Tuple *c2);
double magnitude(Tuple *t);
void normalize_tuple(Tuple *answer, Tuple *t);
double dot(Tuple *t1, Tuple *t2);
void cross_product(Tuple *answer, Tuple *t1, Tuple *t2);
void reflect_vector(Tuple *result, Tuple *input, Tuple *normal);

boolean is_equal(double a, double b);
boolean is_equal4d(double *t, double x, double y, double z, double w);
boolean is_equal_tuple2components(Tuple *t, double x_input, double y_input, double z_input, double w_input);
boolean is_equal_tuple2tuple(Tuple *t1, Tuple *t2);
boolean is_a_point(Tuple *a);
boolean is_a_vector(Tuple *a);



// ------- MATRICES --------
boolean is_equal_matrices(double *A, double *B);
void display_matrix(double *m);
void transpose_matrix(double *matrix, double *input);
void multiply_matrices(double *output, double *A, double *B);
void transform4d(double *output, double *matrix, double x, double y, double z, double w);
// void transform_tuple(Tuple *output, double *matrix, Tuple *b);
Tuple transform_tuple(double *matrix, Tuple *b);
void identity4d(double *matrix);
void display_matrix4x4(double m[4][4]);
void invert_matrix_4x4(double * inverse1d, double * input);



// ------- TRANSFORMATION --------
void translation(double *matrix, double x, double y, double z);
void scaling(double *matrix, double x, double y, double z);
void rotation_around_xAxis(double *matrix, double rotation_in_radians);
void rotation_around_yAxis(double *matrix, double rotation_in_radians);
void rotation_around_zAxis(double *matrix, double rotation_in_radians);
void shearing(double *matrix, double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);
void view_transform(double * view_transform_matrix, Tuple view_from, Tuple view_to, Tuple view_up);



// ------- CANVAS --------

#define MAX_COLOR_VALUE 255

typedef struct
{
   int width;
   int height;
   Tuple ** pixelColor;
} Canvas;
// TODO(julie): move return value as first parameter.

void canvas_to_ppmFile(Canvas * myCanvas);
Canvas create_canvas(int n_column, int n_row);
void write_pixel(Canvas * c, int x, int y, Tuple * color);
void canvas_to_ppmFile(Canvas * myCanvas);



// ------- MATERIAL --------
typedef enum
{
    STRIPE,
    GRADIENT,
    RING,
    RADIAL_GRADIENT,
    CHECKER
} Pattern_type;

#define WORLD_REFRACTIVE_INDEX 1.0  //vacuum

typedef struct
{
    Tuple color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    double reflective;
    double transparency;    //opaque=0 transparent=1
    double refractive_index;    // index of refraction : the degree to which light will bend. vacuum=1 air=1.00029 water=1.333 glass=1.52 diamond=2.417

    // for color pattern:
    boolean has_a_pattern;
    Pattern_type type_of_pattern;
    Tuple color_a;
    Tuple color_b;
    double transform_pattern_to_object[16];
    double transform_object_to_pattern[16];

    // for a second color pattern:

} Material;

void create_material_default(Material *m);
void set_transform_pattern(Material *m, double *t);
Tuple pattern_at(Material *m, Tuple * pattern_point);



// ------- RAY --------
typedef struct
{
    Tuple origin;
    Tuple direction;
} Ray;

void create_ray(Ray *r, Tuple *origin, Tuple *direction);
void compute_position_on_ray(Tuple *position, Ray *r, double t);
void get_point_on_ray(Tuple *position, Ray *r, double t);
void transform_ray(Ray *transformed_ray, double *transformation_matrix, Ray *original_ray);



// ------- OBJECT --------
typedef enum
{
    SPHERE,
    PLANE
} Object_type;

typedef struct
{
    Object_type type_of_object;
    boolean is_casting_shadow;
    Material material;
    double* transform_object_to_world;  // array
    double* transform_world_to_object;  // array

    // for sphere:
    Tuple center;
    double radius;
} Object;

typedef struct
{
    double t;
    Object *object;
} Intersection;


void set_transform_object(Object *obj, double *t);
Object* create_sphere();
Object* create_plane();
void create_glass_sphere(Object *s);
void normal_at(Tuple *world_normal, Object *s, Tuple *world_point);
void local_normal_at_sphere(Tuple *local_normal, Object *s, Tuple *local_point);
void create_intersection(Intersection * i, double t, Object * o);
void hit(Intersection * hit, boolean * is_there_a_hit,
        Intersection * grouped_intersections, int * nb_intersections);
void intersect(Intersection * all_intersections,
                int * nb_intersections, Object *s, Ray *world_ray);
void local_intersect_sphere(Intersection * all_intersections,
                            int * nb_intersections, Object *s, Ray *local_ray);
void local_intersect_plane(Intersection * all_intersections,
                            int * nb_intersections, Object *s, Ray *local_ray);


// ------- LIGHT --------
typedef struct
{
    Tuple position;
    Tuple intensity;    // color & intensity
} Light;

void create_light(Light *l, Tuple *position, Tuple *color_intensity);
void lighting(Tuple *color_result, Object * object, Light *light,
             Tuple *point, Tuple *eye_vector, Tuple *normal_vector,
             boolean is_in_shadow);

// void lighting(Tuple *color_result, Material *material, Light *lights_array, int number_of_lights, Tuple *point, Tuple *eye_vector, Tuple *normal_vector, boolean is_in_shadow);




// ------- WORLD --------
#define MAX_N_OBJECT_WORLD 15
#define MAX_N_LIGHT_WORLD 2
#define MAX_N_INTERSECTION_RAY_OBJ 2
#define NB_INTERSECTION_PER_RAY 10

typedef struct
{
    int number_of_objects;
    int number_of_lights;
    Object* objects[MAX_N_OBJECT_WORLD];
    Light lights[MAX_N_LIGHT_WORLD];
} World;

void create_world(World * w);
void create_default_world(World *world);
void add_object(World * w, Object * object);
void add_light(World * w, Light * light);
void intersect_world_with_ray(Intersection * all_intersections, int * nb_intersections, World * w, Ray * r);
void color_at(Tuple * pixel_color, World * world, Ray * ray, int remaining_recursive_call);
void reflected_color_at(Tuple* reflected_color, World* world, Ray* reflection_ray,
                        double hitPointMaterialReflective, int remaining_recursive_call);


// ------- CAMERA --------
#define NB_RECURSIVE_CALL 5

typedef struct
{
    double hsize;
    double vsize;
    double half_width;
    double half_height;
    double pixel_size;
    double field_of_view_in_radians;
    double transform[16];
} Camera;

void create_camera(Camera *c, double hsize, double vsize, double field_of_view_in_radians);
void ray_for_pixel(Ray *ray, Camera *cam, double px, double py);
void render(Canvas *canvas, Camera *cam, World *world);

#endif /* RAYTRACER_H */