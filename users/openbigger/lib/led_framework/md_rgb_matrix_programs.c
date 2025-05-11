/*
Copyright 2018 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "md_rgb_matrix.h"

// Teal <-> Salmon
led_setup_t leds_teal_salmon[] = {
    {.hs = 0, .he = 33, .rs = 24, .re = 24, .gs = 215, .ge = 215, .bs = 204, .be = 204, .ef = EF_NONE},
    {.hs = 33, .he = 66, .rs = 24, .re = 255, .gs = 215, .ge = 114, .bs = 204, .be = 118, .ef = EF_NONE},
    {.hs = 66, .he = 100, .rs = 255, .re = 255, .gs = 114, .ge = 114, .bs = 118, .be = 118, .ef = EF_NONE},
    {.end = 1},
};

// Yellow
led_setup_t leds_yellow[] = {
    {.hs = 0, .he = 100, .rs = 255, .re = 255, .gs = 255, .ge = 255, .bs = 0, .be = 0, .ef = EF_NONE},
    {.end = 1},
};

// Off
led_setup_t leds_off[] = {
    {.hs = 0, .he = 100, .rs = 0, .re = 0, .gs = 0, .ge = 0, .bs = 0, .be = 0, .ef = EF_NONE},
    {.end = 1},
};

// Red
led_setup_t leds_red[] = {
    {.hs = 0, .he = 100, .rs = 255, .re = 255, .gs = 0, .ge = 0, .bs = 0, .be = 0, .ef = EF_NONE},
    {.end = 1},
};

// Green
led_setup_t leds_green[] = {
    {.hs = 0, .he = 100, .rs = 0, .re = 0, .gs = 255, .ge = 255, .bs = 0, .be = 0, .ef = EF_NONE},
    {.end = 1},
};

// Blue
led_setup_t leds_blue[] = {
    {.hs = 0, .he = 100, .rs = 0, .re = 0, .gs = 0, .ge = 0, .bs = 255, .be = 255, .ef = EF_NONE},
    {.end = 1},
};

// White
led_setup_t leds_white[] = {
    {.hs = 0, .he = 100, .rs = 255, .re = 255, .gs = 255, .ge = 255, .bs = 255, .be = 255, .ef = EF_NONE},
    {.end = 1},
};

// White with moving red stripe
led_setup_t leds_white_with_red_stripe[] = {
    {.hs = 0, .he = 100, .rs = 255, .re = 255, .gs = 255, .ge = 255, .bs = 255, .be = 255, .ef = EF_NONE},
    {.hs = 0, .he = 15, .rs = 0, .re = 0, .gs = 0, .ge = 255, .bs = 0, .be = 255, .ef = EF_SCR_R | EF_SUBTRACT},
    {.hs = 15, .he = 30, .rs = 0, .re = 0, .gs = 255, .ge = 0, .bs = 255, .be = 0, .ef = EF_SCR_R | EF_SUBTRACT},
    {.end = 1},
};

// Black with moving red stripe
led_setup_t leds_black_with_red_stripe[] = {
    {.hs = 0, .he = 15, .rs = 0, .re = 255, .gs = 0, .ge = 0, .bs = 0, .be = 0, .ef = EF_SCR_R},
    {.hs = 15, .he = 30, .rs = 255, .re = 0, .gs = 0, .ge = 0, .bs = 0, .be = 0, .ef = EF_SCR_R},
    {.end = 1},
};

// Rainbow no scrolling
led_setup_t leds_rainbow_ns[] = {
    {.hs = 0, .he = 16.67, .rs = 255, .re = 255, .gs = 0, .ge = 255, .bs = 0, .be = 0, .ef = EF_OVER}, {.hs = 16.67, .he = 33.33, .rs = 255, .re = 0, .gs = 255, .ge = 255, .bs = 0, .be = 0, .ef = EF_OVER}, {.hs = 33.33, .he = 50, .rs = 0, .re = 0, .gs = 255, .ge = 255, .bs = 0, .be = 255, .ef = EF_OVER}, {.hs = 50, .he = 66.67, .rs = 0, .re = 0, .gs = 255, .ge = 0, .bs = 255, .be = 255, .ef = EF_OVER}, {.hs = 66.67, .he = 83.33, .rs = 0, .re = 255, .gs = 0, .ge = 0, .bs = 255, .be = 255, .ef = EF_OVER}, {.hs = 83.33, .he = 100, .rs = 255, .re = 255, .gs = 0, .ge = 0, .bs = 255, .be = 0, .ef = EF_OVER}, {.end = 1},
};

// Rainbow scrolling
led_setup_t leds_rainbow_s[] = {
    {.hs = 0, .he = 16.67, .rs = 255, .re = 255, .gs = 0, .ge = 255, .bs = 0, .be = 0, .ef = EF_OVER | EF_SCR_R}, {.hs = 16.67, .he = 33.33, .rs = 255, .re = 0, .gs = 255, .ge = 255, .bs = 0, .be = 0, .ef = EF_OVER | EF_SCR_R}, {.hs = 33.33, .he = 50, .rs = 0, .re = 0, .gs = 255, .ge = 255, .bs = 0, .be = 255, .ef = EF_OVER | EF_SCR_R}, {.hs = 50, .he = 66.67, .rs = 0, .re = 0, .gs = 255, .ge = 0, .bs = 255, .be = 255, .ef = EF_OVER | EF_SCR_R}, {.hs = 66.67, .he = 83.33, .rs = 0, .re = 255, .gs = 0, .ge = 0, .bs = 255, .be = 255, .ef = EF_OVER | EF_SCR_R}, {.hs = 83.33, .he = 100, .rs = 255, .re = 255, .gs = 0, .ge = 0, .bs = 255, .be = 0, .ef = EF_OVER | EF_SCR_R}, {.end = 1},
};

// Add new LED animations here using one from above as example
// The last entry must be { .end = 1 }
led_setup_t leds_pink[] = {
    {.hs = 0, .he = 100, .rs = 255, .re = 255, .gs = 20, .ge = 20, .bs = 147, .be = 147, .ef = EF_NONE},
    {.end = 1},
};
led_setup_t leds_move_ring[] = {
    {.hs = 0, .he = 100, .rs = 250, .re = 250, .gs = 17, .ge = 17, .bs = 79, .be = 79, .ef = EF_NONE},
    {.end = 1},
};
led_setup_t leds_exercise_ring[] = {
    {.hs = 0, .he = 100, .rs = 166, .re = 166, .gs = 255, .ge = 255, .bs = 0, .be = 0, .ef = EF_NONE},
    {.end = 1},
};
led_setup_t leds_stand_ring[] = {
    {.hs = 0, .he = 100, .rs = 0, .re = 0, .gs = 255, .ge = 255, .bs = 246, .be = 246, .ef = EF_NONE},
    {.end = 1},
};
led_setup_t leds_stand_exercise[] = {
    {.hs = 0,  .he = 33,  .rs = 0,   .re = 64,  .gs = 255, .ge = 255, .bs = 246, .be = 200, .ef = EF_NONE},
    {.hs = 33, .he = 66,  .rs = 64,  .re = 130, .gs = 255, .ge = 255, .bs = 200, .be = 100, .ef = EF_NONE},
    {.hs = 66, .he = 100, .rs = 130, .re = 166, .gs = 255, .ge = 255, .bs = 100, .be = 0,   .ef = EF_NONE},
    {.end = 1},
};
led_setup_t leds_move_stand_exercise[] = {
    // Stand (青蓝)
    {.hs = 0, .he = 33, .rs = 0, .re = 80, .gs = 255, .ge = 255,  .bs = 246, .be = 123,  .ef = EF_NONE},
    // Exercise (荧光绿)
    {.hs = 33, .he = 66,  .rs = 166,   .re = 166, .gs = 255, .ge = 119, .bs = 0, .be = 0, .ef = EF_NONE},
    // Move (红)
    {.hs = 66,  .he = 100,  .rs = 200, .re = 250,   .gs = 17,  .ge = 17, .bs = 79,  .be = 79, .ef = EF_NONE},
    {.end = 1},
};
led_setup_t leds_lightblue_with_rainbow_stripe[] = {
    // 背景粉红色
    {.hs = 0, .he = 100, .rs = 255, .re = 255, .gs = 128, .ge = 128, .bs = 192, .be = 192, .ef = EF_NONE},

    // 深紫色条纹，从粉色中“减去”蓝红
    {.hs = 0,  .he = 15, .rs = 100, .re = 100, .gs = 0,   .ge = 128, .bs = 150, .be = 192, .ef = EF_SCR_R | EF_SUBTRACT},
    {.hs = 15, .he = 30, .rs = 100, .re = 100, .gs = 128, .ge = 0,   .bs = 192, .be = 150, .ef = EF_SCR_R | EF_SUBTRACT},

    {.end = 1},
};
led_setup_t leds_pink_with_purple_stripe[] = {
    // 背景：更浓更紫的粉底
    {.hs = 0, .he = 100, .rs = 255, .re = 255, .gs = 20, .ge = 20, .bs = 147, .be = 147, .ef = EF_NONE},

    // 条纹：抽掉红绿（不抽蓝），让紫浮现
    {.hs = 0,  .he = 15,  .rs = 140, .re = 140, .gs = 40,  .ge = 80,  .bs = 0,   .be = 0,   .ef = EF_SCR_R | EF_SUBTRACT},
    {.hs = 15, .he = 30,  .rs = 140, .re = 140, .gs = 80,  .ge = 40,  .bs = 0,   .be = 0,   .ef = EF_SCR_R | EF_SUBTRACT},

    {.end = 1},
};
led_setup_t leds_duolingo_runner[] = {
    // 背景：多邻国绿
    {.hs = 0, .he = 100, .rs = 52, .re = 52, .gs = 240, .ge = 240, .bs = 50, .be = 50, .ef = EF_NONE},

    // 条纹段1：更亮的绿 → Duo 盯你
    {.hs = 0,  .he = 15, .rs = 200, .re = 102, .gs = 240, .ge = 230, .bs = 150, .be = 100, .ef = EF_SCR_R | EF_SUBTRACT},
    {.hs = 15, .he = 30, .rs = 102, .re = 200, .gs = 230, .ge = 240, .bs = 100, .be = 150, .ef = EF_SCR_R | EF_SUBTRACT},

    {.end = 1},
};
led_setup_t leds_black_with_duolingo[] = {
    {.hs = 0, .he = 15, .rs = 0, .re = 52, .gs = 0, .ge = 250, .bs = 0, .be = 50, .ef = EF_SCR_R},
    {.hs = 15, .he = 30, .rs = 52, .re = 0, .gs = 250, .ge = 0, .bs = 50, .be = 0, .ef = EF_SCR_R},
    {.end = 1},
};
// Add the new animation name to the list below following its format

void *led_setups[] = {leds_exercise_ring, leds_move_ring, leds_stand_ring, leds_move_stand_exercise, leds_pink_with_purple_stripe, leds_duolingo_runner, leds_black_with_duolingo, leds_rainbow_s, leds_rainbow_ns, leds_green, leds_blue, leds_off};

const uint8_t led_setups_count = sizeof(led_setups) / sizeof(led_setups[0]);
