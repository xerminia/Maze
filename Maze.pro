QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += sdk_no_version_check # macos ventura

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    model/cave.cpp \
    model/maze.cpp \
    model/maze_generate.cpp \
    view/mainwindow.cpp \
    view/mazewidget.cpp

HEADERS += \
    controller/controller.h \
    model/cave.h \
    model/maze.h \
    model/maze_generate.h \
    model/object.h \
    view/mainwindow.h \
    view/mazewidget.h

FORMS += \
    view/mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ICON = maze.png
