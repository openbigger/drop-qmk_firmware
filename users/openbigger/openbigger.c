#include "openbigger.h"
#include "color.h"
#include "openbigger_keycodes.h"
#include "math.h"

#define PI 3.14159265f

led_flash_t flashes[MAX_TRACK_KEYS];
bool is_capslock = false;
//os_variant_t current_os = OS_MACOS;//OS_UNSURE;
/*想改成自动检测os没成功 放这里，残留一阵。需要include osdetect.h
bool process_detected_host_os_kb(os_variant_t detected_os) {
    current_os = detected_os;
    dprintf("Detected OS: %d\n", detected_os);
    // 这里可以设置灯光提示，或者保存到 EEPROM
    return true;
}
*/
bool is_splash = false;
bool is_flash = false;
__attribute__ ((weak))
bool process_record_openbigger(uint16_t keycode, keyrecord_t *record)
{
    //dprintf("keycode = %d\n", keycode);
    // 处理按键记录
    // 按下以后点亮成橘色一会儿
    if (record->event.pressed) {
        uint8_t row = record->event.key.row;
        uint8_t col = record->event.key.col;
        uint8_t led_index;
        if (rgb_matrix_map_row_column_to_led(row, col, &led_index)) {
            for (int i = 0; i < MAX_TRACK_KEYS; i++) {
                if (!flashes[i].active) {
                    flashes[i].led_index = led_index;
                    flashes[i].timer_start = timer_read32();
                    flashes[i].active = true;
                    break;
                }
            }
        }
    }

    if (keycode == KC_CAPS) {
        if (record->event.pressed) {
            is_capslock = !is_capslock;
        }
        return true;
    }
    
    switch (keycode) {

        case MY_SPLASH:
            if (record->event.pressed) {
                is_splash = !is_splash;
                dprintf("splash:%d\n",is_splash);
            }
            return false;

        case MY_SEND_MSG:
            if (record->event.pressed) {
                //send_string(STR_HELLO_MM);
                //wait_ms(200);
                //send_string(STR_GO_TO_DIE);
                //wait_ms(200);
                send_string(STR_PINYIN);
                wait_ms(200);
                send_string(STR_PINYIN);
                wait_ms(200);
                send_string(STR_PINYIN);
                wait_ms(200);
                send_string(STR_PINYIN);
                wait_ms(200);
                send_string(STR_PINYIN);
                wait_ms(200);
                send_string(STR_PINYIN);
                wait_ms(200);
                send_string("hahahahahahahahhahahaha1");
            }
            return false;
        case MY_FLASH:
            if (record->event.pressed) {
                is_flash =!is_flash;
                //dprintf("flash:%d\n",is_flash);
            }
            return false;
        /*// 检查os，看看alt和gui到底怎么实现的
        case MY_LALT:
            if (record->event.pressed) {
                register_code((current_os == OS_MACOS) ? KC_LGUI : KC_LALT);
            } else {
                dprintf("alt Detected OS: %d\n", current_os);
                unregister_code((current_os == OS_MACOS) ? KC_LGUI : KC_LALT);
            }
            return false;

        case MY_LGUI:
            if (record->event.pressed) {
                register_code((current_os == OS_MACOS) ? KC_LALT : KC_LGUI);
            } else {
                dprintf("gui Detected OS: %d\n", current_os);
                unregister_code((current_os == OS_MACOS) ? KC_LALT : KC_LGUI);
            }
            return false;
            */
    }   //end switch

    return true;
}



//===================================
// 自定义函数区
//===================================
void refresh_indicators_kb(void) {
    //更新状态灯,它们本身亮
    if((host_keyboard_led_state().caps_lock)||is_capslock) {
        rgb_matrix_set_color(KB_LED_CAPS, RGB_ORANGE_RICH);
    }
    if(host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(KB_LED_NUM, RGB_ORANGE_RICH);
    }
    if(host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(IND_LED_DOWN, RGB_ORANGE_RICH);
    }
} 

void refresh_pressed_key_LED(led_flash_t *f) {
    for (int i = 0; i < MAX_TRACK_KEYS; i++) {
        if (f[i].active) {
            if (timer_elapsed32(f[i].timer_start) < 500) {
                // 在闪烁期间，点亮橙色
                rgb_matrix_set_color(f[i].led_index, RGB_ORANGE_RICH);
            } else {
                // 超时后，停止闪烁
                f[i].active = false;
            }
        }
    }
}
// 赛博灯效，用is_flash判断

static mole_states_t mole_states[RGB_MATRIX_LED_COUNT] = {0};
void my_rgb_matrix_cyber_flash(mole_area_t area, uint8_t r, uint8_t g, uint8_t b) {
    uint16_t now = timer_read();

    bool do_logic = false;
    static uint16_t last_update = 0;
    if (timer_elapsed(last_update) > UPDATE_INTERVAL) {
        last_update = now;
        do_logic = true;
    }

    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        bool is_key = g_led_config.flags[i] & LED_FLAG_KEYLIGHT;
        if ((area == MOLE_AREA_KEYS && !is_key) ||
            (area == MOLE_AREA_CHASSIS && is_key)) {
            continue;  // 区域筛选，统一控制就不能在后面改底盘灯，只能加一个判断Í
        }

        // 状态更新
        if (do_logic) {
            if (mole_states[i].active) {
                if (timer_elapsed(mole_states[i].start_time) > mole_states[i].duration) {
                    mole_states[i].active = false;
                }
            } else {
                if ((rand() % 100) < MOUSE_PROBABILITY) {
                    mole_states[i].active = true;
                    mole_states[i].start_time = now;
                    mole_states[i].duration = MIN_DURATION + (rand() % (MAX_DURATION - MIN_DURATION + 1));
                }
            }
        }

        // 绘制灯光
        if (mole_states[i].active) {
            rgb_matrix_set_color(i, r, g, b);
        } else {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }
}

//全键盘水波
void my_rgb_matrix_splash(uint8_t start_led) {
    static uint8_t offset = 0; // 流动偏移
    for (uint8_t i = start_led; i < RGB_MATRIX_LED_COUNT; i++) {
        if ((i + offset) % 10 < 5) {
            rgb_matrix_set_color(i, RGB_ORANGE_RICH); //GPT说rgb不能直接乘，反正能跑
        } else {
            rgb_matrix_set_color(i, 0, 0, 0); // 黑掉
        }
    }
    offset++; // 每次刷新偏移一下，造成流动效果
}
//键盘改纯色，底盘灯起始EG_LED_L_UP = 99
void my_rgb_matrix_pure_color(uint8_t start_led, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = start_led; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, r, g, b);
    }
}
//彩虹底盘灯
static uint16_t hue_base = 0;
void my_rgb_matrix_animate_chassis_rainbow(void) {
    hue_base += 1;  // 控制速度，可改成 +=2, +=3 更快
    if (hue_base > 360) hue_base = 0;

    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (!(g_led_config.flags[i] & LED_FLAG_KEYLIGHT)) {
            HSV hsv = { .h = hue_base % 360, .s = 255, .v = 50 };  // 彩色 + 柔和亮度
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}
//单键灯效，一次刷新只能刷一个灯，多灯要开矩阵记忆很麻烦
void my_rgb_matrix_LED_single(uint8_t led_index, uint8_t mode) {
    // 静态变量：仅控制一个灯
    static uint16_t phase = 90;       // 初始化从最亮处开始（sin(90°) = 1）
    static uint8_t frame_count = 0;
    static uint8_t hold_counter = 0;  // 用于驻留时间控制
    static uint8_t last_mode = 255;
    static RGB lasst_color = {0x66, 0xCC, 0x66};// duolingo soft green

    // 切换模式时清除驻留和重置相位
    if (mode != last_mode) {
        last_mode = mode;
        hold_counter = 0;
        phase = 90;  // 保证开始时有可见亮度
        frame_count = 0;
    }
    // 如果更新时间没到，直接返回
    dprintf("LED INDEX = %u, count = %u\n", led_index, frame_count);
    frame_count++;
    if (frame_count < 12) {
        rgb_matrix_set_color(led_index, lasst_color.r, lasst_color.g, lasst_color.b);
        return;
    }
    frame_count = 0;
    // 驻留在亮点时不推进 phase
    if (hold_counter > 0) {
        hold_counter--;
    } else {
        phase += 2;
        if (phase >= 360) phase -= 360;

        // 亮点范围驻留 1 秒左右（15帧）
        if (phase >= 85 && phase <= 95) {
            hold_counter = 15;
        }
    }

    // 计算亮度（正弦波）
    float rad = phase * PI / 180.0f;
    float sin_value = sinf(rad);  // [-1, 1]
    uint8_t sparkle_brightness = (uint8_t)(100 + (sin_value + 1.0f) * 77.5f);  // [100,255]

    // 不同模式的色彩定义
    HSV hsv;
    switch (mode) {
        case 0: // 星空白
            hsv = (HSV){ 0, 0, sparkle_brightness };
            break;
        case 1: // 青蓝思考
            hsv = (HSV){
                140 + ((sparkle_brightness - 100) * 60 / 155),
                200,
                sparkle_brightness
            };
            break;
        case 2: // 灵感黄光
            hsv = (HSV){
                10 + ((sparkle_brightness - 100) * 40 / 155),//25～25+40
                230,
                sparkle_brightness
            };
            break;
        case 3: // 龙魂觉醒
            hsv = (HSV){
                0 + ((sparkle_brightness - 100) * 30 / 155),
                250,
                sparkle_brightness
            };
            break;
        case 4: // 深紫色
            hsv = (HSV){ 191, 255, 255 };//RGB(128, 0, 255)
             break;
        default:
            hsv = (HSV){ 0, 0, 0 };
            break;
    }

    RGB rgb = hsv_to_rgb(hsv);
    lasst_color = rgb;
    rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);
    //rgb_matrix_set_color(led_index, 255, 0, 0);  // 强制亮红
    dprintf("LED INDEX = %u, RGB = %d,%d,%d\n", led_index, rgb.r, rgb.g, rgb.b);
}

void refresh_indicators_layer(uint8_t layer_num) {
    rgb_matrix_set_color(IND_LED_DOWN, RGB_OFF); 
    rgb_matrix_set_color(IND_LED_UP, RGB_OFF);
    rgb_matrix_set_color(IND_LED_MID, RGB_OFF);

    rgb_matrix_set_color(IND_LED_DOWN-layer_num, RGB_SPRINGGREEN); 
}
//特殊调节层
void rgb_light_keys(void) {
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        // 键盘除了F1-F12全黑，底盘不变，这样可以看到变幻的灯光效果
        if((i < EG_LED_L_UP && i > KB_LED_DEL)|| i == 0 )
        {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
        // 点亮希望亮的LED
        if (i == KB_LED_DEL || i == KB_LED_DEL+1 || i == KB_LED_DEL+2||i == KB_LED_DEL+3||i == KB_LED_DEL+4
            || i== KB_LED_NUM || i == KB_LED_NUM+1 || i == KB_LED_NUM+2||i == KB_LED_NUM+3||i == KB_LED_NUM +4
            ||i==KB_LED_TAB || i== KB_LED_TAB+1 || i == KB_LED_TAB+2||i == KB_LED_TAB+3||i == KB_LED_TAB +4
            || i== KB_LED_CAPS || i == KB_LED_CAPS+1 || i == KB_LED_CAPS+2||i == KB_LED_CAPS+3||i == KB_LED_CAPS +4||i == KB_LED_CAPS +7||i == KB_LED_CAPS +8
            || i == KB_LED_Z|| i == KB_LED_Z+1 ||i == KB_LED_Z+3)
        {
            rgb_matrix_set_color(i, RGB_PURPLE_DEEPER); 
        } 
        else if(i == KB_LED_1||i == KB_LED_1+1||i == KB_LED_1+2||i == KB_LED_1+3)//自己加的键
        {
            rgb_matrix_set_color(i, RGB_EXERCISE_RING);
        }
        else if(i == KB_LED_TAB +8
                ||i == KB_LED_Z +5
                ||i == KB_LED_SPC || i == KB_LED_SPC+1 )
        {
            rgb_matrix_set_color(i, RGB_STAND_RING);
        }
        else if(i == KB_LED_Z +4 || i==KB_LED_FN)//B,Fn
        {
            rgb_matrix_set_color(i, RGB_ORANGE_RICH);
        }
        else {
            //rgb_matrix_set_color(i, 0, 0, 0); // 
        }
    }
}