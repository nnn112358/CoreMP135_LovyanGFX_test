# CMakeの最小バージョンを指定
cmake_minimum_required (VERSION 3.8)

# プロジェクト名と言語を指定
project(coremp135_LovyanGFX)

# コンパイラの指定 (クロスコンパイル用の設定)
SET(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
SET(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)

# LovyanGFXライブラリがLinuxのフレームバッファを使用することを定義
add_definitions(-DLGFX_LINUX_FB)

# ソースファイルを自動的に見つけてリストアップ
# GLOBを使うことで、指定したパターンにマッチするファイルのリストを作成
file(GLOB Target_Files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS
    *.cpp
    LovyanGFX/src/lgfx/Fonts/efont/*.c
    LovyanGFX/src/lgfx/Fonts/IPA/*.c
    LovyanGFX/src/lgfx/utility/*.c
    LovyanGFX/src/lgfx/v1/*.cpp
    LovyanGFX/src/lgfx/v1/misc/*.cpp
    LovyanGFX/src/lgfx/v1/panel/Panel_Device.cpp
    LovyanGFX/src/lgfx/v1/platforms/framebuffer/*.cpp
    )

# 実行可能ファイルを作成し、ソースファイルを追加
add_executable(coremp135_LovyanGFX ${Target_Files})

# インクルードディレクトリを指定
# これにより、プロジェクト内のどの場所からでもLovyanGFXのヘッダーファイルに簡単にアクセスできる
target_include_directories(coremp135_LovyanGFX PUBLIC "LovyanGFX/src/")

# C++17の機能を使用するための設定
target_compile_features(coremp135_LovyanGFX PUBLIC cxx_std_17)

# スレッドライブラリへのリンクを指定
# マルチスレッドを使用する場合に必要
target_link_libraries(coremp135_LovyanGFX -lpthread)

# コンパイラオプションを設定
# ここではコメントアウトされていますが、必要に応じて特定のオプションを有効にすることができます
#target_compile_options(coremp135_LovyanGFX PRIVATE -nostdinc)
