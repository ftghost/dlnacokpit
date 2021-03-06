/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransportManager.h
 * Author: ghost
 *
 * Created on 12 novembre 2015, 19:13
 */

#ifndef TRANSPORTMANAGER_H
#define TRANSPORTMANAGER_H



#include <QThread>
#include "congig.h"


class TransportManager :public QThread
{
Q_OBJECT

public:
    TransportManager(int);
    TransportManager(const TransportManager& orig);
    virtual ~TransportManager();
    char * GetInstanceId();
    char * GetIconPath();
    bool PrepareUri(Dictionnaire * d);
    bool PrepareNextUri(Dictionnaire * d);
    bool Play();
    bool Pause();
    bool Stop();
    bool Next();
    bool SetVolume(char *);
    bool GetVolume();
    char * GetVolumeExt();
    bool SetVolumeExt(char *);
    bool GetInfo();
    QList<QString> GetInfoExt();



signals:
    void termine(int index,bool IsOk,bool IsServer);
    
private:
    bool isStop;
    bool isNext;
    bool isPause;
    
    
    
    
    int rootIndex;
    UpnpRoot u;
    UpnpListService serviceConnectionManager;
    UpnpListAction  actionConnectionManager;    
    UpnpListService serviceAvTransportManager;
    UpnpListAction  actionSetUriAvTransportManager;    
    UpnpListAction  actionPlayAvTransportManager;    
    UpnpListAction  actionPauseAvTransportManager;  
    UpnpListAction  actionStopAvTransportManager;  
    UpnpListAction  actionNextAvTransportManager;  
    UpnpListAction  actionSetNextUriAvTransportManager;
    UpnpListService serviceRenderingControl;
    UpnpListAction  actionSetVolumeRenderingControl;
    UpnpListAction  actionGetVolumeRenderingControl;
    UpnpListAction  actionGetPositionInfoAvTransportManager;
    
    char ServiceTypeRenderer[500];
    char urlControlRenderer[500]; 
    char urlControl[500]; 
    char ServiceType[500]; 
    char volume[5];
    char InstanceId[10];
    char *Track;
    char *AbsTime;
    char *TrackDuration;
    char *RelTime;
    bool GetSerciceType();
    bool GetSerciceRendererType();
    bool GetSerciceUrlControl();
    bool GetSerciceUrlControlRenderer();
    
    UpnpListService GetServiceConnectionManager();
    UpnpListService GetServiceRenderingControl();
    UpnpListAction GetActionConnectionManager(char *);
    UpnpListService GetServiceAvTransportManager();
    UpnpListAction GetActionAvTransportManager(char *);
    UpnpListAction GetActionRenderingControl(char *);
    void run();
};

#endif	/* GETDEVICEDATA_H */





