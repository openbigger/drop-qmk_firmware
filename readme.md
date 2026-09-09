# 💡 Drop SHIFT V1 自定义键盘固件（feature/riot_xap 分支）

[![Platform](https://img.shields.io/badge/platform-DropSHIFT-blue?style=flat-square)]()
[![Support](https://img.shields.io/badge/support-Mac_Layer-orange?style=flat-square)]()
[![LED](https://img.shields.io/badge/LED-Pink_Mode-F06292?style=flat-square)]()
[![Status](https://img.shields.io/badge/status-Active-brightgreen?style=flat-square)]()
[![Last Commit](https://img.shields.io/github/last-commit/openbigger/drop-qmk_firmware?style=flat-square)](https://github.com/openbigger/drop-qmk_firmware/commits)
[![License](https://img.shields.io/badge/license-Open%20Source-blue?style=flat-square)]()
[![Powered by ChatGPT](https://img.shields.io/badge/🤖_-Code_with_GPT-10a37f?style=flat-square&logo=openai&logoColor=white)](https://openai.com/chatgpt)
[![Version](https://img.shields.io/badge/version-v1.2-blue)](https://github.com/openbigger/drop-qmk_firmware)
[![Platform](https://img.shields.io/badge/platform-Mac%20%7C%20Win-lightgrey)]()


> 🛠 本分支基于 Drop官方提供的库中[`drop_led`](https://github.com/Massdrop/qmk_firmware/tree/feature/riot_xap/users/drop_led) 用户模块进行深度定制，适配win和macOS平台、增强灯效控制、优化默认布局。
> 
> 💡 Drop官方[`How to Configure your Drop Keyboard!`](https://helpdesk.drop.com/hc/en-us/articles/44444057868305-How-to-Configure-your-Drop-Keyboard) 详细介绍了键盘的自定义过程并附离线编辑烧录程序下载链接。其中[`在线自定义`链接已失效](https://drop.com/mechanical-keyboards/configurator) 可在登陆后记住自己保存的键盘布局。由于界面自定义只能增加静态颜色，无法改变已有模式，且层的先后次序无法拖动，故clone官方库写自己的bin文件。
---

## bin文件说明
`users/openbigger/drop_shift_v1_mykbd.bin`为v1.2版本
`users/openbigger/drop_shift_v1_mykbd_1221.bin`为v1.3版本，加入Raw HID command
`users/openbigger/drop_shift_v1_mykbd_0908.bin`为v1.4版本，Raw HID 可传入底盘闪灯 RGB 颜色。

## 📦 分支说明

- 🔄 分支名：`feature/riot_xap`[`库链接`](https://github.com/Massdrop/qmk_firmware/tree/feature/riot_xap)
- 🔧 用户模块：从 `users/drop_led` 复制为 `users/openbigger`
- 🧠 `md_rgb_matrix_programs.c`中加入自定义灯效数组 `led_setups` 
- 💻 三层布局，从下到上：0 Win 模式、1 Mac 模式、2 调节层，用`Fn+1`切换，三个小灯可以显示在哪一层
- 🌈 灯光亮度调节：默认最大亮度由 `130` 改为 `70`（适配 Mac 节能，似乎没什么🐦用）

---
## 项目亮点

| 主题       | 内容                                                         |
|------------|--------------------------------------------------------------|
| 🎮 键盘侠   | Fn+2 狂闪底盘灯 Fn+4 打出一串文字                                 |
| 🐭 赛博地鼠   | Fn+3 全键盘晶莹闪烁                                 |
| 🟢 多邻国   | 绿主题灯效 + 滚动高亮和暗黑                                        |
| 🍎 苹果运动 | 健康三环灯效：Move / Exercise / Stand                        |
| 🍏 macOS   | Cmd/Alt 智能映射，capslock 检测支持 通过Fn+1切换win和mac键盘布局                               |
| 🤖 AI 键   | GPT 快捷调用，一键触发                                       |
| 🎨 自定义色 | 精调粉紫滚动、橘黄底盘灯，功能键色彩指示、阿松6子彩                                 |

## 🗂️ 项目结构
```
keyboards/drop/shift/v1/keymaps/mykbd/
├── keymap.c                      # 主键映射逻辑
├── rules.mk                      # 启用自定义用户模块
├── config.h                      # 上一层目录，最大亮度设置、功能启用
└── md_rgb_matrix_programs.c.bak  # 备份旧灯效设置（已删除）

users/openbigger/
└── lib/led_framework/
    ├── config.h                # from drop_led
    ├── openbigger_keycodes.c   # 自定义键值，把原keymaps的也搬过来
    ├── openbigger.c            # 自己的函数在自己这里跑
    ├── openbigger.h            # 拿给外面的用
    ├── post_config.h           # from drop_led
    ├── rgb_matrix_user.inc     # from drop_led
    └── rules.mk                # 编译路径
```
## 🌐 自定义功能说明

| 功能模块         | 描述 |
|------------------|------|
| Layer 切换指示灯 | 使用原有 NumLock / CapsLock / ScrollLock 灯显示当前 Layer 状态 |
| 粉色灯效         | 自定义若干灯效色彩替换原有 |
| CapsLock 自亮     | 按下 CapsLock 时，仅点亮自身按键灯，增强视觉提示 |
| 炫酷灯效 | Layer3调节层，激活后按2点亮底盘灯 |
| Raw HID command | 开灯：EA 12 21 01；关灯：EA 12 21 00 |
| 自定义按键     | Fn+4，输出字符串，右边Alt，叫出GPT（需要系统配合设置快捷键shift+ctrl+alt+g） |

## ⌨️ 层级说明

| 层编号 | 模式名称     | 功能描述                         |
|--------|--------------|----------------------------------|
| 0      | Win 默认层    | 标准 Windows 布局，默认灯效，win为紫色      |
| 1      | Mac 模式层    | 基层0层并兼容 macOS cmd，alt为紫色    |
| 2      | Fn 调节层     | 控制灯效模式切换、亮度、平台切换 |


## 📥 使用说明

```bash
# 编译固件（这里跑不通就去看AGENTS.md的5.编译）
qmk compile -kb drop/shift/v1 -km mykbd
# 因为是老分支用make更好
make drop/shift/v1:mykbd 
# Fn+b长按进入烧录模式 用drop的工具烧录到 Drop SHIFT

# 启动串口调试（查看按键、灯效日志）
qmk console
# 常常不成功，需要先进行python环境配置，一例：
export DYLD_LIBRARY_PATH=/opt/homebrew/lib:$DYLD_LIBRARY_PATH
# 窗口中看dprintf发出的东西，记得带变量，只有字符串用send
``` 

---

## ✅ License & Credits（标准文本）

```markdown
## 📜 License & Credits

- 本分支基于 [Massdrop 官方 QMK 分支 `feature/riot_xap`](https://github.com/Massdrop/qmk_firmware/tree/feature/riot_xap)
- 自定义用户模块：`users/ahem_drop_led`，由毛毛改写自 `drop_led`
- 项目遵循 QMK Firmware 的 [MIT License](https://github.com/qmk/qmk_firmware/blob/master/LICENSE)
- 特别感谢：QMK 社区、Drop 官方贡献者
```

# THIS IS THE DEVELOP BRANCH

Warning- This is the `develop` branch of QMK Firmware. You may encounter broken code here. Please see [Breaking Changes](https://docs.qmk.fm/#/breaking_changes) for more information.

# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the [Clueboard product line](https://clueboard.co).

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [Docsify](https://docsify.js.org/) and hosted on [GitHub](/docs/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls), or by clicking the "Edit this page" link at the bottom of any page.

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
