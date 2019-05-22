//
//  player.h
//  Dave
//
//  Created by Shlomi Nissan on 4/28/19.
//  Copyright © 2019 Shlomi Nissan. All rights reserved.
//

#ifndef player_h
#define player_h

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "system.h"
#include "textures.h"
#include "map.h"

#define CP_LEFT_TOP     0
#define CP_LEFT_BOTTOM  1
#define CP_RIGHT_TOP    2
#define CP_RIGHT_BOTTOM 3
#define CP_BOTTOM_LEFT  4
#define CP_BOTTOM_RIGHT 5
#define CP_TOP_LEFT     6
#define CP_TOP_RIGHT    7
#define CP_NUM          8

#define FACING_LEFT     1
#define FACING_RIGHT    2
#define IDLE             1 << 0
#define WALKING_LEFT     1 << 1
#define WALKING_RIGHT    1 << 2
#define TRY_JUMP         1 << 3
#define JUMPING          1 << 4
#define FALLING          1 << 5
#define GROUND           1 << 6

extern struct Player {
    SDL_Point pos;
    Vector velocity;
    int score;
    unsigned char lives;
    unsigned char dir;
    unsigned char state;
    unsigned char level;
    bool has_trophy;
} player;

typedef struct {
    SDL_Point pos;
    SDL_Rect rect;
    bool collision;
} CollisionPoint;

void init_player(void);
void update_dave(void);
void draw_dave(void);
void set_player(unsigned char);
void unset_player(unsigned char);

#endif /* player_h */
