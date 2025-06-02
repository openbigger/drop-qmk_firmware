#pragma once

#include "quantum.h"

// Define all of LEDs
enum shift_v1_led_numbers  {
    //0~17
    KB_LED_ESC = 0,//checked
    KB_LED_F1 = 1,//checked
    KB_LED_DEL = 13,
    KB_LED_HOME = 14,//checked
    //18~35
    KB_LED_1 = 19,//checked
    KB_LED_2 = 20,//checked
    KB_LED_EQL = 30,//checked
    KB_LED_NUM= 32,
    //36~53
    KB_LED_TAB = 36,//checked
    KB_LED_R = 40,//checked
    KB_LED_P7 = 50,//checked
    //54~71
    KB_LED_CAPS = 54,
    KB_LED_H = 60,//checked
    KB_LED_PPLS = 70,//checked
    //71~87
    KB_LED_Z = 72,
    KB_LED_DOT = 80,//checked
    KB_LED_RSFT = 82,
    KB_LED_UP = 83,
    //88~98
    KB_LED_WIN = 89,
    KB_LED_LALT = 90,//checked.
    KB_LED_SPC = 91,
    KB_LED_RALT = 92,
    KB_LED_FN = 93,
    KB_LED_PDOT = 98,//checked keyboard end
    //99~118
    EG_LED_L_UP = 99,
    EG_LED_R_UP = 121,
    EG_LED_L_DOWN = 130,
    EG_LED_R_DOWN = 154,
    //105 between f4 f5
    //108 f7
    //115 between f12 del
    //124 between PrtSc -
    //134 between right 0
    //160 `  
    //163~165
    IND_LED_UP = 163,//cap
    IND_LED_MID = 164,//num
    IND_LED_DOWN = 165,//scroll
};

#define MAX_TRACK_KEYS 5 // 最多同时记录多少个按下的键

typedef struct {
    uint8_t led_index;
    uint32_t timer_start;
    bool active;
} led_flash_t;
extern led_flash_t flashes[MAX_TRACK_KEYS];
//extern os_variant_t current_os;//OS_UNSURE;
//赛博灯效
//#define TOTAL_KEYS RGB_MATRIX_LED_COUNT
#define UPDATE_INTERVAL 50            // 控制整体刷新频率
#define MOUSE_PROBABILITY 4           // 每次尝试“出洞”的概率百分比
#define MIN_DURATION 500              // 老鼠最短停留时间 ms
#define MAX_DURATION 1000              // 老鼠最长停留时间 ms

typedef enum {
    MOLE_AREA_KEYS,
    MOLE_AREA_CHASSIS,
} mole_area_t;

typedef struct {
    bool active;              // 当前是否有老鼠
    uint16_t start_time;      // 老鼠出现时间
    uint16_t duration;        // 这只老鼠停留多久
} mole_states_t;

void my_rgb_matrix_cyber_flash(mole_area_t area, uint8_t r, uint8_t g, uint8_t b);
extern bool is_flash;

void refresh_indicators_kb(void);//键盘指示灯，大写锁定等按下后点亮自己
void refresh_indicators_layer(uint8_t layer_num);//三个小灯改为layer指示灯，在哪一层亮哪个灯
void refresh_pressed_key_LED(led_flash_t *f);//键盘按下后，点亮自己
void rgb_light_keys(void);//调节层的灯光布局
//全键盘水波
extern bool is_splash;
void my_rgb_matrix_splash(uint8_t start_led);
// 单灯控制，呼吸
void my_rgb_matrix_LED_single(uint8_t led_index, uint8_t mode);
//简单改色
void my_rgb_matrix_pure_color(uint8_t start_led, uint8_t r, uint8_t g, uint8_t b);
//彩虹底盘灯
void my_rgb_matrix_animate_chassis_rainbow(void);
// 为 mode 命名
#define MY_LED_MODE_WHITE      0
#define MY_LED_MODE_BLUE       1
#define MY_LED_MODE_YELLOW     2
#define MY_LED_MODE_DRAGON     3
#define MY_LED_MODE_STATIC_PURPLE 4
#define BREATH_INTERVAL 30  // 每次亮度更新的间隔（毫秒）

//weak
bool process_record_openbigger(uint16_t keycode, keyrecord_t *record);

/*
#define RGB_AZURE       0x99, 0xF5, 0xFF    // 天蓝色 / 蔚蓝色
#define RGB_BLACK       0x00, 0x00, 0x00    // 黑色
#define RGB_BLUE        0x00, 0x00, 0xFF    // 蓝色
#define RGB_CHARTREUSE  0x80, 0xFF, 0x00    // 黄绿色 / 查特酒绿
#define RGB_CORAL       0xFF, 0x7C, 0x4D    // 珊瑚色
#define RGB_CYAN        0x00, 0xFF, 0xFF    // 青色 / 蓝绿色
#define RGB_GOLD        0xFF, 0xD9, 0x00    // 金色
#define RGB_GOLDENROD   0xD9, 0xA5, 0x21    // 金菊色 / 金杆色
#define RGB_GREEN       0x00, 0xFF, 0x00    // 绿色
#define RGB_MAGENTA     0xFF, 0x00, 0xFF    // 洋红色 / 品红色
#define RGB_ORANGE      0xFF, 0x80, 0x00    // 橙色
#define RGB_PINK        0xFF, 0x80, 0xBF    // 粉色
#define RGB_PURPLE      0x7A, 0x00, 0xFF    // 紫色
#define RGB_RED         0xFF, 0x00, 0x00    // 红色
#define RGB_SPRINGGREEN 0x00, 0xFF, 0x80    // 春绿色
#define RGB_TEAL        0x00, 0x80, 0x80    // 蓝绿色 / 水鸭色
#define RGB_TURQUOISE   0x47, 0x6E, 0x6A    // 青绿松石色
#define RGB_WHITE       0xFF, 0xFF, 0xFF    // 白色
#define RGB_YELLOW      0xFF, 0xFF, 0x00    // 黄色
#define RGB_OFF         RGB_BLACK           // 关闭（黑色）
*/
//#define RGB_PINK_DARKER      0xFF, 0x80, 0xC0   // 代码粉, AI粉255, 20, 147
#define RGB_PINK_DARKER      0xE0, 0x60, 0xA0   // 深粉色
#define RGB_PINK_BERRY       0xC0, 0x40, 0x80    // 莓果粉
#define RGB_PURPLE_DARKER    0x60, 0x00, 0xC0   // 深紫色
#define RGB_PURPLE_DEEPER    0x80, 0x00, 0xff   // 更浓的紫
#define RGB_ORANGE_RICH  0xFF, 0x50, 0x00  // 更正的橙色（亮但不黄）

#define RGB_MOVE_RING      0xFA, 0x11, 0x4F   // 活动（红色）
#define RGB_EXERCISE_RING  0xA6, 0xFF, 0x00   // 锻炼（绿色）
#define RGB_STAND_RING     0x00, 0xFF, 0xF6   // 站立（蓝色）
#define RGB_DUOLINGO_GREEN  0x66, 0xE6, 0x64  // 多邻国绿 R: 102, G: 230, B: 100
#define RGB_DUOLINGO_SOFT_GREEN  0x66, 0xCC, 0x66

#define STR_HELLO_MM "Hello 毛毛! 欢迎使用 OpenBigger 键盘."
#define STR_GO_TO_DIE "go to hell~ しねえ、死ね、死ね！"
#define STR_PINYIN "nimen1douqu1siba4"
/*
 * HSV 色相对照表（H 为 Hue，单位：度）
 * S = 255（饱和度最大），V = 255（明度最大）时对应的颜色及其心理感受：
 *
 * H     S   V     显示颜色   | 感觉说明
 * 0     255 255   红色       | 鲜明、热烈
 * 30    255 255   橙色       | 活力、温暖
 * 60    255 255   黄色       | 轻快、提示
 * 120   255 255   绿色       | 安全、健康
 * 180   255 255   青色       | 科技感、冷静
 * 240   255 255   蓝色       | 稳重、理性
 * 300   255 255   紫色       | 神秘、优雅
 * 330   255 255   桃红色     | 活泼、梦幻
 *
 * 可参考此表选择合适的色调用于灯效设计，既美观又符合功能意图。
 */