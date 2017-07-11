QT += core gui

CONFIG += c++11

TARGET = atwcman
CONFIG += console
CONFIG -= app_bundle

QMAKE_RPATH = $ORIGIN/lib

LIBS = -lpcre -L/lib/x86_64-linux-gnu/libpcre.so.3.13.2

TEMPLATE = app

SOURCES += main.cpp \
    includes/earlybirdlib.cpp \
    includes/geotools.cpp \
    includes/mjstime.cpp \
    convert.cpp \
    libmseed/fileutils.c \
    libmseed/genutils.c \
    libmseed/gswap.c \
    libmseed/lmplatform.c \
    libmseed/logging.c \
    libmseed/lookup.c \
    libmseed/msrutils.c \
    libmseed/pack.c \
    libmseed/packdata.c \
    libmseed/parseutils.c \
    libmseed/selection.c \
    libmseed/tracelist.c \
    libmseed/traceutils.c \
    libmseed/unpack.c \
    libmseed/unpackdata.c

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    convert.h \
    includes/earlybirdlib.h \
    libmseed/libmseed.h \
    libmseed/packdata.h \
    libmseed/unpackdata.h
