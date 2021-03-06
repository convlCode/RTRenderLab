#-------------------------------------------------
#
# Project created by QtCreator 2019-07-15T16:27:31
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RTRenderLab
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    Camera.cpp \
    Mesh.cpp \
    Model.cpp \
    ResourceManager.cpp \
    Texture2D.cpp \
        main.cpp \
        mainwindow.cpp \
    GLWidget.cpp \
    Shader.cpp \
    renderOBJ/Coordinate.cpp \
    renderOBJ/Cube.cpp \
    renderOBJ/Plane.cpp

HEADERS += \
    Camera.h \
    Mesh.h \
    Model.h \
    ResourceManager.h \
    Texture2D.h \
        mainwindow.h \
    GLWidget.h \
    Shader.h \
    renderOBJ/Coordinate.h \
    renderOBJ/Cube.h \
    renderOBJ/Plane.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    shaders.qrc

win32: LIBS += -L$$PWD/../../../openglDev/assimpLib/lib/ -lassimp-vc140-mt

INCLUDEPATH += $$PWD/../../../openglDev/assimpLib/include
DEPENDPATH += $$PWD/../../../openglDev/assimpLib/include
