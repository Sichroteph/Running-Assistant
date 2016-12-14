#pragma once
#include <pebble.h>



#define KEY_CUSTOM_RUN 0
#define KEY_CUSTOM_WALK 1
#define KEY_CUSTOM_REPEAT 2

// Units : seconds
uint16_t custom_run, custom_walk;
uint8_t custom_repeat;

void load_datas (void);
void save_datas (void);
