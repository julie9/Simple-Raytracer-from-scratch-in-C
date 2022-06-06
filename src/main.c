#include <stdio.h>
#include <stdlib.h> // for memory allocation functions.
#include <math.h>

#define DEBUG 0

#include "features/raytracer.h"
#include "features/camera.c"
#include "features/canvas.c"
#include "features/light.c"
#include "features/material.c"
#include "features/matrices.c"
#include "features/object.c"
#include "features/ray.c"
#include "features/raytracer.h"
#include "features/transformations.c"
#include "features/tuples.c"
#include "features/world.c"

#include "unitTesting.c"
#include "chapter11.c"

int tests_run = 0;

int main()
{
    // projectile_game();
    // trace();
#if !DEBUG
    // debug = FALSE;
    trace();


#else
    int result;

    result = all_tests_refraction();
    if(result == 0)
        printf("All tests passed - for the refraction!\n");

    // result = all_tests_reflection();
    // if(result == 0)
    //     printf("All tests passed - for the reflection!\n");

    // unit testing for tuples
    // result = all_tests_camera();
    // if(result == 0)
    //     printf("All tests passed - for the cameras!\n");

    // // unit testing for tuples
    // result = all_tests_tuples();
    // if(result == 0)
    //     printf("All tests passed - for the tuples!\n");

    // // unit testing for canvas
    // result = all_tests_canvas();
    // if(result == 0)
    //     printf("All tests passed - for the canvas!\n");

    // // unit testing for matrix
    // result = all_tests_matrices();
    // if(result == 0)
    //     printf("All tests passed - for the matrix!\n");

    // // unit testing for ray
    // result = all_tests_ray();
    // if(result == 0)
    //     printf("All tests passed - for the matrix!\n");

    // // unit testing for tuples
    // // result = all_tests_light();
    // // if(result == 0)
    // //     printf("All tests passed - for the light!\n");

    printf("Number of tests run: %d\n", tests_run);

#endif

    return 0;
}