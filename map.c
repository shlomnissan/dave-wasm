//
//  map.c
//  Dave
//
//  Created by Shlomi Nissan on 4/28/19.
//  Copyright © 2019 Shlomi Nissan. All rights reserved.
//

#include "map.h"

#define TROPHY_POINTS 1000

GameObject game_objects[];

int map[ROWS][COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6},
    {1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 6},
    {1, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 8, 0, 0, 0, 3, 0, 0, 1, 6},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 6},
    {1, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 1, 6},
    {1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 6},
    {1, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6},
    {1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 6},
    {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 0, 0, 1, 6},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static GameObject create_game_object(SDL_Rect texture, char type, int points, bool animated) {
    GameObject obj = {};
    obj.texture = texture;
    obj.type = type;
    obj.points = points;
    obj.animated = animated;
    return obj;
}

void init_game_objects() {
    game_objects[1] = create_game_object(textures[TX_RED_BRICK], WALL, 0, false);
    game_objects[2] = create_game_object(textures[TX_PIPE], WALL, 0, false);
    game_objects[3] = create_game_object(textures[TX_BLUE_DIAMOND], LOOT, 100, false);
    game_objects[4] = create_game_object(textures[TX_RED_DIAMOND], LOOT, 150, false);
    game_objects[5] = create_game_object(textures[TX_PURPLE_GEM], LOOT, 150, false);
    game_objects[6] = create_game_object(textures[TX_WALL], NONE, 0, false);
    game_objects[7] = create_game_object(textures[TX_DOOR], NONE, 0, false);
    game_objects[8] = create_game_object(textures[TX_TROPHY_1], LOOT, TROPHY_POINTS, true);
    game_objects[8].animated_texture = (TextureSequence *)malloc(sizeof(TextureSequence));
    game_objects[8].animated_texture->frames[0] = textures[TX_TROPHY_1];
    game_objects[8].animated_texture->frames[1] = textures[TX_TROPHY_2];
    game_objects[8].animated_texture->frames[2] = textures[TX_TROPHY_3];
    game_objects[8].animated_texture->frames[3] = textures[TX_TROPHY_4];
    game_objects[8].animated_texture->frames[4] = textures[TX_TROPHY_5];
    game_objects[8].animated_texture->current_frame = 0;
    game_objects[8].animated_texture->frame_counter = 0;
    game_objects[8].animated_texture->length = 5;
    game_objects[8].animated_texture->fps = 5;
}

void draw_map() {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (map[j][i] > 0) {
                GameObject game_object = game_objects[map[j][i]];
                SDL_Rect pos = {i * TX_W, j * TX_H, TX_W, TX_H};
                if (!game_object.animated) {
                    if (j == 10) {
                        game_object.texture.h = 12;
                        pos.h = 12;
                    }
                    draw_texture(game_object.texture, pos, 0);
                } else {
                    draw_animated_texture(game_object.animated_texture, i * TX_W, j * TX_H);
                }
            }
        }
    }
}

void draw_hud() {
    SDL_Rect txt_score_pos = {0, 0, textures[TX_TXT_SCORE].w, textures[TX_TXT_SCORE].h};
    draw_texture(textures[TX_TXT_SCORE], txt_score_pos, 0);
    
    SDL_Rect txt_level_pos = {7 * TX_W + (TX_W / 2), 0, textures[TX_TXT_LEVEL].w, textures[TX_TXT_LEVEL].h};
    draw_texture(textures[TX_TXT_LEVEL], txt_level_pos, 0);
    
    SDL_Rect txt_dave_pos = {12 * TX_W, 0, textures[TX_TXT_DAVES].w, textures[TX_TXT_DAVES].h};
    draw_texture(textures[TX_TXT_DAVES], txt_dave_pos, 0);
    
    SDL_Rect tx_daves_pos = {16 * TX_W, 0, TX_W, TX_H};
    for (int i = 0; i < player.lives; i++) {
        SDL_Rect p = tx_daves_pos;
        p.x += i * TX_W;
        draw_texture(textures[TX_DAVE], p, 0);
    }
    
    if (player.has_trophy) {
        SDL_Rect txt_trophy_pos = {9 * TX_W, 6 * TX_H, textures[TX_TXT_TROPHY].w, textures[TX_TXT_TROPHY].h};
        draw_texture(textures[TX_TXT_TROPHY], txt_trophy_pos, -90.0);
    }
    
    SDL_Rect frame = {};
    int h_frame_offset = 0;
    
    for (int i = 0; i < 10; i++) {
        frame = (SDL_Rect){h_frame_offset, TX_H - 8, textures[TX_FRAME].w, textures[TX_FRAME].h};
        draw_texture(textures[TX_FRAME], frame, 0);
        
        frame = (SDL_Rect){h_frame_offset, 10 * TX_H + 14, textures[TX_FRAME].w, textures[TX_FRAME].h};
        draw_texture(textures[TX_FRAME], frame, 0);
        
        h_frame_offset += textures[TX_FRAME].w;
    }
    
    char score[6];
    sprintf(score, "%05d", player.score);
    put_text(4 * TX_W, 2, score);
    
    char level[3];
    sprintf(level, "%02d", player.level);
    put_text(11 * TX_W, 2, level);
}

bool handle_collision(SDL_Point point) {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            char v = map[j][i];
            if (v > 0) {
                GameObject obj = game_objects[v];
                SDL_Rect r = {i * TX_W, j * TX_H, 32, 32};
                if (SDL_PointInRect(&point, &r)) {
                    if (obj.type == WALL) {
                        return true;
                    }
                    if (obj.type == LOOT) {
                        player.score += obj.points;
                        map[j][i] = 0;
                        
                        if (obj.points == TROPHY_POINTS) {
                            player.has_trophy = true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
