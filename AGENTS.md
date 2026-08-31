- 仔细阅读 readme.md
- 没有用户同意，不操作git，不删除增加文件，不安装新东西

## 新 Mac：clone、精简并编译 Drop SHIFT v1

仓库分支必须是 `feature/riot_xap`。不要把 keymap 迁移到新版官方 QMK；本键盘依赖这棵旧 firmware tree 的 RIOT 实现。

### 1. Clone

```bash
git clone --branch feature/riot_xap https://github.com/openbigger/drop-qmk_firmware.git
cd drop-qmk_firmware
```
### 2. 本机精简：只隐藏，不删除、不提交删除
使用 sparse-checkout。layouts/default/ 必须保留，旧 QMK CLI 启动时会读取它；layouts/community/ 可以隐藏。
```bash
git sparse-checkout init --no-cone
git sparse-checkout set --no-cone \
  '/*' '!/*/' \
  '/builddefs/' '/data/' '/drivers/' \
  '/keyboards/drop/' \
  '/layouts/default/' \
  '/lib/fnv/' '/lib/lib8tion/' '/lib/python/' '/lib/riot/' '/lib/printf/' \
  '/platforms/' '/quantum/' '/tmk_core/' '/util/' \
  '/users/drop_led/' '/users/openbigger/'
```
不要 git rm、git reset --hard、暂存删除，或为了精简而修改上游目录。
### 3. 只初始化本键盘所需子模块
```bash
git submodule update --init lib/riot lib/printf
```
不要初始化 chibios、chibios-contrib、googletest、lufa、lvgl、pico-sdk、vusb。
### 4. 本机工具（都放仓库外，每台机器情况不同，供参考）
macOS 自带 make 3.81 太旧；需要 GNU Make 4：
```bash
brew install make
```
QMK CLI 仍然需要：Makefile 会用它生成 
```bash
version.h、info_config.h 等文件。
python3 -m venv ~/.qmk-venv
~/.qmk-venv/bin/python -m pip install --upgrade pip
~/.qmk-venv/bin/python -m pip install qmk
~/.qmk-venv/bin/python -m pip install -r requirements.txt
```
需要官方 Arm GNU Toolchain（带 newlib）。不要使用 Homebrew 的 arm-none-eabi-gcc；它在此机器上缺 ARM stdint.h。
建议缓存到：
```bash
~/Library/Caches/dropkb-arm-gnu-toolchain/14.2.rel1/Payload/bin
```
### 5. 编译
必须用 gmake，并加 SKIP_GIT=yes。旧 QMK 的默认 Make 路径会自动同步全部子模块；此参数会阻止它。
```bash
PATH="$HOME/.qmk-venv/bin:$HOME/Library/Caches/dropkb-arm-gnu-toolchain/14.2.rel1/Payload/bin:$PATH" \
PYTHONPATH="$PWD/lib/python" \
gmake SKIP_GIT=yes TARGET=drop_shift_v1_mykbd_1221 drop/shift/v1:mykbd WERROR=0
```
产物在仓库根目录，生成前先询问版本号。不要覆盖旧 bin；改 TARGET= 的尾号生成新版本。版本号1221:
`drop_shift_v1_mykbd_1221.bin`
编译完成后删除临时产物：
`rm -rf .build`
### 6. VS Code 只显示根仓库
在 VS Code 用户设置加入：
`"git.detectSubmodules": false`
然后执行用户cmd+shift+p Developer: Reload Window。Source Control 只显示 drop-qmk_firmware，不会单列子模块。