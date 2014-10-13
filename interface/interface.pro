#-------------------------------------------------
#
# Project created by QtCreator 2012-05-25T13:41:33
#
#-------------------------------------------------

QT += core gui network widgets testlib multimedia multimediawidgets

TEMPLATE = app

DEPENDPATH += ../diana-qutty
DEPENDPATH += ../

INCLUDEPATH += /usr/include/QtMultimediaKit
INCLUDEPATH += /usr/include/QtMobility

INCLUDEPATH += ./ \
  ./utils \
  ./data \
  ./settings \
  ./camera

TARGET = interface

CONFIG += ordered

SOURCES += \
  ./data/electronicdataview.cpp \
  ./data/electronic_view.cpp \
  ./data/abstract_electronic_data_manager.cpp \
  ./command_interface.cpp \
  ./settings/settings_page.cpp \
  ./settings/settings.cpp \
  ./settings/settings_network.cpp \
  ./settings/settings_interface.cpp \
  ./utils/d_logger.cpp \
  ./unitTesting/unittest.cpp \
  ./unitTesting/unittestmanager.cpp \
  ./unitTesting/electronicviewcsvreader.cpp \
  ./camera/cam.cpp \
  ./main.cpp

HEADERS  += \
  ./command_interface.h \
  ./data/electronic_view.h \
  ./data/electronicdataview.h \
  ./data/abstract_electronic_data_manager.h \
  ./costants.h \
  ./settings/settings_network.h \
  ./settings/settings_interface.h \
  ./settings/settings.h \
  ./settings/settings_page.h \
  ./utils/d_logger.h \
  ./unitTesting/unittest.h \
  ./unitTesting/unittestmanager.h \
  ./unitTesting/electronicviewcsvreader.h \
  ./camera/cam.h

FORMS += $$files(ui/*.ui)

win32 {
    DEFINES += _WINDOWS
}

unix {
    DEFINES += _LINUX
}

RESOURCES += ui/Resources.qrc

# find a way to copy config files to the build directory automatically.

extraFiles.path = $$OUT_PWD/defaults
extraFiles.files = ./defaults
INSTALLS += extraFiles

