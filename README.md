## 概要
M5StackのCoreMP135にて、LCDをフレームバッファ機能で描画し、タッチパネルを使用するサンプル。
LovyanGFXライブラリを使用する。

サンプルの動作：
https://x.com/nnn112358/status/1791830049139966350

CoreMP135:https://www.switch-science.com/products/9650

## 開発環境
Description:    Ubuntu 22.04.3 LTS


## 準備する手順

クロスコンパイラのインストール

```
sudo apt install gcc-arm-linux-gnueabihf
```

リポジトリのダウンロード
```
git clone https://github.com/nnn112358/CoreMP135_LovyanGFX_test
```

LovyanGFXのダウンロード（*.cppと同フォルダにLovyanGFXを配置する）
```
cd CoreMP135_LovyanGFX_test
git clone https://github.com/lovyan03/LovyanGFX.git
```


## ビルド手順

cmakeにて、クロスコンパイラでのビルドを行う。
./build/coremp135_LovyanGFXにファイルが生成される。

```
cd CoreMP135_LovyanGFX_test
mkdir build
cmake ..
make
```

## 既知の不具合
libsdl2-devがインストールされている環境で、クロスコンパイラでのビルドを行うとエラーが発生する。

```
$ sudo apt install libsdl2-dev
$ make
[ 95%] Building CXX object CMakeFiles/coremp135_LovyanGFX.dir/coremp135_touchpanel.cpp.o
In file included from /usr/include/SDL2/SDL_stdinc.h:31,
                 from /usr/include/SDL2/SDL_main.h:25,
                 from /opt/LinuxHome/CoreMP135/CoreMP135_LovyanGFX_test/LovyanGFX/src/lgfx/v1/platforms/sdl/common.hpp:32,
                 from /opt/LinuxHome/CoreMP135/CoreMP135_LovyanGFX_test/LovyanGFX/src/lgfx/v1/platforms/sdl/Panel_sdl.hpp:23,
                 from /opt/LinuxHome/CoreMP135/CoreMP135_LovyanGFX_test/LovyanGFX/src/lgfx/v1/platforms/device.hpp:94,
                 from /opt/LinuxHome/CoreMP135/CoreMP135_LovyanGFX_test/LovyanGFX/src/lgfx/v1_init.hpp:22,
                 from /opt/LinuxHome/CoreMP135/CoreMP135_LovyanGFX_test/LovyanGFX/src/LovyanGFX.hpp:31,
                 from /opt/LinuxHome/CoreMP135/CoreMP135_LovyanGFX_test/coremp135_touchpanel.cpp:4:
/usr/include/SDL2/SDL_config.h:4:10: fatal error: SDL2/_real_SDL_config.h: No such file or directory
    4 | #include <SDL2/_real_SDL_config.h>
      |          ^~~~~~~~~~~~~~~~~~~~~~~~~
compilation terminated.
make[2]: *** [CMakeFiles/coremp135_LovyanGFX.dir/build.make:370: CMakeFiles/coremp135_LovyanGFX.dir/coremp135_touchpanel.cpp.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:83: CMakeFiles/coremp135_LovyanGFX.dir/all] Error 2
make: *** [Makefile:91: all] Error 2
```


## 暫定回避策

LovyanGFXでは、/usr/includeを探索して、SDLのファイルがあると参照してしまうようである。ビルドのために、いったん削除する。

```
$ sudo apt remove libsdl2-dev
```

## 参考資料
CM4Stack LGFX test program@tunefs
https://github.com/tunefs/cm4stack_lgfxtest

LovyanGFX@lovyan03
https://github.com/lovyan03/LovyanGFX

