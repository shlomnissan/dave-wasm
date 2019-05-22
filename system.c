//
//  system.c
//  Dave
//
//  Created by Shlomi Nissan on 4/24/19.
//  Copyright © 2019 Shlomi Nissan. All rights reserved.
//

#include "system.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    if (window == NULL | renderer == NULL) {
        return false;
    } 

    return true;
}

void destroy() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}