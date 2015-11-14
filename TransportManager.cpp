/* 
 * File:   GetDeviceData.cpp
 * Author: ghost
 * 
 * Created on 31 octobre 2015, 10:42
 */

#include "TransportManager.h"
#include "UpnpManager.h"
#include "UpnpActionFactory.h"
#include "vectorTool.h"
#include "xmlTool.h"
#include <QDebug>
#include "DataManager.h"

TransportManager::TransportManager(int index) 
{
    rootIndex = index;
}

TransportManager::TransportManager(const TransportManager& orig) 
{
}

TransportManager::~TransportManager() 
{
}


bool   TransportManager::GetSerciceUrlControl()
{
        memset(urlControl,'\0',sizeof(urlControl));
        char * psz_url = vectorTool::get_value_of_arg(serviceAvTransportManager.Dic,"controlURL");
        if(psz_url==NULL)
        {
            return false;
        }

        if(u.UrlBase[strlen(u.UrlBase)-1]=='/')
        {
            u.UrlBase[strlen(u.UrlBase)-1]='\0';
        }
        sprintf(urlControl,"%s%s",u.UrlBase,psz_url);
        return true;
}

bool   TransportManager::GetSerciceType()
{
        memset(ServiceType,'\0',sizeof(ServiceType));
        char *Serv = vectorTool::get_value_of_arg(serviceAvTransportManager.Dic,"serviceType");
        if(Serv==NULL)
        {
            return false;
        }
        else
        {
            strcpy(ServiceType,Serv);
        }
        return true;   
}


UpnpListService TransportManager::GetServiceConnectionManager()
{
 UpnpListService NulllistService;
    try
    {
        
          NulllistService.IdService = -1;
        for(int i=0;i<u.upnpListDevice.size();i++)
        {
            if(u.upnpListDevice[i].IsUnknow == false)
            {

                if(u.upnpListDevice[i].Isreader == false)
                {
                   for(int j=0;j<u.upnpListService.size();j++)
                   {
                       if(u.upnpListService[j].IsUnknow == false)
                       {
                          if(u.upnpListService[j].IsConnectionManager == true)
                          {
                              return u.upnpListService[j];
                          }
                       }
                   }
                }
            }
        }
        return NulllistService;
    }
    catch(...)
    {
        return NulllistService;
    }   
}


 bool TransportManager::PrepareUri(Dictionnaire * d)
 {
    std::vector<Dictionnaire> data;
    vectorTool::InsertOrModifyVector(data,"CurrentURI",d->Playurl);     
    bool resultat = UpnpActionFactory::GetInstance().CreateAction(actionSetUriAvTransportManager,"SetAVTransportURI",(char*)urlControl,(char*)ServiceType,data,u.UrlBase); 
    return true;
 }
 
 bool TransportManager::Play()
 {
    std::vector<Dictionnaire> data;
    bool resultat = UpnpActionFactory::GetInstance().CreateAction(actionPlayAvTransportManager,"Play",(char*)urlControl,(char*)ServiceType,data,u.UrlBase);     
    return true;
 }




UpnpListAction TransportManager::GetActionConnectionManager(char * ActionName)
{
UpnpListAction NulllistAction;
    try
    {
        
        NulllistAction.IdAction=-1;
        int indexAction = 0;
        for(int i=0;i<serviceConnectionManager.ListAction.size();i++)
        {
           char * actionName = vectorTool::get_value_of_arg(serviceConnectionManager.ListAction[i].Dic,"name");
           if(actionName == NULL)
           {
                  continue;
           }
           else
           {
            if(strcmp(actionName,ActionName)==0)
            {
               return serviceConnectionManager.ListAction[i];
            }
           }
        }
        return NulllistAction;
    }
    catch(...)
    {
        return NulllistAction;
    }   
}


 UpnpListService TransportManager::GetServiceAvTransportManager()
 {
 UpnpListService NulllistService;
    try
    {
        
        NulllistService.IdService = -1;
        for(int i=0;i<u.upnpListDevice.size();i++)
        {
            if(u.upnpListDevice[i].IsUnknow == false)
            {

                if(u.upnpListDevice[i].Isreader == true)
                {
                   for(int j=0;j<u.upnpListService.size();j++)
                   {
                       if(u.upnpListService[j].IsUnknow == false)
                       {
                          if(u.upnpListService[j].IsAvTransport == true)
                          {
                              return u.upnpListService[j];
                          }
                       }
                   }
                }
            }
        }
        return NulllistService;
    }
    catch(...)
    {
        return NulllistService;
    }       
 }
 
 
 UpnpListAction TransportManager::GetActionAvTransportManager(char * ActionName)
 {
    UpnpListAction NulllistAction;
    try
    {
        
        NulllistAction.IdAction=-1;
        int indexAction = 0;
        for(int i=0;i<serviceAvTransportManager.ListAction.size();i++)
        {
           char * actionName = vectorTool::get_value_of_arg(serviceAvTransportManager.ListAction[i].Dic,"name");
           if(actionName == NULL)
           {
                  continue;
           }
           else
           {
            if(strcmp(actionName,ActionName)==0)
            {
               return serviceAvTransportManager.ListAction[i];
            }
           }
        }
        return NulllistAction;
    }
    catch(...)
    {
        return NulllistAction;
    }       
 }




void TransportManager::run()
{
    bool deviceType = false;
    u = UpnpManager::GetInstance().GetStructureDeviceByIndex(rootIndex); 
    if(u.idRoot ==-1) 
    {
      termine(rootIndex,false,deviceType);
      return;
    }

    serviceConnectionManager=GetServiceConnectionManager();
    //Service
    if(serviceConnectionManager.IdService != -1)
    {
         actionConnectionManager = GetActionConnectionManager("PrepareForConnection");
        if(actionConnectionManager.IdAction !=-1 )
        {
            //TODO CALL PrepareForConnection
            qDebug() << "Service Connectoin Manager trouvé" << serviceConnectionManager.IdService;  
        }
    }
    strcpy(InstanceId,"0");
    
    
    
    serviceAvTransportManager = GetServiceAvTransportManager();
    if(serviceAvTransportManager.IdService == -1)
    {
      termine(rootIndex,false,deviceType);
      return;   
    }
  //Get SetUri ACtion
    actionSetUriAvTransportManager = GetActionAvTransportManager("SetAVTransportURI");
    if(actionSetUriAvTransportManager.IdAction == -1)
    {
      termine(rootIndex,false,deviceType);
      return;   
    }
    
    actionPlayAvTransportManager = GetActionAvTransportManager("Play");
    {
      if(actionPlayAvTransportManager.IdAction == -1)
      {
        termine(rootIndex,false,deviceType);
        return;   
      }
    }
   
    
    
    
    //Url de controle
    if(GetSerciceUrlControl()== false)
    {
      termine(rootIndex,false,deviceType);
      return;       
    }
    qDebug() << "Url de control trouvé" << urlControl;  
    
    //Service type
    if(GetSerciceType()==false)
    {
      termine(rootIndex,false,deviceType);
      return;    
    }
    qDebug() << "Service type trouvé" << ServiceType;  
    //
    
    
  
    termine(rootIndex,true,deviceType);
}