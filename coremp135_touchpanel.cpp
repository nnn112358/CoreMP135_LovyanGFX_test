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

// �X�N���[���̕��ƍ������`���܂��B
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
// �g�p����t���[���o�b�t�@�f�o�C�X�̃p�X���`���܂��B
#define FRAMEBUFFER_DEVICE "/dev/fb1"
// �^�b�`�C�x���g����������f�o�C�X�̃p�X���`���܂��B
#define TOUCH_EVENT_DEVICE "/dev/input/by-path/platform-4c004000.i2c-event"
// �^�b�`�|�C���g�̔��a���`���܂��B
int TOUCH_POINT_RADIUS=5;

// �f�B�X�v���C�̏����ݒ���s�����߂̃I�u�W�F�N�g���쐬���܂��B
LGFX lcd(SCREEN_WIDTH, SCREEN_HEIGHT, FRAMEBUFFER_DEVICE);
// �f�B�X�v���C��ő�����s�����߂̃X�v���C�g���쐬���܂��B
static LGFX_Sprite lcdSprite(&lcd);

int main() {
    // �f�B�X�v���C�̏��������s���܂��B
    lcd.init();
    // �f�B�X�v���C�̐F�[�x��16�r�b�g�ɐݒ肵�܂��B
    lcd.setColorDepth(16);
    // �f�B�X�v���C���N���A���܂��B
    lcd.fillScreen(0);
    // �e�L�X�g�̐F�𔒎��ɍ��w�i�Őݒ肵�܂��B
    lcd.setTextColor(TFT_WHITE, TFT_BLACK);

    // �^�b�`�C�x���g�̃f�o�C�X�t�@�C����ǂݍ��ݐ�p�ŊJ���܂��B
    int inputFileDescriptor = open(TOUCH_EVENT_DEVICE, O_RDONLY);
    if (inputFileDescriptor < 0) {
        perror("Failed to open the input device");
        return 1;
    }

    input_event touchEvent;
    int touchX = 0, touchY = 0;

    while (true) {
        // �^�b�`�C�x���g���������������ǂݎ��܂��B
        if (read(inputFileDescriptor, &touchEvent, sizeof(touchEvent)) == sizeof(touchEvent)) {
            switch (touchEvent.type) {
                case EV_KEY:
                    // ����̃L�[�iMeta�L�[�j�������ꂽ�ꍇ�A�X�N���[�����N���A���܂��B
                    if (touchEvent.code == KEY_LEFTMETA && touchEvent.value == 1) {
                        lcd.fillScreen(0);
                    }
                    break;
                case EV_ABS:
                    // X���W���X�V���ꂽ�ꍇ�A���̒l���X�V���܂��B
                    if (touchEvent.code == ABS_MT_POSITION_X) {
                        touchX = touchEvent.value;
                    } else if (touchEvent.code == ABS_MT_POSITION_Y) {
                        // Y���W���X�V���ꂽ�ꍇ�A���̈ʒu�ɉ~��`�悵�܂��B
                        touchY = touchEvent.value;
                        lcd.setColor(lcd.color888(255, 0, 0));  // �F��Ԃɐݒ肵�܂��B
                        lcd.fillCircle(touchX, touchY, TOUCH_POINT_RADIUS);  // �^�b�`�|�C���g�ɉ~��`�悵�܂��B
                    }
                    break;
                default:
                    break;
            }
        }
    }
    // �C�x���g�������I�������f�o�C�X�t�@�C������܂��B
    close(inputFileDescriptor);
    return 0;
}
