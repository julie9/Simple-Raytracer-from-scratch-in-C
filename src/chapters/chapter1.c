#include "features/tuples.c"


struct Projectile{
    Tuple position;
    Tuple velocity;
};

struct Environment{
    Tuple gravity;
    Tuple wind;
};

int tick(struct Environment *env, struct Projectile *proj){

    proj->position = adding_tuple(&(proj->position), &(proj->velocity));
    Tuple temp = adding_tuple(&(proj->velocity), &(env->gravity));
    proj->velocity = adding_tuple(&(temp), &(env->wind));
    
    return 0;
}

int projectile_game()
{
    struct Projectile ball;
    // initial conditions:
    //  the projectile starts one unit aabove the origin.
    //  velocity is normalised to 1 unit/tick.
    ball.position = create_point(0, 1, 0);
    ball.velocity = create_vector(1, 1, 0);
    ball.velocity = normalize_tuple(&ball.velocity);

    struct Environment planet;
    planet.gravity = create_vector(0, -0.1, 0);
    planet.wind = create_vector(-0.01, 0, 0);

    int time = 0;
    while (ball.position.y >= 0)
    {
        printf("time = %d ticks\n", time++);
        display_tuple(&(ball.position));
        tick(&planet, &ball);
    }

    return 0;
}

