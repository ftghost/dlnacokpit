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
#include "DataManager.h"
#include <QDebug>
#include "UpnpEventManager.h"


UpnpDiscover::UpnpDiscover() 
{
  
       
}


pthread_mutex_t UpnpDiscover::mutex;

UpnpDiscover UpnpDiscover::m_instance=UpnpDiscover();

int UpnpDiscover::callback(Upnp_EventType event_type, void* event, void* cookie)
{
    pthread_mutex_lock(&mutex);
    int ret = 0;
    struct Upnp_Discovery *d_event = NULL;
    struct Upnp_Event *e_event = NULL;
    char * name =NULL;
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
                UpnpEventManager::GetInstance().SetEvent((struct Upnp_Event *)event);
                UpnpEventManager::GetInstance().Run();
                /*
                e_event = (struct Upnp_Event *)event;
                Sta = NULL;
                inf = xmlTool::get_argument_value( e_event->ChangedVariables,"LastChange");
                Sta = xmlTool::get_VolumeChange(inf);
                if(Sta != NULL)
                {
                   //qDebug() << "Vol "  << Sta << "****"  ; 
                   DataManager::GetInstance().UpdateVolume(Sta);
                   delete Sta;
                   Sta=NULL;
                }
                
                Sta = xmlTool::get_lastChange(inf);
                if(Sta != NULL)
                {
                    if(LastState != NULL)
                        if(strcmp(Sta,"STOPPED")==0 && strcmp(LastState,"NO_MEDIA_PRESENT")!=0) 
                            Stopped = true;
                    
                    if(LastState == NULL)
                        if(strcmp(Sta,"NO_MEDIA_PRESENT")==0) 
                            Stopped = false;
                    
                    qDebug() << "Last : " << LastState<< "**** Now : " << Sta << "****"  << Stopped << "****" << Started;
                    if(strcmp(Sta,"PLAYING")==0)
                    {
                        if(LastState != NULL)
                        {
                            if(strcmp(LastState,"TRANSITIONING")==0)
                            {
                                if(Stopped==false || Started == true)
                                {
                                    Started = false;
                                    Stopped = false;
                                    DataManager::GetInstance().SetNextUri(); //Todo set nexturi
                                    //DataManager::GetInstance().UpdateTitre();
                                    qDebug() << "Add file";
                                }
                                else
                                {
                                   Stopped = false;
                                   Started = false;
                                   DataManager::GetInstance().SetSameUri(); //Todo set nexturi
                                   qDebug() << "Add same file"; 
                                }
                            }
                        }
                    }
                    else
                    {
                         if(strcmp(Sta,"STOPPED")==0 && Started == false) 
                         {
                            DataManager::GetInstance().PlayAndSetUri();
                            qDebug() << "Play-----";
                            //DataManager::GetInstance().UpdateTitre();
                         }
                    }
                    if(LastState != NULL) delete LastState;
                    LastState = new char[strlen(Sta)+1];
                    strcpy(LastState,Sta);
                }*/
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
