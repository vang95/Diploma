#-------------------------------------------------
#
# Project created by QtCreator 2016-10-23T15:04:04
#
#-------------------------------------------------

QT       += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisualLaserRadiation
TEMPLATE = app

INCLUDEPATH += /Components \
    Components/Visual \
    Components/UdpClient \
    Components/Main \
    Components/Data

SOURCES += main.cpp\
    Components/Visual/basicvisualradiation.cpp \
    Components/Visual/widgetvisualradiation.cpp \
    Components/UdpClient/updclient.cpp \
    Components/Main/widgetsetting.cpp \
    Components/Main/application.cpp \
    Components/Data/bufferdata.cpp \
    Components/UdpClient/packetarray.cpp

HEADERS  +=  Components/Visual/basicvisualradiation.h \
    Components/Visual/widgetvisualradiation.h \
    Components/UdpClient/updclient.h \
    Components/Main/application.h \
    Components/Main/widgetsetting.h \
    Components/Data/array.h \
    Components/Main/header.h \
    Components/Data/bufferdata.h \
    Components/UdpClient/packetarray.h

