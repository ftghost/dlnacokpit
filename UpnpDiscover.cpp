/* 
 * File:   UpnpDiscover.cpp
 * Author: ghost
 * 
 * Created on 21 juillet 2015, 20:27
 */

#include "UpnpDiscover.h"
#include "DataManager.h"
#include "xmlTool.h"
#include <pthread.h>



UpnpDiscover::UpnpDiscover() 
{
  
       
}


#include "DataManager.h"
#include <QDebug>
pthread_mutex_t UpnpDiscover::mutex;

UpnpDiscover UpnpDiscover::m_instance=UpnpDiscover();
char * UpnpDiscover::LastState=NULL;
bool UpnpDiscover::IsRead = false;

int UpnpDiscover::callback(Upnp_EventType event_type, void* event, void* cookie)
{
    pthread_mutex_lock(&mutex);
    int ret = 0;
    struct Upnp_Discovery *d_event = NULL;
    struct Upnp_Event *e_event = NULL;
    char * name =NULL;
    char * Sta =NULL;
    UpnpRoot uStruct;
    try
    {   
        
        switch (event_type)
        {
            case UPNP_DISCOVERY_ADVERTISEMENT_ALIVE:
            case UPNP_DISCOVERY_SEARCH_RESULT:
                d_event = (struct Upnp_Discovery *)event;
                uStruct = UpnpManager::GetInstance().AddDevice(d_event);
                //qDebug() << "Discover" << uStruct.idRoot;
                if(uStruct.idRoot != -1)
                {
                    DataManager::GetInstance().EventNewDeviceAdded(uStruct.idRoot);
                }
                ret = d_event->ErrCode;
                break;
            
            case UPNP_DISCOVERY_ADVERTISEMENT_BYEBYE:
                d_event = (struct Upnp_Discovery *)event;
                name = UpnpManager::GetInstance().RemoveDevice(d_event);
                //TODO RETIRE DEVICE
                ret = d_event->ErrCode;
                break; 
                
          
                
            case UPNP_EVENT_RECEIVED:
                e_event = (struct Upnp_Event *)event;
                Sta = NULL;
                Sta = xmlTool::get_lastChange(xmlTool::get_argument_value( e_event->ChangedVariables,"LastChange"));
                if(Sta != NULL)
                {
                    if(strcmp(Sta,"STOPPED")==0 )
                    {
                       IsRead = false; 
                    }
                    if(strcmp(Sta,"PLAYING")==0 )
                    {
                        IsRead = true;
                        if(IsRead == true)
                        {
                            if(LastState != NULL)
                            {
                               if(strcmp(LastState,"TRANSITIONING")==0)
                               {
                                   DataManager::GetInstance().SetNextUri(); //Todo set nexturi
                                   qDebug() << "Add file";
                               }
                            }
                        }
                    }
                    if(LastState != NULL) delete LastState;
                    LastState = new char[strlen(Sta)+1];
                    strcpy(LastState,Sta);
                    
                }
                qDebug() << LastState<< "****" << Sta << "****" << IsRead;
                break;
                
            default:
                ret = 998;
                break;
        }
                
        
    }
    catch(...)
    {
      ret =  999;
    }
    pthread_mutex_unlock(&mutex);
    return ret;
}

UpnpClient_Handle UpnpDiscover::GetHandle()
{
    return handle;
}

void UpnpDiscover::start()
{
    char *type = "upnp:rootdevice"; 
    
    if (UpnpInit(NULL, 0) != UPNP_E_SUCCESS)
    {   
        UpnpFinish();
        return;
    }
    if(UpnpRegisterClient(callback, NULL, &handle)!=UPNP_E_SUCCESS)
    {
        UpnpFinish();
        return;
    }
    
    int ret = UpnpSearchAsync(handle, 5, type, NULL);
    
    if(ret!=UPNP_E_SUCCESS)
    {
        UpnpFinish();
        return;   
    }
    
}


void UpnpDiscover::stop()
{
    if (UpnpFinish()!= UPNP_E_SUCCESS)
    {   
        UpnpFinish();
    }
}


UpnpDiscover & UpnpDiscover::GetInstance()
{
  return m_instance;
}

UpnpDiscover::~UpnpDiscover()
{
    stop();
}
