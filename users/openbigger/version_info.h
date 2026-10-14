#pragma once

#define STR_VERSION "\nFirmware version: v1.5\n"
#define STR_INFO "Project: https://github.com/openbigger/drop-qmk_firmware\n" \
    "You can use KEYBOARD_FLASH_SKILL.md to create codex Notifications.\n\n"
#define STR_BGC_LOOP \
    "Background colours (Fn+A previous, Fn+D next):\n" \
    "Color 1: Exercise Green | Color 2: Move Pink\n" \
    "Color 3: Stand Cyan | Color 4: Activity Rings\n" \
    "Color 5: Pink Purple Runner\n" \
    "Color 6: Duolingo Runner | Color 7: Duo on Black\n" \
    "Color 8: Osomatsu Scroll | Color 9: Osomatsu Six Colours\n" \
    "Color 10: Green | Color 11: Blue\n\n"
#define STR_HOT_KEYS \
    "Custom keys:\n" \
    "Fn+1: Switch Windows / macOS layout\n" \
    "Fn+2: Toggle chassis splash\n" \
    "Fn+3: Toggle matrix cyber flash\n" \
    "Fn+4: Type preset message\n" \
    "Fn+5: Show this information\n" \
    "Right Alt: Call GPT; set shortcut Ctrl+Alt+Shift+G\n\n" \
    "Raw HID (32-byte report; first 7 bytes used):\n" \
    "Off: EA 12 21 00\n" \
    "On:  EA 12 21 SS RR GG BB\n" \
    "SS is non-zero; RR/GG/BB are RGB values (00-FF).\n" \
    "Use example:\n" \
    "Tell your agent: \"Use KEYBOARD_FLASH_SKILL.md to build a keyboard flash notification system.\"\n"
    
