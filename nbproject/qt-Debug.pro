# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux
TARGET = DlnaCokpit
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets webkit
SOURCES += ChainedData.cpp DataManager.cpp GetDeviceData.cpp JavaScriptOperations.cpp QthreadMainWorker.cpp TransportManager.cpp UpnpActionFactory.cpp UpnpDiscover.cpp UpnpEventManager.cpp UpnpManager.cpp htmlTool.cpp main.cpp vectorTool.cpp xmlTool.cpp
HEADERS += ChainedData.h DataManager.h GetDeviceData.h JavaScriptOperations.h QthreadMainWorker.h TransportManager.h UpnpActionFactory.h UpnpDiscover.h UpnpEventManager.h UpnpManager.h congig.h htmlTool.h vectorTool.h xmlTool.h
FORMS +=
RESOURCES += Ressource.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += -lupnp -lcurl -lixml  
QT += core gui webkitwidgets
