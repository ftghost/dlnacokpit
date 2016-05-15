/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UpnpEventManager.h
 * Author: ghost
 *
 * Created on 4 janvier 2016, 18:50
 */

#ifndef UPNPEVENTMANAGER_H
#define UPNPEVENTMANAGER_H

#include <upnp/upnp.h>
#include <QString>

class UpnpEventManager {
public:
    public:
    static UpnpEventManager & GetInstance();
    virtual ~UpnpEventManager();
    bool SetEvent(Upnp_Event *);
    bool SetSelected(int);
    bool Run();
    bool SetNextUriSet(bool);
    bool SetDataMangerStopped(bool);
   
private:
    UpnpEventManager& operator= (const UpnpEventManager&){}
    UpnpEventManager (const UpnpEventManager&){}
    UpnpEventManager();
    static UpnpEventManager m_instance;
    struct Upnp_Event *e_event = NULL;
    int SelectedIndex=-1;
    bool NextUriSet = false;
    bool IsStopped = false;
    bool IsDataMangerStopped = false;
    
    QString LastState = "";
    const QString NO_MEDIA_PRESENT = "NO_MEDIA_PRESENT";
    const QString STOPPED = "STOPPED";
    const QString TRANSITIONING = "TRANSITIONING";
    const QString PLAYING = "PLAYING";
};

#endif /* UPNPEVENTMANAGER_H */

