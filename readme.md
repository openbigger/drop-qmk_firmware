# 💡 Drop SHIFT V1 自定义键盘固件（feature/riot_xap 分支）

[![Platform](https://img.shields.io/badge/platform-DropSHIFT-blue?style=flat-square)]()
[![Support](https://img.shields.io/badge/support-Mac_Layer-orange?style=flat-square)]()
[![LED](https://img.shields.io/badge/LED-Pink_Mode-F06292?style=flat-square)]()
[![Status](https://img.shields.io/badge/status-Active-brightgreen?style=flat-square)]()
[![Last Commit](https://img.shields.io/github/last-commit/openbigger/drop-qmk_firmware?style=flat-square)](https://github.com/openbigger/drop-qmk_firmware/commits)
[![License](https://img.shields.io/badge/license-Open%20Source-blue?style=flat-square)]()
[![Powered by ChatGPT](https://img.shields.io/badge/🤖_-Code_with_GPT-10a37f?style=flat-square&logo=openai&logoColor=white)](https://openai.com/chatgpt)

> 🛠 本分支基于 [`drop_led`](https://github.com/Massdrop/qmk_firmware/tree/feature/riot_xap/users/drop_led) 用户模块进行深度定制，适配多平台、增强灯效控制、优化默认布局。

---

## 📦 分支说明

- 🔄 分支名：`feature/riot_xap`
- 🔧 用户模块：从 `users/drop_led` 复制为 `users/ahem_drop_led`
- 🧠 `md_rgb_matrix_programs.c`中加入自定义灯效数组 `led_setups` ，`keymap.c`中加入粉色动态效果
- 💻 三层布局，从下到上：0 Win 模式、1 Mac 模式、2 调节层，用`Fn+1`切换，三个小灯可以显示在哪一层
- 🌈 灯光亮度调节：默认最大亮度由 `130` 改为 `80`（适配 Mac 节能）

---

## 🗂️ 项目结构
```
keyboards/drop/shift/v1/keymaps/mykbd/
├── keymap.c                # 主键映射逻辑
├── rules.mk                # 启用自定义用户模块
├── config.h                # 最大亮度设置、功能启用
└── md_rgb_matrix_programs.c.bak  # 备份旧灯效设置（可删除）

users/ahem_drop_led/
└── lib/led_framework/
    ├── md_led_framework.c         # 主灯效框架
    ├── md_rgb_matrix.c            # LED 渲染函数
    └── md_rgb_matrix_programs.c   # 灯效数组定义（含粉色）
```
## 🌐 自定义功能说明

| 功能模块         | 描述 |
|------------------|------|
| Layer 切换指示灯 | 使用原有 NumLock / CapsLock / ScrollLock 灯显示当前 Layer 状态 |
| 粉色灯效         | 在 Layer 1 时自动切换为粉色灯效模式，支持动态或全亮模式 |
| CapsLock 自亮     | 按下 CapsLock 时，仅点亮自身按键灯，增强视觉提示 |
| Mac 模式炫酷灯效 | Layer 1（Mac 层）激活后开启炫彩打字灯效 |
| 最大亮度调节     | RGB 灯光最大亮度从默认 130 降低为 80，适配 MacBook 电源管理 |

## ⌨️ 层级说明

| 层编号 | 模式名称     | 功能描述                         |
|--------|--------------|----------------------------------|
| 0      | Win 默认层    | 标准 Windows 布局，默认灯效      |
| 3      | Fn 调节层     | 控制灯效模式切换、亮度、平台切换 |
| 1      | Mac 模式层    | 兼容 macOS 快捷键，带炫酷灯效    |

## 📥 使用说明

```bash
# 编译固件
qmk compile -kb drop/shift/v1 -km mykbd

# 烧录到 Drop SHIFT
qmk flash -kb drop/shift/v1 -km mykbd

# 启动串口调试（查看按键、灯效日志）
qmk console
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
