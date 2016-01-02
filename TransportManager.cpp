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
    isStop = false;
    isNext = false;
    isPause = false;
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


bool   TransportManager::GetSerciceUrlControlRenderer()
{
        memset(urlControlRenderer,'\0',sizeof(urlControlRenderer));
        char * psz_url = vectorTool::get_value_of_arg(serviceRenderingControl.Dic,"controlURL");
        if(psz_url==NULL)
        {
            return false;
        }

        if(u.UrlBase[strlen(u.UrlBase)-1]=='/')
        {
            u.UrlBase[strlen(u.UrlBase)-1]='\0';
        }
        sprintf(urlControlRenderer,"%s%s",u.UrlBase,psz_url);
        return true;
}




bool  TransportManager::GetSerciceType()
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




bool  TransportManager::GetSerciceRendererType()
{
        memset(ServiceTypeRenderer,'\0',sizeof(ServiceTypeRenderer));
        char *Serv = vectorTool::get_value_of_arg(serviceRenderingControl.Dic,"serviceType");
        if(Serv==NULL)
        {
            return false;
        }
        else
        {
            strcpy(ServiceTypeRenderer,Serv);
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


UpnpListService TransportManager::GetServiceRenderingControl()
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
                          if(u.upnpListService[j].IsRenderingControl == true)
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


bool TransportManager::SetVolume(char  * vol)
 {
    std::vector<Dictionnaire> data;
    vectorTool::InsertOrModifyVector(data,"DesiredVolume",vol);  
    vectorTool::InsertOrModifyVector(data,"InstanceID",InstanceId); 
    bool resultat = UpnpActionFactory::GetInstance().CreateAction(actionSetVolumeRenderingControl,"SetVolume",(char*)urlControlRenderer,(char*)ServiceTypeRenderer,data,u.UrlBase); 
    return resultat;
 }

bool TransportManager::GetVolume()
 {
    std::vector<Dictionnaire> data;
    vectorTool::InsertOrModifyVector(data,"InstanceID",InstanceId);    
    bool resultat = UpnpActionFactory::GetInstance().CreateAction(actionGetVolumeRenderingControl,"GetVolume",(char*)urlControlRenderer,(char*)ServiceTypeRenderer,data,u.UrlBase); 
    return resultat;
 }



 bool TransportManager::PrepareNextUri(Dictionnaire * d)
 {
    std::vector<Dictionnaire> data;
    vectorTool::InsertOrModifyVector(data,"NextURI",d->Playurl);     
    bool resultat = UpnpActionFactory::GetInstance().CreateAction(actionSetNextUriAvTransportManager,"SetNextAVTransportURI",(char*)urlControl,(char*)ServiceType,data,u.UrlBase); 
    return resultat;
 }


 bool TransportManager::PrepareUri(Dictionnaire * d)
 {
    std::vector<Dictionnaire> data;
    vectorTool::InsertOrModifyVector(data,"CurrentURI",d->Playurl);     
    bool resultat = UpnpActionFactory::GetInstance().CreateAction(actionSetUriAvTransportManager,"SetAVTransportURI",(char*)urlControl,(char*)ServiceType,data,u.UrlBase); 
    return resultat;
 }
 
 bool TransportManager::Play()
 {
    std::vector<Dictionnaire> data;
    bool resultat = UpnpActionFactory::GetInstance().CreateAction(actionPlayAvTransportManager,"Play",(char*)urlControl,(char*)ServiceType,data,u.UrlBase);     
    return true;
 }

 bool TransportManager::Pause()
 {
    std::vector<Dictionnaire> data;
    vectorTool::InsertOrModifyVector(data,"InstanceID",InstanceId);  
    bool resultat = UpnpActionFactory::GetInstance().CreateAction(actionPauseAvTransportManager,"Pause",(char*)urlControl,(char*)ServiceType,data,u.UrlBase);     
    return true;
 }
 
 bool TransportManager::Stop()
 {
    std::vector<Dictionnaire> data;
    vectorTool::InsertOrModifyVector(data,"InstanceID",InstanceId);  
    
    bool resultat = UpnpActionFactory::GetInstance().CreateAction(actionStopAvTransportManager,"Stop",(char*)urlControl,(char*)ServiceType,data,u.UrlBase);     
    return resultat;
 }
 
  bool TransportManager::Next()
 {
    std::vector<Dictionnaire> data;
    vectorTool::InsertOrModifyVector(data,"InstanceID",InstanceId);  
    bool resultat = UpnpActionFactory::GetInstance().CreateAction(actionNextAvTransportManager,"Next",(char*)urlControl,(char*)ServiceType,data,u.UrlBase);     
    return resultat;
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
 
 
 
 UpnpListAction TransportManager::GetActionRenderingControl(char * ActionName)
 {
  UpnpListAction NulllistAction;
    try
    {
        
        NulllistAction.IdAction=-1;
        int indexAction = 0;
        for(int i=0;i<serviceRenderingControl.ListAction.size();i++)
        {
           char * actionName = vectorTool::get_value_of_arg(serviceRenderingControl.ListAction[i].Dic,"name");
           if(actionName == NULL)
           {
                  continue;
           }
           else
           {
            if(strcmp(actionName,ActionName)==0)
            {
               return serviceRenderingControl.ListAction[i];
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

char * TransportManager::GetIconPath()
{
    return u.Icon;
}


bool TransportManager::SetVolumeExt(char * vol)
{
    strcpy(volume,vol);
    return true;
}

char * TransportManager::GetVolumeExt()
{
    return volume;
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
            //qDebug() << "Service Connectoin Manager trouvé" << serviceConnectionManager.IdService;  
        }
    }
    strcpy(InstanceId,"0");
    
    
    serviceRenderingControl = GetServiceRenderingControl();
    
    
    
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
    
    
    //Get SetUri ACtion
    actionSetNextUriAvTransportManager = GetActionAvTransportManager("SetNextAVTransportURI");
  
    
    
    
    actionPlayAvTransportManager = GetActionAvTransportManager("Play");
    if(actionPlayAvTransportManager.IdAction == -1)
    {
      termine(rootIndex,false,deviceType);
      return;   
    }
   
    actionPauseAvTransportManager= GetActionAvTransportManager("Pause");
    if(actionPauseAvTransportManager.IdAction != -1)
    {
        if(actionPauseAvTransportManager.ListParametreAction.size()==0)
        {
          Dictionnaire d;
          d.name = new char[strlen("direction")+1];
          d.value = new char[strlen("in")+1];
          strcpy(d.name,"direction");
          strcpy(d.value,"in");
          Dictionnaire d1;
          d1.name = new char[strlen("name")+1];
          d1.value = new char[strlen("InstanceID")+1];
          strcpy(d1.name,"name");
          strcpy(d1.value,"InstanceID");
          UpnpListParametreAction ListParametreAction;
          ListParametreAction.Dic.push_back(d);
          ListParametreAction.Dic.push_back(d1);
          actionPauseAvTransportManager.ListParametreAction.push_back(ListParametreAction);
        }
        isPause = true; 
    }
    
    
    actionStopAvTransportManager= GetActionAvTransportManager("Stop");
    if(actionStopAvTransportManager.IdAction != -1)
    {
        if(actionStopAvTransportManager.ListParametreAction.size()==0)
        {
          Dictionnaire d;
          d.name = new char[strlen("direction")+1];
          d.value = new char[strlen("in")+1];
          strcpy(d.name,"direction");
          strcpy(d.value,"in");
          Dictionnaire d1;
          d1.name = new char[strlen("name")+1];
          d1.value = new char[strlen("InstanceID")+1];
          strcpy(d1.name,"name");
          strcpy(d1.value,"InstanceID");
          UpnpListParametreAction ListParametreAction;
          ListParametreAction.Dic.push_back(d);
          ListParametreAction.Dic.push_back(d1);
          actionStopAvTransportManager.ListParametreAction.push_back(ListParametreAction);
        }
        
        isStop = true;
    }
    
    actionNextAvTransportManager= GetActionAvTransportManager("Next");
    if(actionNextAvTransportManager.IdAction != -1)
    {
         if(actionNextAvTransportManager.ListParametreAction.size()==0)
        {
          Dictionnaire d;
          d.name = new char[strlen("direction")+1];
          d.value = new char[strlen("in")+1];
          strcpy(d.name,"direction");
          strcpy(d.value,"in");
          Dictionnaire d1;
          d1.name = new char[strlen("name")+1];
          d1.value = new char[strlen("InstanceID")+1];
          strcpy(d1.name,"name");
          strcpy(d1.value,"InstanceID");
          UpnpListParametreAction ListParametreAction;
          ListParametreAction.Dic.push_back(d);
          ListParametreAction.Dic.push_back(d1);
          actionNextAvTransportManager.ListParametreAction.push_back(ListParametreAction);
        }
        isNext = true;   
    }
    
    actionSetVolumeRenderingControl= GetActionRenderingControl("SetVolume");
    if(actionSetVolumeRenderingControl.IdAction != -1)
    {
        qDebug() << "Volume ok";
    }
    
    
    
    
   
    //qDebug() << "Url de control trouvé" << urlControl;  
    
    //Service type
    if(GetSerciceRendererType()==true)
    {
        if(GetSerciceUrlControlRenderer()==true)
        {
           actionGetVolumeRenderingControl= GetActionRenderingControl("GetVolume");
            {
                GetVolume();
                char * vol =vectorTool::get_value_of_arg(actionGetVolumeRenderingControl.DicReponse,"CurrentVolume");
                if(vol!=NULL)
                {
                    strcpy(volume,vol);
                    qDebug() << "Volume ok : " << vol;
                }
            }  
        }
    }
    
   
    
    
    //Url de controle
    if(GetSerciceUrlControl()== false)
    {
      termine(rootIndex,false,deviceType);
      return;       
    }
    //qDebug() << "Url de control trouvé" << urlControl;  
    
    //Service type
    if(GetSerciceType()==false)
    {
      termine(rootIndex,false,deviceType);
      return;    
    }
    //qDebug() << "Service type trouvé" << ServiceType;  
    //
    
    
  
    termine(rootIndex,true,deviceType);
}