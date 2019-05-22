//
//  map.h
//  Dave
//
//  Created by Shlomi Nissan on 4/28/19.
//  Copyright © 2019 Shlomi Nissan. All rights reserved.
//

#ifndef map_h
#define map_h

#define ROWS    14
#define COLS    20

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "textures.h"
#include "player.h"
#include "font.h"

typedef struct {
    SDL_Rect texture;
    TextureSequence *animated_texture;
    char type;
    int points;
    bool animated;
} GameObject;
extern GameObject game_objects[9];

void draw_hud(void);
void draw_map(void);
void init_game_objects(void);
bool handle_collision(SDL_Point);

enum GameObjectType { WALL, LOOT, NONE };

#endif /* map_h */
