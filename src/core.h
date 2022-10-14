#ifndef  DYNA_CORE_H
#define  DYNA_CORE_H

#include <SDL2/SDL.h>

void core_load(void);
void core_update(float delta);
void core_render(SDL_Renderer* render);
void core_destroy(void);

#endif //DYNA_CORE_H