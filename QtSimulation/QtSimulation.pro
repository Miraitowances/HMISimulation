QT       += core gui axcontainer

RC_ICONS = head.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Components/externevent.cpp \
    Components/information.cpp \
    Components/screendispaly.cpp \
    ExternCFun/Base.c \
    ExternCFun/DriveFunction.c \
    ExternCFun/FImageFunction.c \
    ExternCFun/FontFunction.c \
    ExternCFun/HMIDispScreen.c \
    ExternCFun/HMIPushButton.c \
    ExternCFun/HMIinteraction.c \
    ExternCFun/HMIlinteradef.c \
    ExternCFun/ImitateFunction.c \
    ExternCFun/InterfaceDefine.c \
    ExternCFun/SuperNumber.c \
    ExternCFun/extcfunction.cpp \
    Function/extconnect.cpp \
    MouseEvent/labelmouse.cpp \
    UserLogin/gencode.cpp \
    UserLogin/userlogin.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Components/externevent.h \
    Components/information.h \
    Components/screendispaly.h \
    ExternCFun/Base.h \
    ExternCFun/DriveFunction.h \
    ExternCFun/FImageFunction.h \
    ExternCFun/FontFunction.h \
    ExternCFun/HMIDispScreen.h \
    ExternCFun/HMIPushButton.h \
    ExternCFun/HMIinteraction.h \
    ExternCFun/HMIlinteradef.h \
    ExternCFun/ImitateFunction.h \
    ExternCFun/InterfaceDefine.h \
    ExternCFun/SuperNumber.h \
    ExternCFun/extcfunction.h \
    Function/extconnect.h \
    MouseEvent/labelmouse.h \
    UserLogin/gencode.h \
    UserLogin/userlogin.h \
    mainwindow.h

FORMS += \
    Components/externevent.ui \
    Components/information.ui \
    Components/screendispaly.ui \
    UserLogin/gencode.ui \
    UserLogin/userlogin.ui \
    mainwindow.ui


INCLUDEPATH += \
    $$PWD/MouseEvent    \
    $$PWD/Components    \
    $$PWD/UserLogin     \
    $$PWD/Function      \
    $$PWD/ExternCFun    \



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/Resources.qrc

DISTFILES += \
    head.ico
