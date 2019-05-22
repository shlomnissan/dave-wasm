//
//  font.c
//  Dave
//
//  Created by Shlomi Nissan on 5/19/19.
//  Copyright © 2019 Shlomi Nissan. All rights reserved.
//

#include "font.h"

SDL_Rect chars[10];

void init_font() {
    int h_offset = 0;
    int v_offset = 9 * TX_H;
    int char_width = TX_W / 2;
    int char_height = 20;
    
    for (int i = 0; i < 10; i++) {
        chars[i] = (SDL_Rect){h_offset, v_offset, char_width, char_height};
        h_offset += char_width;
    }
}

void put_text(int x, int y, char *str) {
    unsigned long len = strlen(str);
    int h_offset = x;
    
    for (int i = 0; i < len; i++) {
        char c = str[i] - '0';
        draw_texture(chars[c], (SDL_Rect){h_offset, y, chars[0].w, chars[0].h}, 0);
        h_offset += chars[c].w;
    }
    
}
