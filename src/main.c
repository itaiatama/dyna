#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WIDTH  640
#define HEIGHT 480
#define BACKGROUND 0x333333FF

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

    while(!quit) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    quit = true;
                break;
            }
        }

        SDL_SetRenderDrawColor(rend, HEX(BACKGROUND));
        SDL_RenderClear(rend);

        SDL_SetRenderDrawColor(rend, HEX(0xAA00EEFF));
        SDL_RenderFillRect(rend, &(SDL_Rect){0, 0, 64, 64});

        SDL_RenderPresent(rend);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}