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

class UpnpEventManager {
public:
    public:
    static UpnpEventManager & GetInstance();
    virtual ~UpnpEventManager();
    bool SetEvent(Upnp_Event *);
    bool SetSelected(int);
    bool Run();
   
private:
    UpnpEventManager& operator= (const UpnpEventManager&){}
    UpnpEventManager (const UpnpEventManager&){}
    UpnpEventManager();
    static UpnpEventManager m_instance;
    struct Upnp_Event *e_event = NULL;
    int SelectedIndex=-1;
    

};

#endif /* UPNPEVENTMANAGER_H */

