//
//  textures.h
//  Dave
//
//  Created by Shlomi Nissan on 4/28/19.
//  Copyright © 2019 Shlomi Nissan. All rights reserved.
//

#ifndef textures_h
#define textures_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TX_W    32
#define TX_H    32

#define TX_RED_BRICK        0
#define TX_DOOR             1
#define TX_WALL             2
#define TX_PIPE             3
#define TX_BLUE_DIAMOND     4
#define TX_RED_DIAMOND      5
#define TX_PURPLE_GEM       6
#define TX_TROPHY_1         7
#define TX_TROPHY_2         8
#define TX_TROPHY_3         9
#define TX_TROPHY_4         10
#define TX_TROPHY_5         11
#define TX_WALK_RIGHT_1     12
#define TX_WALK_RIGHT_2     13
#define TX_WALK_RIGHT_3     14
#define TX_JUMP_RIGHT       15
#define TX_IDLE             16
#define TX_WALK_LEFT_1      17
#define TX_WALK_LEFT_2      18
#define TX_WALK_LEFT_3      19
#define TX_JUMP_LEFT        20
#define TX_DAVE             21
#define TX_TXT_SCORE        22
#define TX_TXT_DAVES        23
#define TX_TXT_LEVEL        24
#define TX_TXT_TROPHY       25
#define TX_FRAME            26

extern SDL_Texture *spritesheet;
extern SDL_Rect textures[27];

typedef struct {
    SDL_Rect frames[10];
    unsigned char length;
    unsigned char fps;
    unsigned char current_frame;
    unsigned char frame_counter;
} TextureSequence;

void init_textures(void);
void draw_texture(SDL_Rect, SDL_Rect, double);
void draw_animated_texture(TextureSequence *, int, int);
void free_textures(void);

#endif /* textures_h */
