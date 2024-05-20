## 概要
M5StackのCoreMP135にて、タッチパネルを使用するサンプル。
LovyanGFXライブラリを使用する。

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

LovyanGFXのダウンロード

```
cd LovyanGFX
git clone https://github.com/lovyan03/LovyanGFX.git
```


## ビルド手順

```
cd CoreMP135_LovyanGFX_test
mkdir build
cmake ..
make
```


## 既知の不具合




## 参考資料
CM4Stack LGFX test program@tunefs
https://github.com/tunefs/cm4stack_lgfxtest

LovyanGFX@lovyan03
https://github.com/lovyan03/LovyanGFX

