QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    chessgame.cpp \
    chessgamegraphics.cpp \
    chesswidget.cpp \
    figure.cpp \
    figures.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    board.h \
    chessgame.h \
    chessgamegraphics.h \
    chesswidget.h \
    figure.h \
    figures.h \
    mainwindow.h \
    point.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Figures/Bishop.png \
    Figures/Cell.png \
    Figures/Dark_Bishop.png \
    Figures/Dark_Cell.png \
    Figures/Dark_King.png \
    Figures/Dark_Knight.png \
    Figures/Dark_Pawn.png \
    Figures/Dark_Queen.png \
    Figures/Dark_Rook.png \
    Figures/King.png \
    Figures/Pawn.png \
    Figures/Queen.png \
    Figures/Rook.png
