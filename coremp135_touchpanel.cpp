#include <stdio.h>

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>

#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <thread>
#include <random>

// スクリーンの幅と高さを定義します。
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
// 使用するフレームバッファデバイスのパスを定義します。
#define FRAMEBUFFER_DEVICE "/dev/fb1"
// タッチイベントを処理するデバイスのパスを定義します。
#define TOUCH_EVENT_DEVICE "/dev/input/by-path/platform-4c004000.i2c-event"
// タッチポイントの半径を定義します。
int TOUCH_POINT_RADIUS=5;

// ディスプレイの初期設定を行うためのオブジェクトを作成します。
LGFX lcd(SCREEN_WIDTH, SCREEN_HEIGHT, FRAMEBUFFER_DEVICE);
// ディスプレイ上で操作を行うためのスプライトを作成します。
static LGFX_Sprite lcdSprite(&lcd);

int main() {
    // ディスプレイの初期化を行います。
    lcd.init();
    // ディスプレイの色深度を16ビットに設定します。
    lcd.setColorDepth(16);
    // ディスプレイをクリアします。
    lcd.fillScreen(0);
    // テキストの色を白字に黒背景で設定します。
    lcd.setTextColor(TFT_WHITE, TFT_BLACK);

    // タッチイベントのデバイスファイルを読み込み専用で開きます。
    int inputFileDescriptor = open(TOUCH_EVENT_DEVICE, O_RDONLY);
    if (inputFileDescriptor < 0) {
        perror("Failed to open the input device");
        return 1;
    }

    input_event touchEvent;
    int touchX = 0, touchY = 0;

    while (true) {
        // タッチイベントが発生したら情報を読み取ります。
        if (read(inputFileDescriptor, &touchEvent, sizeof(touchEvent)) == sizeof(touchEvent)) {
            switch (touchEvent.type) {
                case EV_KEY:
                    // 特定のキー（Metaキー）が押された場合、スクリーンをクリアします。
                    if (touchEvent.code == KEY_LEFTMETA && touchEvent.value == 1) {
                        lcd.fillScreen(0);
                    }
                    break;
                case EV_ABS:
                    // X座標が更新された場合、その値を更新します。
                    if (touchEvent.code == ABS_MT_POSITION_X) {
                        touchX = touchEvent.value;
                    } else if (touchEvent.code == ABS_MT_POSITION_Y) {
                        // Y座標が更新された場合、その位置に円を描画します。
                        touchY = touchEvent.value;
                        lcd.setColor(lcd.color888(255, 0, 0));  // 色を赤に設定します。
                        lcd.fillCircle(touchX, touchY, TOUCH_POINT_RADIUS);  // タッチポイントに円を描画します。
                    }
                    break;
                default:
                    break;
            }
        }
    }
    // イベント処理が終わったらデバイスファイルを閉じます。
    close(inputFileDescriptor);
    return 0;
}
