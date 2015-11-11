# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = DlnaCokpit
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets webkit
SOURCES += ChainedData.cpp DataManager.cpp DataStock.cpp GetDeviceData.cpp JavaScriptOperations.cpp QthreadMainWorker.cpp UpnpActionFactory.cpp UpnpDiscover.cpp UpnpManager.cpp htmlTool.cpp main.cpp vectorTool.cpp xmlTool.cpp
HEADERS += ChainedData.h DataManager.h DataStock.h GetDeviceData.h JavaScriptOperations.h QthreadMainWorker.h UpnpActionFactory.h UpnpDiscover.h UpnpManager.h congig.h htmlTool.h vectorTool.h xmlTool.h
FORMS +=
RESOURCES += Ressource.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += -lupnp -lcurl -lixml  
QT += core gui webkitwidgets
