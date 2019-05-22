//
//  player.c
//  Dave
//
//  Created by Shlomi Nissan on 4/28/19.
//  Copyright © 2019 Shlomi Nissan. All rights reserved.
//

#include "player.h"

struct Player player = {};

CollisionPoint collision_points[8];

static void calculate_colission_points(void);
static void draw_debug(void);
static void set_animation_frames(void);
static bool is_player(unsigned char);

static bool hit_left(void);
static bool hit_right(void);
static bool hit_top(void);
static bool hit_bottom(void);

const float gravity = 0.12;
const float jump_force = -3.5;
const Uint8 cp_offset = 7;
const Uint8 flicker_interval = 20;

Uint8 flicker_counter = 0;

TextureSequence walking_left = {};
TextureSequence walking_right = {};

void init_player() {
    player.pos.x = 2 * TX_W;
    player.pos.y = 9 * TX_H;
    player.lives = 3;
    player.dir = 0;
    player.velocity.x = 2;
    player.velocity.y = 0;
    player.score = 0;
    player.state |= IDLE;
    player.has_trophy = false;
    player.level = 1;
    set_animation_frames();
}

static void set_animation_frames() {
    walking_left.frames[0] = textures[TX_WALK_LEFT_1];
    walking_left.frames[1] = textures[TX_WALK_LEFT_2];
    walking_left.frames[2] = textures[TX_WALK_LEFT_3];
    walking_left.length = 3;
    walking_left.current_frame = 0;
    walking_left.frame_counter = 0;
    walking_left.fps = 12;
    
    walking_right.frames[0] = textures[TX_WALK_RIGHT_1];
    walking_right.frames[1] = textures[TX_WALK_RIGHT_2];
    walking_right.frames[2] = textures[TX_WALK_RIGHT_3];
    walking_right.length = 3;
    walking_right.current_frame = 0;
    walking_right.frame_counter = 0;
    walking_right.fps = 12;
}

void update_dave() {
    if (!hit_bottom()) {
        unset_player(GROUND);
        if (!is_player(JUMPING)) {
            set_player(FALLING);
        }
    } else {
        set_player(GROUND);
    }
    
    if (is_player(WALKING_RIGHT) && !hit_right()) {
        player.pos.x += player.velocity.x;
        player.dir = FACING_RIGHT;
        unset_player(IDLE);
    }
    
    if (is_player(WALKING_LEFT) && !hit_left()) {
        player.pos.x -= player.velocity.x;
        player.dir = FACING_LEFT;
        unset_player(IDLE);
    }
    
    if (is_player(TRY_JUMP) && is_player(GROUND) && !is_player(JUMPING)) {
        set_player(JUMPING);
        unset_player(TRY_JUMP | GROUND);
        
        if (is_player(IDLE)) {
            player.dir = FACING_RIGHT;
        }
        player.velocity.y = jump_force;
    }

    if (is_player(GROUND)) {
        if (is_player(JUMPING) || is_player(FALLING)) {
            unset_player(JUMPING | FALLING);
            player.velocity.y = 0;
            player.pos.y -= (player.pos.y % TX_H);
        }
    } else {
        if (is_player(JUMPING) || is_player(FALLING)) {
            if (player.velocity.y < 0 && hit_top()) {
                player.velocity.y = 1.5;
            }
            if (player.velocity.y > 5.0) {
                player.velocity.y = 5.0;
            } else {
                player.velocity.y += gravity;
            }
            player.pos.y += player.velocity.y;
        }
    }
    
    calculate_colission_points();
}

void draw_dave() {
    SDL_Rect player_pos = {player.pos.x, player.pos.y, TX_W, TX_H};
    
    if (player.dir == FACING_LEFT) {
        if (is_player(JUMPING) || (!is_player(JUMPING) && !is_player(GROUND) && is_player(WALKING_LEFT))) {
            draw_texture(textures[TX_JUMP_LEFT], player_pos, 0);
        }
        else if (!is_player(JUMPING) && is_player(WALKING_LEFT)) {
            draw_animated_texture(&walking_left, player.pos.x, player.pos.y);
        }
        else {
            draw_texture(textures[TX_WALK_LEFT_2], player_pos, 0);
        }
    }
    else if (player.dir == FACING_RIGHT) {
        if (is_player(JUMPING) || (!is_player(JUMPING) && !is_player(GROUND) && is_player(WALKING_RIGHT))) {
            draw_texture(textures[TX_JUMP_RIGHT], player_pos, 0);
        }
        else if (!is_player(JUMPING) && is_player(WALKING_RIGHT)) {
            draw_animated_texture(&walking_right, player.pos.x, player.pos.y);
        }
        else {
            draw_texture(textures[TX_WALK_RIGHT_2], player_pos, 0);
        }
        
    }
    else {
        flicker_counter++;
        if (flicker_counter < flicker_interval) {
            draw_texture(textures[TX_IDLE], player_pos, 0);
        }
        else if (flicker_counter > flicker_interval * 2) {
            flicker_counter = 0;
        }
    }
    if (DEBUG_GAME) {
        draw_debug();
    }
}

static bool is_player(unsigned char state) {
    return player.state & state;
}

void set_player(unsigned char state) {
    player.state = player.state | state;
}

void unset_player(unsigned char state) {
    player.state = player.state & ~state;
}

static void calculate_colission_points() {
    collision_points[CP_LEFT_TOP] = (CollisionPoint){player.pos.x + 3, player.pos.y + cp_offset};
    collision_points[CP_LEFT_BOTTOM] = (CollisionPoint){player.pos.x + 3, player.pos.y + TX_H - cp_offset};
    collision_points[CP_RIGHT_TOP] = (CollisionPoint){player.pos.x + TX_W - 3, player.pos.y + cp_offset};
    collision_points[CP_RIGHT_BOTTOM] = (CollisionPoint){player.pos.x + TX_W - 3, player.pos.y + TX_H - cp_offset};
    collision_points[CP_BOTTOM_LEFT] = (CollisionPoint){player.pos.x + cp_offset, player.pos.y + TX_H};
    collision_points[CP_BOTTOM_RIGHT] = (CollisionPoint){player.pos.x + TX_W - cp_offset, player.pos.y + TX_H};
    collision_points[CP_TOP_LEFT] = (CollisionPoint){player.pos.x + cp_offset, player.pos.y};
    collision_points[CP_TOP_RIGHT] = (CollisionPoint){player.pos.x + TX_W - cp_offset, player.pos.y};
    
    for (int i = 0; i < CP_NUM; i++) {
        if (handle_collision(collision_points[i].pos)) {
            collision_points[i].collision = true;
        } else {
            collision_points[i].collision = false;
        }
    }
}

static bool hit_left() {
    return collision_points[CP_LEFT_TOP].collision ||
           collision_points[CP_LEFT_BOTTOM].collision;
}

static bool hit_right() {
    return collision_points[CP_RIGHT_TOP].collision ||
           collision_points[CP_RIGHT_BOTTOM].collision;
}

static bool hit_top() {
    return collision_points[CP_TOP_LEFT].collision ||
           collision_points[CP_TOP_RIGHT].collision;
}

static bool hit_bottom() {
    return collision_points[CP_BOTTOM_LEFT].collision ||
           collision_points[CP_BOTTOM_RIGHT].collision;
}

static void draw_debug() {
    for (int i = 0; i < CP_NUM; i++) {
        if (collision_points[i].collision) {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x32, 0xFF);
        } else {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        }
        SDL_RenderDrawPoint(renderer, collision_points[i].pos.x, collision_points[i].pos.y);
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
}
