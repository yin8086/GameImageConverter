#-------------------------------------------------
#
# Project created by QtCreator 2013-06-06T16:11:49
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = GameImageConverter
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ./include/
SOURCES += main.cpp \
    ThreadWorker.cpp \
    InParser/UnityInParser.cpp \
    BufferParser/AlphaBufParser.cpp \
    BufParserFac/NorBufParFac.cpp \
    BufferParser/RGBA4444BufParser.cpp \
    BufferParser/ARGB1555BufParser.cpp \
    BufferParser/RGBA8888BufParser.cpp \
    BufferParser/RGB888BufParser.cpp \
    BufferParser/RGB565BufParser.cpp \
    BufferParser/ARGB8888BufParser.cpp \
    BufferParser/ARGB4444BufParser.cpp \
    BufferParser/PVRCT4BufParser.cpp \
    InterPic.cpp \
    InParserFac.cpp \
    InParse.cpp

HEADERS += \
    ThreadWorker.h \
    InterPic.h \
    InParse.h \
    OutParser.h \
    InParser/UnityInParser.h \
    BufferParser.h \
    BufferParser/AlphaBufParser.h \
    BufParFactory.h \
    BufParserFac/NorBufParFac.h \
    BufferParser/RGBA4444BufParser.h \
    BufferParser/ARGB1555BufParser.h \
    BufferParser/RGB565BufParser.h \
    BufferParser/RGBA8888BufParser.h \
    BufferParser/RGB888BufParser.h \
    BufferParser/ARGB8888BufParser.h \
    BufferParser/ARGB4444BufParser.h \
    BufferParser/PVRCT4BufParser.h \
    BaseDef.h \
    InParserFac.h