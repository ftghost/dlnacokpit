/* 
 * File:   UpnpManager.h
 * Author: ghost
 *
 * Created on 26 juillet 2015, 16:23
 */

#ifndef UPNPMANAGER_H
#define	UPNPMANAGER_H
#include <vector>
#include "congig.h"

class UpnpManager
{
public:
    virtual ~UpnpManager();
    static UpnpManager & GetInstance();
    UpnpRoot  AddDevice(Upnp_Discovery * uDiscover);
    char * RemoveDevice(Upnp_Discovery * uDiscover);
    bool WriteInfoService(UpnpRoot *uStruct);
    UpnpRoot GetStructureDeviceByIndex(int);
    
private:
    UpnpManager& operator= (const UpnpManager&){}
    UpnpManager (const UpnpManager&){}
    std::vector<UpnpRoot> UpnpServiceArray;   
    static pthread_mutex_t mutexManager;
    static UpnpManager m_instance;
    bool ParseAndAddDevice(std::vector<Dictionnaire> dict , UpnpRoot *uStruct);
    bool ParseAndAddServiceAction(UpnpListService *ListService);
    std::vector< std::vector<Dictionnaire> > ParseAndAddActionParameters(std::vector<UpnpListAction> ListAction,std::vector< std::vector<Dictionnaire> > dic);
    UpnpManager();

};

#endif	/* UPNPMANAGER_H */

