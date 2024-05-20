# CMake�̍ŏ��o�[�W�������w��
cmake_minimum_required (VERSION 3.8)

# �v���W�F�N�g���ƌ�����w��
project(coremp135_LovyanGFX)

# �R���p�C���̎w�� (�N���X�R���p�C���p�̐ݒ�)
SET(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
SET(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)

# LovyanGFX���C�u������Linux�̃t���[���o�b�t�@���g�p���邱�Ƃ��`
add_definitions(-DLGFX_LINUX_FB)

# �\�[�X�t�@�C���������I�Ɍ����ă��X�g�A�b�v
# GLOB���g�����ƂŁA�w�肵���p�^�[���Ƀ}�b�`����t�@�C���̃��X�g���쐬
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

# ���s�\�t�@�C�����쐬���A�\�[�X�t�@�C����ǉ�
add_executable(coremp135_LovyanGFX ${Target_Files})

# �C���N���[�h�f�B���N�g�����w��
# ����ɂ��A�v���W�F�N�g���̂ǂ̏ꏊ����ł�LovyanGFX�̃w�b�_�[�t�@�C���ɊȒP�ɃA�N�Z�X�ł���
target_include_directories(coremp135_LovyanGFX PUBLIC "LovyanGFX/src/")

# C++17�̋@�\���g�p���邽�߂̐ݒ�
target_compile_features(coremp135_LovyanGFX PUBLIC cxx_std_17)

# �X���b�h���C�u�����ւ̃����N���w��
# �}���`�X���b�h���g�p����ꍇ�ɕK�v
target_link_libraries(coremp135_LovyanGFX -lpthread)

# �R���p�C���I�v�V������ݒ�
# �����ł̓R�����g�A�E�g����Ă��܂����A�K�v�ɉ����ē���̃I�v�V������L���ɂ��邱�Ƃ��ł��܂�
#target_compile_options(coremp135_LovyanGFX PRIVATE -nostdinc)