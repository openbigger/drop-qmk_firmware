#include "openbigger.h"
#include "color.h"
#include "openbigger_keycodes.h"

led_flash_t flashes[MAX_TRACK_KEYS];
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
    
    switch (keycode) {
        
        case MY_SPLASH:
            if (record->event.pressed) {
                is_splash = !is_splash;
                dprintf("splash:%d\n",is_splash);
            }
            return false;
            
        case MY_SEND_MSG:
            if (record->event.pressed) {
                send_string(STR_HELLO_MM);
                wait_ms(200);
                send_string(STR_GO_TO_DIE);
                dprintf("altsplash:%d\n",is_splash);
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
    }
    
    return true;
}



//===================================
// 自定义函数区
//===================================
void refresh_indicators_kb(void) {
    //更新状态灯,它们本身亮
    if(host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(KB_LED_CAPS, RGB_SPRINGGREEN);
    }
    if(host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(KB_LED_NUM, RGB_SPRINGGREEN);
    }
    if(host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(IND_LED_DOWN, RGB_SPRINGGREEN);
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


void my_rgb_matrix_splash(uint8_t start_led) {
    
    static uint8_t offset = 0; // 流动偏移
    for (uint8_t i = start_led; i < RGB_MATRIX_LED_COUNT; i++) {
        if ((i + offset) % 10 < 5) {
            rgb_matrix_set_color(i, RGB_ORANGE_RICH); //ß.GPT说不能直接乘，反正能跑
        } else {
            rgb_matrix_set_color(i, 0, 0, 0); // 黑掉
        }
    }
    offset++; // 每次刷新偏移一下，造成流动效果
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
        else if(i == KB_LED_1||i == KB_LED_1+1||i == KB_LED_1+2)
        {
            rgb_matrix_set_color(i, RGB_EXERCISE_RING);
        }
        else if(i == KB_LED_TAB +8
                ||i == KB_LED_Z +4||i == KB_LED_Z +5
                ||i == KB_LED_SPC || i == KB_LED_SPC+1 )
        {
            rgb_matrix_set_color(i, RGB_STAND_RING);
        }
        else {
            //rgb_matrix_set_color(i, 0, 0, 0); // 
        }
    }
}