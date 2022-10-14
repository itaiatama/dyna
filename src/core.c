#include "core.h"

static SDL_FRect player = {0.0F, 0.0F, 32.0F, 32.0F};

float vel_x = 1;
float vel_y = 1;

void core_load(void) {
}

void core_update(float delta) {

    vel_x = vel_x > 0 ? 100 * delta : -100 * delta;
    vel_y = vel_y > 0 ? 100 * delta : -100 * delta;

    if(player.x            < 0  ) { vel_x *= -1; }
    if(player.x + player.w > 640) { vel_x *= -1; }

    if(player.y            < 0  ) { vel_y *= -1; }
    if(player.y + player.h > 480) { vel_y *= -1; }

    player.x += vel_x;
    player.y += vel_y;



}

void core_render(SDL_Renderer* render) {
    SDL_SetRenderDrawColor(render, 200, 56, 56, 255);
    //SDL_RenderFillRect(render, &player);
    SDL_RenderFillRectF(render, &player);
}

void core_destroy(void) {
}