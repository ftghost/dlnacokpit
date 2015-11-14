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
    bool PrepareUri(Dictionnaire * d);
    bool Play();
    

signals:
    void termine(int index,bool IsOk,bool IsServer);
    
private:
    int rootIndex;
    UpnpRoot u;
    UpnpListService serviceConnectionManager;
    UpnpListAction  actionConnectionManager;    
    UpnpListService serviceAvTransportManager;
    UpnpListAction  actionSetUriAvTransportManager;    
    UpnpListAction  actionPlayAvTransportManager;    
    char urlControl[500]; 
    char ServiceType[500]; 
    char InstanceId[10];
    bool GetSerciceType();
    bool GetSerciceUrlControl();
    UpnpListService GetServiceConnectionManager();
    UpnpListAction GetActionConnectionManager(char *);
    UpnpListService GetServiceAvTransportManager();
    UpnpListAction GetActionAvTransportManager(char *);
    void run();
};

#endif	/* GETDEVICEDATA_H */





