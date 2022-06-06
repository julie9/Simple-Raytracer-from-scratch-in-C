#include "features/tuples.c"
#include "features/canvas.c"

struct Projectile{
    Tuple position;
    Tuple velocity;
};

struct Environment{
    Tuple gravity;
    Tuple wind;
};

int tick(struct Environment *env, struct Projectile *proj){

    adding_tuple(&(proj->position),
                    &(proj->position), &(proj->velocity));
    Tuple temp;
    adding_tuple(&(temp),
                    &(proj->velocity), &(env->gravity));
    adding_tuple(&(proj->velocity),
                    &(temp), &(env->wind));

    return 0;
}

int projectile_game()
{
    struct Projectile ball;
    // initial conditions:
    //  the projectile starts one unit aabove the origin.
    //  velocity is normalised to 1 unit/tick.
    create_point(&(ball.position), 0, 1, 0);
    create_vector(&(ball.velocity), 1, 1.8, 0);
    normalize_tuple(&ball.velocity, &ball.velocity);
    // ball.velocity = multiply_tuple_by_value(&ball.velocity, 5);
    display_tuple(&ball.velocity);

    struct Environment planet;
    create_vector(&planet.gravity, 0, -0.1, 0);
    create_vector(&planet.wind, -0.01, 0, 0);

    Canvas myCanvas = create_canvas(25, 70);
    Tuple red;
    create_color(&red, 1, 0, 0);

    int time = 0;
    while (ball.position.y >= 0)
    {
        printf("time = %d ticks\n", time++);
        display_tuple(&(ball.position));
        write_pixel(&myCanvas, ball.position.x, myCanvas.height - ball.position.y , &red);
        tick(&planet, &ball);
    }
    canvas_to_ppmFile(&myCanvas);
    printf("done");

    return 0;
}

