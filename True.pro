QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogaddalgorithm.cpp \
    dialogaddparamrow.cpp \
    dialogparameters.cpp \
    dialogresults.cpp \
    gridcontroller.cpp \
    gridmodel.cpp \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    mediator.cpp \
    worker.cpp \
    workerthreadcontroller.cpp

HEADERS += \
    ../../../../c++/Qt/qtdllteszt/IObserver.h \
    ../../../../c++/Qt/qtdllteszt/ipathfinder.h \
    dialogaddalgorithm.h \
    dialogaddparamrow.h \
    dialogparameters.h \
    dialogresults.h \
    gridcontroller.h \
    gridmodel.h \
    iobserver.h \
    ipathfinder.h \
    logger.h \
    mainwindow.h \
    mediator.h \
    mypoint.h \
    worker.h \
    workerthreadcontroller.h

FORMS += \
    dialogaddalgorithm.ui \
    dialogaddparamrow.ui \
    dialogparameters.ui \
    dialogresults.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../../c++/dllteszt/Debug/dllteszt.dll
