QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/controller.cc \
    ../model/cave/cave.cc \
    ../model/matrix.cc \
    ../model/maze/maze.cc \
    ../model/maze/mazegeneration.cc \
    ../model/maze/solver.cc \
    MazeScene.cc \
    caveform.cc \
    cavescene.cc \
    main.cc \
    mainwindow.cc

HEADERS += \
    ../controller/controller.h \
    ../model/cave/cave.h \
    ../model/matrix.h \
    ../model/maze/maze.h \
    ../model/maze/solver.h \
    MazeScene.h \
    caveform.h \
    cavescene.h \
    mainwindow.h

FORMS += \
    caveform.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
