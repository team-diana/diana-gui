#-------------------------------------------------
#
# Project created by QtCreator 2012-05-25T13:41:33
#
#-------------------------------------------------

QT += core gui network widgets testlib multimedia multimediawidgets

TEMPLATE = app

DEPENDPATH += ../diana-qutty
DEPENDPATH += ../

INCLUDEPATH += ./
INCLUDEPATH += ../diana-qutty/
INCLUDEPATH += ../diana-qutty/puttysrc
INCLUDEPATH += ../diana-qutty/tmux

INCLUDEPATH += /usr/include/QtMultimediaKit
INCLUDEPATH += /usr/include/QtMobility

#---  ros library. Still in development
INCLUDEPATH += ../ros/
#---

TARGET = interface

CONFIG += ordered

SOURCES += main.cpp\
    command_interface.cpp \
    comunication.cpp \
    commands.cpp \
    qcontroller.cpp \
    console.cpp \
    cam.cpp \
    settings.cpp \
    settings_page.cpp \ 
    settings_network.cpp \
    qutty.cpp \
    Qutty_config_window.cpp \
    d_logger.cpp \
    electronic_view.cpp \
    abstract_electronic_data_manager.cpp \
    test_electronic_data_manager.cpp \
    ros_electronic_data_manager.cpp \
    electronicdataview.cpp \
    unitTesting/electronicviewcsvreader.cpp \
    settings_interface.cpp \
    unitTesting/unittestmanager.cpp \
    unitTesting/unittest.cpp \


HEADERS  += command_interface.h \
    comunication.h \
    commands.h \
    qcontroller.h \
    console.h \
    TypeLib_CC.h \
    TypeLib_CC.h \
    cam.h \
    XBeeAPI.h \
    settings.h \
    settings_page.h \ 
    settings_network.h \
    qutty.h \
    Qutty_config_window.h \
    d_logger.h \
    electronic_view.h \
    ros_electronic_data_manager.h \
    abstract_electronic_data_manager.h \
    test_electronic_data_manager.h \
    electronicdataview.h \
    unitTesting/electronicviewcsvreader.h \
    settings_interface.h \
    costants.h \
    unitTesting/unittestmanager.h \
    unitTesting/unittest.h \

FORMS    += command_interface.ui \
    settings.ui \
    settings_network.ui \
    settings_interface.ui \
    Qutty_config_window.ui

LD_LIBRARY_PATH+=../qutty

LIBS += -L.. -L../QuTTY -lQuTTY

win32 {
    LIBS += -L"$$_PRO_FILE_PWD_/SDL/lib/" -lSDL
    LIBS += -L"$$_PRO_FILE_PWD_"-llibXBeeAPI_V5
    DEFINES += _WINDOWS
}

unix {
    LIBS += -L"./SDL/lib" -lSDL
    DEFINES += _LINUX
}

RESOURCES += \
    Resources.qrc

# find a way to copy config files to the build directory automatically.

extraFiles.path = $$OUT_PWD/defaults
extraFiles.files = ./defaults
INSTALLS += extraFiles

