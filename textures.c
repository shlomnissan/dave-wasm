//
//  textures.c
//  Dave
//
//  Created by Shlomi Nissan on 4/28/19.
//  Copyright © 2019 Shlomi Nissan. All rights reserved.
//

#include "textures.h"
#include "system.h"

SDL_Texture *spritesheet = NULL;
SDL_Rect textures[];

void init_textures() {
    SDL_Surface *surface = IMG_Load("assets/sprites.png");
    if (!surface) {
        printf("%s\n", IMG_GetError());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
    spritesheet = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    textures[TX_RED_BRICK] =        (SDL_Rect){0 * TX_W, 0 * TX_H, TX_W, TX_H};
    textures[TX_DOOR] =             (SDL_Rect){1 * TX_W, 0 * TX_H, TX_W, TX_H};
    textures[TX_WALL] =             (SDL_Rect){2 * TX_W, 0 * TX_H, TX_W, TX_H};
    textures[TX_PIPE] =             (SDL_Rect){0 * TX_W, 1 * TX_H, TX_W, TX_H};
    textures[TX_BLUE_DIAMOND] =     (SDL_Rect){1 * TX_W, 1 * TX_H, TX_W, TX_H};
    textures[TX_RED_DIAMOND] =      (SDL_Rect){2 * TX_W, 1 * TX_H, TX_W, TX_H};
    textures[TX_PURPLE_GEM] =       (SDL_Rect){3 * TX_W, 1 * TX_H, TX_W, TX_H};
    textures[TX_TROPHY_1] =         (SDL_Rect){0 * TX_W, 2 * TX_H, TX_W, TX_H};
    textures[TX_TROPHY_2] =         (SDL_Rect){1 * TX_W, 2 * TX_H, TX_W, TX_H};
    textures[TX_TROPHY_3] =         (SDL_Rect){2 * TX_W, 2 * TX_H, TX_W, TX_H};
    textures[TX_TROPHY_4] =         (SDL_Rect){3 * TX_W, 2 * TX_H, TX_W, TX_H};
    textures[TX_TROPHY_5] =         (SDL_Rect){4 * TX_W, 2 * TX_H, TX_W, TX_H};
    textures[TX_IDLE] =             (SDL_Rect){4 * TX_W, 3 * TX_H, TX_W, TX_H};
    textures[TX_WALK_RIGHT_1] =     (SDL_Rect){0 * TX_W, 3 * TX_H, TX_W, TX_H};
    textures[TX_WALK_RIGHT_2] =     (SDL_Rect){1 * TX_W, 3 * TX_H, TX_W, TX_H};
    textures[TX_WALK_RIGHT_3] =     (SDL_Rect){2 * TX_W, 3 * TX_H, TX_W, TX_H};
    textures[TX_WALK_LEFT_1] =      (SDL_Rect){0 * TX_W, 4 * TX_H, TX_W, TX_H};
    textures[TX_WALK_LEFT_2] =      (SDL_Rect){1 * TX_W, 4 * TX_H, TX_W, TX_H};
    textures[TX_WALK_LEFT_3] =      (SDL_Rect){2 * TX_W, 4 * TX_H, TX_W, TX_H};
    textures[TX_JUMP_RIGHT] =       (SDL_Rect){3 * TX_W, 3 * TX_H, TX_W, TX_H};
    textures[TX_JUMP_LEFT] =        (SDL_Rect){3 * TX_W, 4 * TX_H, TX_W, TX_H};
    textures[TX_DAVE] =             (SDL_Rect){4 * TX_W, 4 * TX_H, TX_W, TX_H};
    textures[TX_TXT_SCORE] =        (SDL_Rect){0 * TX_W, 7 * TX_H, 4 * TX_W, TX_H};
    textures[TX_TXT_DAVES] =        (SDL_Rect){0 * TX_W, 6 * TX_H, 4 * TX_W, TX_H};
    textures[TX_TXT_LEVEL] =        (SDL_Rect){0 * TX_W, 8 * TX_H, 3 * TX_W, TX_H};
    textures[TX_TXT_TROPHY] =       (SDL_Rect){5 * TX_W, 0 * TX_H, TX_W, 11 * TX_H};
    textures[TX_FRAME] =            (SDL_Rect){0 * TX_W, 5 * TX_H, 2 * TX_W, 4};
}

void draw_texture(SDL_Rect tx_frame, SDL_Rect tx_pos, double angle) {
    SDL_RenderCopyEx(renderer, spritesheet, &tx_frame, &tx_pos, angle, NULL, SDL_FLIP_NONE);
}

void draw_animated_texture(TextureSequence *texture, int x, int y) {
    texture->frame_counter++;
    if (FPS / texture->frame_counter == texture->fps) {
        texture->current_frame += 1;
        texture->frame_counter = 0;
        if (texture->current_frame > texture->length - 1) {
            texture->current_frame = 0;
        }
    }
    SDL_Rect pos = {x, y, TX_W, TX_H};
    draw_texture(texture->frames[texture->current_frame], pos, 0);
}

void free_textures() {
    SDL_DestroyTexture(spritesheet);
}
