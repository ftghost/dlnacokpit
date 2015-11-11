/* 
 * File:   UpnpActionFactory.h
 * Author: ghost
 *
 * Created on 12 août 2015, 17:45
 */

#ifndef UPNPACTIONFACTORY_H
#define	UPNPACTIONFACTORY_H
#include "congig.h"

class UpnpActionFactory 
{
public:
    virtual ~UpnpActionFactory();
    static UpnpActionFactory & GetInstance();
    bool CreateAction(UpnpListAction &Action,char * ActionName,char *url,char * ServiceType,std::vector<Dictionnaire> data,char *UrlBase);
    
    
private:
    UpnpActionFactory& operator= (const UpnpActionFactory&){}
    UpnpActionFactory (const UpnpActionFactory&){}
    static UpnpActionFactory m_instance;
    UpnpActionFactory();    
    static pthread_mutex_t mutex;

};

#endif	/* UPNPACTIONFACTORY_H */

