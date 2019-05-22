//
//  system.h
//  Dave
//
//  Created by Shlomi Nissan on 4/24/19.
//  Copyright © 2019 Shlomi Nissan. All rights reserved.
//

#ifndef system_h
#define system_h

#define FPS             60
#define MS_DELAY        1000 / FPS
#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480
#define DEBUG_GAME      0

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_TITLE "Dangerous Dave"

typedef struct {
    float x;
    float y;
} Vector;

extern SDL_Renderer *renderer;

bool init(void);
void destroy(void);

#endif /* system_h */
