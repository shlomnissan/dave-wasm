//
//  main.c
//  Dave
//
//  Created by Shlomi Nissan on 4/20/19.
//  Copyright © 2019 Shlomi Nissan. All rights reserved.
//

#include <emscripten.h>
#include "system.h"
#include "map.h"
#include "player.h"

bool running = true;

void handle_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_KEYDOWN) {
            switch( event.key.keysym.sym ){
                case SDLK_LEFT:
                    set_player(WALKING_LEFT);
                    break;
                case SDLK_RIGHT:
                    set_player(WALKING_RIGHT);
                    break;
                case SDLK_UP:
                    set_player(TRY_JUMP);
                    break;
            }
        }
        if (event.type == SDL_KEYUP) {
            switch( event.key.keysym.sym ){
                case SDLK_LEFT:
                    unset_player(WALKING_LEFT);
                    break;
                case SDLK_RIGHT:
                    unset_player(WALKING_RIGHT);
                    break;
                case SDLK_UP:
                    unset_player(TRY_JUMP);
                    break;
            }
        }
    }
}

void update() {
    update_dave();
}

void draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    draw_hud();
    draw_map();
    draw_dave();
    
    SDL_RenderPresent(renderer);
}

void mainLoop() {
    handle_input();
    update();
    draw();
}

int main(int argc, const char * argv[]) {
    if (!init()) {
        return 1;
    }
    
    init_textures();
    init_font();
    init_player();
    init_game_objects();
    
    emscripten_set_main_loop(mainLoop, -1, 1);
    
    free_textures();
    destroy();
    return 0;
}
