/* 
 * File:   UpnpDiscover.h
 * Author: ghost
 *
 * Created on 21 juillet 2015, 20:27
 */

#ifndef UPNPDISCOVER_H
#define	UPNPDISCOVER_H


#include <upnp/upnp.h>
#include "UpnpManager.h"
class UpnpDiscover 
{

    public:
        virtual ~UpnpDiscover();
        static UpnpDiscover & GetInstance();
        UpnpClient_Handle GetHandle();
        static char * LastState ;
        static bool Stopped;
        static bool Started;
        

       
        
private:
    UpnpDiscover& operator= (const UpnpDiscover&){}
    UpnpDiscover (const UpnpDiscover&){}
    UpnpClient_Handle handle;
    static int callback(Upnp_EventType event_type, void *event, void *cookie);
    static pthread_mutex_t mutex;
    static UpnpDiscover m_instance;
    UpnpDiscover();
    
    
public:
    void start();
    void stop();


};

#endif	/* UPNPDISCOVER_H */

