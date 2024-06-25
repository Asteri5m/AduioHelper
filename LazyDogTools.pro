QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += -lOle32 -lUser32 -lShlwapi -lversion -ladvapi32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audiomanager.cpp \
    main.cpp \
    lazydog.cpp \
    taskmonitor.cpp

HEADERS += \
    PolicyConfig.h \
    audiomanager.h \
    custom.h \
    lazydog.h \
    taskmonitor.h

FORMS += \
    lazydog.ui


#设置图标
RC_ICONS = LD_64.ico

#添加版本
VERSION = 0.0.2


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc


QMAKE_PROJECT_DEPTH = 0
