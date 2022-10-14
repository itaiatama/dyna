#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "fc.h"
#include "core.h"

#define WIDTH  640
#define HEIGHT 480
#define BACKGROUND 0x333333FF
#define TARGET_FPS 60

#define TARGET_FRAME_TIME (1.0F / TARGET_FPS * 1000.0F)

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define HEX(c)               \
        ((c >> (8 * 3)) & 0xFF), \
        ((c >> (8 * 2)) & 0xFF), \
        ((c >> (8 * 1)) & 0xFF), \
        ((c >> (8 * 0)) & 0xFF)  
#endif
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #define HEX(c)               \
        ((c >> (8 * 0)) & 0xFF), \
        ((c >> (8 * 1)) & 0xFF), \
        ((c >> (8 * 2)) & 0xFF), \
        ((c >> (8 * 3)) & 0xFF)  
#endif

int main(void) {

    if(SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL Error: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Window* win = SDL_CreateWindow(
        "DY:NA",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if(!win) {
        fprintf(stderr, "[ERROR]: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* rend = SDL_CreateRenderer(
        win,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if(!rend) {
        fprintf(stderr, "[ERROR]: %s", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return -1;
    }


    bool quit = false;
    FrameCounter frames = {0};
    float delta = 0.0F;

    core_load();

    while(!quit) {

        uint64_t start = SDL_GetTicks64();

        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    quit = true;
                break;

                case SDL_KEYDOWN:
                break;
                case SDL_KEYUP:
                break;
            }
        }

        core_update(delta);

        SDL_SetRenderDrawColor(rend, HEX(BACKGROUND));
        SDL_RenderClear(rend);

        core_render(rend);

        SDL_RenderPresent(rend);
        int64_t await = TARGET_FRAME_TIME - (SDL_GetTicks64() - start);
        
        if(await > 0) {
            SDL_Delay(await);
        }

        int64_t frame_time = SDL_GetTicks64() - start;
        delta = ((float) frame_time / 1000.0F);

        fc_sync(&frames, delta);
        fc_print(&frames);
    }

    core_destroy();

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}