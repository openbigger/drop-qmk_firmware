#pragma once

// 所有用户自定义按键从这个范围开始，避免和 QMK 标准 HID 键码冲突
// QMK 定义：#define SAFE_RANGE 0xF000
// 本文件中每个 enum 后面都接一个 *_SAFE_RANGE_END 占位符用于延续编号

// ========== keymap 层中专用按键 ==========

enum md_keycodes {
    L_BRI = SAFE_RANGE, //LED Brightness Increase                                   //Working
    L_BRD,              //LED Brightness Decrease                                   //Working
    L_EDG_I,            //LED Edge Brightness Increase
    L_EDG_D,            //LED Edge Brightness Decrease
    L_EDG_M,            //LED Edge lighting mode
    L_PTN,              //LED Pattern Select Next                                   //Working
    L_PTP,              //LED Pattern Select Previous                               //Working
    L_PSI,              //LED Pattern Speed Increase                                //Working
    L_PSD,              //LED Pattern Speed Decrease                                //Working
    L_RATIOD,
    L_RATIOI,
    L_T_MD,             //LED Toggle Mode                                           //Working
    L_T_ONF,            //LED Toggle On / Off                                       //Broken
    L_ON,               //LED On                                                    //Broken
    L_OFF,              //LED Off                                                   //Broken
    L_T_BR,             //LED Toggle Breath Effect                                  //Working
    L_T_PTD,            //LED Toggle Scrolling Pattern Direction                    //Working
    U_T_AGCR,           //USB Toggle Automatic GCR control                          //Working
    DBG_TOG,            //DEBUG Toggle On / Off                                     //
    DBG_MTRX,           //DEBUG Toggle Matrix Prints                                //
    DBG_KBD,            //DEBUG Toggle Keyboard Prints                              //
    DBG_MOU,            //DEBUG Toggle Mouse Prints                                 //
    DBG_FAC,            //DEBUG Factory light testing (All on white)
    MD_BOOT,
    NEW_SAFE_RANGE             //Restart into bootloader after hold timeout                //Working
};

// ========== openbigger 模块按键 ==========
enum openbigger_keycodes {
    MY_SEND_MSG = NEW_SAFE_RANGE,
    MY_SPLASH,

    OPENBIGGER_SAFE_RANGE_END
};

// ========== 未来其他模块可以继续这样扩展 ==========
/*
enum another_module_keycodes {
    FOO_BAR = KEYMAP_SAFE_RANGE_END,
    ...
    ANOTHER_SAFE_RANGE_END
};
*/