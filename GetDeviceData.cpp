/* 
 * File:   GetDeviceData.cpp
 * Author: ghost
 * 
 * Created on 31 octobre 2015, 10:42
 */

#include "GetDeviceData.h"
#include "UpnpManager.h"
#include "UpnpActionFactory.h"
#include "vectorTool.h"
#include "xmlTool.h"
#include <QDebug>
#include "DataManager.h"

GetDeviceData::GetDeviceData(int index) 
{
    rootIndex = index;
}

GetDeviceData::GetDeviceData(const GetDeviceData& orig) {
}

GetDeviceData::~GetDeviceData() {
}


std::vector<Dictionnaire>  GetDeviceData::GetNexttData(Dictionnaire resPre)
{
        std::vector<Dictionnaire> res;   
        std::vector<Dictionnaire> data;
        int index =0;
        int startingIndex = 0 ;
        char buffer [50];
        sprintf(buffer,"%d",startingIndex);
        vectorTool::InsertOrModifyVector(data,"StartingIndex",buffer);  
        if(resPre.IsItem == true)
        {
            return res;
        }
        else
        {
            {
                vectorTool::InsertOrModifyVector(data,"ObjectID",resPre.id);  
                bool cont = true;
                while(cont==true)
                {

                    bool resulttat = UpnpActionFactory::GetInstance().CreateAction(actionBrowseDirectory,"Browse",(char*)urlControl,(char*)ServiceType,data,u.UrlBase);
                    char * XmlResult = vectorTool::get_value_of_arg(actionBrowseDirectory.DicReponse,"Result");
                    qDebug() << "XmlResult : " <<  XmlResult;
                    std::vector<Dictionnaire> res1 = xmlTool::get_list_arg_value_by_char(XmlResult,"title","");
                    if(res1.size() > 0)
                    {
                        res.insert(res.end(), res1.begin(), res1.end());
                        startingIndex = startingIndex+1;
                        sprintf(buffer,"%d",startingIndex);
                        qDebug() << "Index : " <<  buffer;
                        vectorTool::InsertOrModifyVector(data,"StartingIndex",buffer);  
                        res1.clear();
                        res1.swap(res1);
                    }
                    else
                    {
                        cont = false;
                    }
                }
            }
        }
        data.clear();
        data.swap(data);
    return res;
}



std::vector<Dictionnaire>  GetDeviceData::GetRootData()
{
    std::vector<Dictionnaire> res;   
    std::vector<Dictionnaire> data;
    int index =0;
    int startingIndex = 0 ;
    char buffer [50];
    sprintf(buffer,"%d",startingIndex);
    vectorTool::InsertOrModifyVector(data,"StartingIndex",buffer);  
    
   bool cont = true;
   while(cont==true)
   {
        bool resulttat = UpnpActionFactory::GetInstance().CreateAction(actionBrowseDirectory,"Browse",(char*)urlControl,(char*)ServiceType,data,u.UrlBase);
        char * XmlResult = vectorTool::get_value_of_arg(actionBrowseDirectory.DicReponse,"Result");
        qDebug() << "XmlResult : " <<  XmlResult;
        std::vector<Dictionnaire> res1 = xmlTool::get_list_arg_value_by_char(XmlResult,"title","");
        if(res1.size() > 0)
        {
            res.insert(res.end(), res1.begin(), res1.end());
            startingIndex = startingIndex+1;
            sprintf(buffer,"%d",startingIndex);
            vectorTool::InsertOrModifyVector(data,"StartingIndex",buffer);  
            res1.clear();
            res1.swap(res1);
        }
        else
        {
            res1.clear();
            res1.swap(res1);
            cont  = false;
        }
    }
    data.clear();
    data.swap(data);
    
    return res;
}

UpnpListService GetDeviceData::GetServiceContentDirectory()
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
                          if(u.upnpListService[j].IsContentDirectory == true)
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

UpnpListAction GetDeviceData::GetActionContentDirectory(char *ActionName)
{
    UpnpListAction NulllistAction;
    try
    {
        
        NulllistAction.IdAction=-1;
        int indexAction = 0;
        for(int i=0;i<serviceContentDirectory.ListAction.size();i++)
        {
           char * actionName = vectorTool::get_value_of_arg(serviceContentDirectory.ListAction[i].Dic,"name");
           if(actionName == NULL)
           {
                  continue;
           }
           else
           {
            if(strcmp(actionName,ActionName)==0)
            {
               return serviceContentDirectory.ListAction[i];
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

bool   GetDeviceData::GetSerciceUrlControl()
{
        memset(urlControl,'\0',sizeof(urlControl));
        char * psz_url = vectorTool::get_value_of_arg(serviceContentDirectory.Dic,"controlURL");
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

bool   GetDeviceData::GetSerciceType()
{
        memset(ServiceType,'\0',sizeof(ServiceType));
        char *Serv = vectorTool::get_value_of_arg(serviceContentDirectory.Dic,"serviceType");
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


UpnpListService GetDeviceData::GetServiceConnectionManager()
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

UpnpListAction GetDeviceData::GetActionConnectionManager(char * ActionName)
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


void GetDeviceData::run()
{
    bool deviceType = true;
    //Root
    u = UpnpManager::GetInstance().GetStructureDeviceByIndex(rootIndex);
    if(u.idRoot ==-1) 
    {
      termine(rootIndex,false,deviceType);
      return;
    }
    //Service
    serviceContentDirectory = GetServiceContentDirectory();
    if(serviceContentDirectory.IdService==-1)
    {
      termine(rootIndex,false,deviceType);
      return;
    }
    qDebug() << "Service content Directory trouvé" << serviceContentDirectory.IdService;  
    
    serviceConnectionManager = GetServiceConnectionManager();

    if(serviceConnectionManager.IdService==-1)
    {
      termine(rootIndex,false,deviceType);
      return;
    }
    qDebug() << "Service Connectoin Manager trouvé" << serviceConnectionManager.IdService;  
    
    
    
    //Action
    actionBrowseDirectory = GetActionContentDirectory("Browse");
    if(actionBrowseDirectory.IdAction==-1)
    {
      termine(rootIndex,false,deviceType);
      return;
    }
    qDebug() << "Action browse content Directory Service trouvé" << actionBrowseDirectory.IdAction;
    
    actionConnectionManager = GetActionConnectionManager("PrepareForConnection");
    if(actionConnectionManager.IdAction==-1)
    {
        strcpy(InstanceId,"0");
    }
    else
    {
        //TODO CALL PrepareForConnection
        strcpy(InstanceId,"0");
    }
    qDebug() << "Action browse content Directory Service trouvé" << actionBrowseDirectory.IdAction;
    
    
    //Url de controle#include "ChainedData.h"
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
    
    
    bool Init = false;
    std::vector<Dictionnaire> res;
    std::vector<Dictionnaire> resRoot = GetRootData();
    std::vector<Dictionnaire> resArstist;
    for(int i=0;i<resRoot.size();i++)
    {
        qDebug() << "Name " << resRoot[i].name <<" Value " <<resRoot[i].value;
        if(strcmp(resRoot[i].value,"Audio") == 0  )
        {
            res=GetNexttData(resRoot[i]);
            for(int j=0;j<res.size();j++)
            {
              qDebug() << "Name " << res[j].name <<" Value " <<res[j].value;  
              if(strcmp(res[j].value,"Artists") == 0 )
              {
                  resArstist=GetNexttData(res[j]);
                  for(int j=0;j<resArstist.size();j++)
                  {
                      qDebug() << "Arstist Name " << resArstist[j].name <<" Value " <<resArstist[j].value; 
                      DataManager::GetInstance().AddDataToList(&resArstist[j]);
                      std::vector<Dictionnaire> res2=GetNexttData(resArstist[j]);
                      for(int k=0;k<res2.size();k++)
                      {
                        qDebug() << "Album Name " << res2[k].value ;
                        if(strcmp("All - full name",res2[k].value)!=0 && strcmp("All Songs",res2[k].value)!=0)
                        {
                            DataManager::GetInstance().AddAlbumToList(&res2[k],resArstist[i].value);
                            std::vector<Dictionnaire> res3=GetNexttData(res2[k]);
                            for(int l=0;l<res3.size();l++)
                            {
                                DataManager::GetInstance().AddTrackToList(&res3[l],res2[k].value);
                                qDebug() << "Add track : " <<  res3[l].value << " to Album Name :" << res2[k].value ;
                                 Init = true;
                            }
                            res3.clear();
                            res3.swap(res3);
                        }
                      }
                      res2.clear();
                      res2.swap(res2);
                  }
                  resArstist.clear();
                  resArstist.swap(resArstist);
              }
            }
        }
    }
    resRoot.clear();
    resRoot.swap(resRoot);
    if( Init == true)
        termine(rootIndex,true,deviceType);
    else
        termine(rootIndex,false,deviceType);
}