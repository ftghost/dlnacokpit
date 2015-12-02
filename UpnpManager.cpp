/* 
 * File:   UpnpManager.cpp
 * Author: ghost
 * 
 * Created on 26 juillet 2015, 16:23
 */

#include "UpnpManager.h"
#include <cstddef>
#include "htmlTool.h"
#include "xmlTool.h"
#include "vectorTool.h"
#include "UpnpDiscover.h"
#include <stdio.h>
#include <string.h>
#include <vector>
#include <QDebug>



UpnpManager UpnpManager::m_instance=UpnpManager();
pthread_mutex_t UpnpManager::mutexManager;

UpnpManager::UpnpManager() 
{

}

 UpnpRoot UpnpManager::GetStructureDeviceByIndex(int index)
 {
    
    UpnpRoot u ;
    u.idRoot = -1;
    int a =-1;
    for (int i=0; i< UpnpServiceArray.size() ;i++)
    {
        if(UpnpServiceArray[i].idRoot == index)
        {
            a=i;
            break;
        }
    }
    if(a==-1)
    {
        return u;
    }
    return UpnpServiceArray[a];
 }
 
 
 
 

bool UpnpManager::WriteInfoService(UpnpRoot *uStruct)
{
    return true;
    for(int i = 0;i< uStruct->upnpListDevice.size();i++)
    {
        int device = uStruct->upnpListDevice[i].IdDevice;
        for(int j = 0 ; j< uStruct->upnpListDevice[i].Dic.size();j++)
        {
            char tmp[500];
            memset(tmp,'\0',sizeof(tmp));
            sprintf(tmp,"Device numero : %d -------- InfoName : %s , InfoValue : %s",device,uStruct->upnpListDevice[i].Dic[j].name,uStruct->upnpListDevice[i].Dic[j].value);  
        }
    }

      if(uStruct->upnpListIcon.empty()==false)
      {
         for(int i = 0;i< uStruct->upnpListIcon.size();i++)
          {  
            for(int j = 0 ; j< uStruct->upnpListIcon[i].Dic.size();j++)
            {
                char tmp[500];
                memset(tmp,'\0',sizeof(tmp));
                sprintf(tmp,"Device numero : %d  , Icon numero : %d-------- InfoName : %s , InfoValue : %s",uStruct->upnpListIcon[i].IdDevice,uStruct->upnpListIcon[i].IdIcon,uStruct->upnpListIcon[i].Dic[j].name,uStruct->upnpListIcon[i].Dic[j].value);  
            }
         }
      }
    
        if(uStruct->upnpListService.empty()==false)     //Get urlbase
        {
            for(int i = 0;i< uStruct->upnpListService.size();i++)
            {
               
                for(int j = 0 ; j< uStruct->upnpListService[i].Dic.size();j++)
                {
                    char tmp[500];
                    memset(tmp,'\0',sizeof(tmp));
                    sprintf(tmp,"Device numero : %d  , Service numero : %d-------- InfoName : %s , InfoValue : %s",uStruct->upnpListService[i].IdDevice,uStruct->upnpListService[i].IdService,uStruct->upnpListService[i].Dic[j].name,uStruct->upnpListService[i].Dic[j].value);  
                }
                    if(uStruct->upnpListService[i].ListAction.empty()==false)
                    {
                        for(int k = 0 ; k< uStruct->upnpListService[i].ListAction.size();k++)
                        {
                            for(int l =0 ; l<uStruct->upnpListService[i].ListAction[k].Dic.size();l++)
                            {
                                char tmp[500];
                                memset(tmp,'\0',sizeof(tmp));
                                sprintf(tmp,"Device numero : %d  , Service numero : %d , Action numero : %d-------- InfoName : %s , InfoValue : %s",uStruct->upnpListService[i].ListAction[k].IdDevice,
                                uStruct->upnpListService[i].ListAction[k].IdService,uStruct->upnpListService[i].ListAction[k].IdAction,uStruct->upnpListService[i].ListAction[k].Dic[l].name,
                                uStruct->upnpListService[i].ListAction[k].Dic[l].value);
                            }
                            
                            if(uStruct->upnpListService[i].ListAction[k].ListParametreAction.empty()==false)
                            {
                                for(int m = 0;m<uStruct->upnpListService[i].ListAction[k].ListParametreAction.size();m++)
                                {
                                   for(int l =0 ; l<uStruct->upnpListService[i].ListAction[k].ListParametreAction[m].Dic.size();l++)
                                    {
                                        char tmp[500];
                                        memset(tmp,'\0',sizeof(tmp));
                                        sprintf(tmp,"Device numero : %d  , Service numero : %d , Action numero : %d , parametre Numero %d-------- InfoName : %s , InfoValue : %s",uStruct->upnpListService[i].ListAction[k].IdDevice,
                                        uStruct->upnpListService[i].ListAction[k].ListParametreAction[m].IdService,uStruct->upnpListService[i].ListAction[k].ListParametreAction[m].IdAction,
                                        uStruct->upnpListService[i].ListAction[k].ListParametreAction[m].IdParametre,uStruct->upnpListService[i].ListAction[k].ListParametreAction[m].Dic[l].name, 
                                        uStruct->upnpListService[i].ListAction[k].ListParametreAction[m].Dic[l].value);
                                    }  
                                   
                                    for(int l =0 ; l<uStruct->upnpListService[i].ListAction[k].ListParametreAction[m].DicEtat.size();l++)
                                    {
                                        
                                        char tmp[500];
                                        memset(tmp,'\0',sizeof(tmp));
                                        sprintf(tmp,"Device numero : %d  , Service numero : %d , Action numero : %d , parametre Numero %d-------- InfoName : %s , InfoValue : %s",uStruct->upnpListService[i].ListAction[k].IdDevice,
                                        uStruct->upnpListService[i].ListAction[k].ListParametreAction[m].IdService,uStruct->upnpListService[i].ListAction[k].ListParametreAction[m].IdAction,
                                        uStruct->upnpListService[i].ListAction[k].ListParametreAction[m].IdParametre,uStruct->upnpListService[i].ListAction[k].ListParametreAction[m].DicEtat[l].name, 
                                        uStruct->upnpListService[i].ListAction[k].ListParametreAction[m].DicEtat[l].value);
                                    }
                                   
                                }
                            }
                        }
                    }
            }
        }
}


char * UpnpManager::RemoveDevice(Upnp_Discovery * uDiscover)
{
    char * Name =NULL;
     if(uDiscover != NULL)
     {
        for (std::vector<UpnpRoot>::iterator it = UpnpServiceArray.begin() ; it != UpnpServiceArray.end(); ++it)
        {
           if(strcmp(uDiscover->DeviceId,it->u->DeviceId)==0)
           {
               Name = vectorTool::get_value_of_arg(it->upnpListDevice[0].Dic,"friendlyName"); 
               UpnpServiceArray.erase(it);
               break;
           } 
        }
     }
     return Name;
}


std::vector< std::vector<Dictionnaire> >  UpnpManager::ParseAndAddActionParameters(std::vector<UpnpListAction>  ListAction,std::vector< std::vector<Dictionnaire> > dic)
 {
     bool all = false;
     std::vector< std::vector<Dictionnaire> > retour;
     int count=0;
     for(int i=0;i<ListAction.size();i++)
     {
         for(int j=0;j<ListAction[i].ListParametreAction.size();j++)
         {
             char * ArgName = vectorTool::get_value_of_arg(ListAction[i].ListParametreAction[j].Dic,"relatedStateVariable"); 
             all = false;
             for(int k=0;k<dic.size();k++)
             {
                 for(int l =0; l<dic[k].size();l++)
                 {
                    char * Name = dic[k][l].value;
                    if(Name != NULL)
                    {
                        if(strcmp(Name,ArgName)==0)
                        {
                            for(int count =0;count<dic[k].size();count++)
                            {
                                if(dic[k][count].name != NULL && dic[k][count].value!=NULL)
                                {
                                    Dictionnaire d;
                                    d.name = new char[strlen(dic[k][count].name)+1];
                                    d.value = new char[strlen(dic[k][count].value)+1];
                                    strcpy(d.name,dic[k][count].name);
                                    strcpy(d.value,dic[k][count].value);
                                    retour[count].push_back(d);
                                    count++;
                                }
                            }
                            
                            all=true;
                            break;
                        }
                    }
                 }
             }
         }
     }
     return retour;
 }

bool UpnpManager::ParseAndAddServiceAction(UpnpListService *ListService)
{
    std::vector<Dictionnaire> dict= xmlTool::get_list_arg_value(ListService->xmlDocAction,"actionList","");
    std::vector< std::vector<Dictionnaire> > listDict = vectorTool::strip_xml_arg(dict,"name");
    int idaction = 0;
    int IdParametre =0;
    bool ReadyToParseArg = false;
    for(int i=0;i<listDict.size();i++)
    {
        if(listDict[i].size() == 1)
        {
            ReadyToParseArg = true;
            UpnpListAction upnpListAction;
            upnpListAction.IdAction = idaction;
            upnpListAction.IdService = ListService->IdService;
            upnpListAction.IdDevice = ListService->IdDevice;
            upnpListAction.Dic.push_back(listDict[i][0]);
            ListService->ListAction.push_back(upnpListAction);
            idaction++;
            IdParametre = 0;
        }
        else
        {
            if(ReadyToParseArg == true)
            {
                
                if(vectorTool::count_number_of_arg(listDict[i],"relatedStateVariable")==1)
                {
                   UpnpListParametreAction upnpListParametreAction;
                   upnpListParametreAction.IdParametre = IdParametre;
                   upnpListParametreAction.IdDevice = ListService->IdDevice;
                   upnpListParametreAction.IdService = ListService->IdService;
                   upnpListParametreAction.IdAction = idaction-1;       
                   for(int j=0;j<listDict[i].size();j++)
                   {
                        upnpListParametreAction.Dic.push_back(listDict[i][j]);
                   }
                   ListService->ListAction[upnpListParametreAction.IdAction].ListParametreAction.push_back(upnpListParametreAction);
                   IdParametre++;
                }
                else
                {
                    ReadyToParseArg = false;
                }
            }
        }
    }
    
    std::vector<Dictionnaire> dictState= xmlTool::get_list_arg_value(ListService->xmlDocAction,"serviceStateTable","");
    std::vector< std::vector<Dictionnaire> > listDictState = vectorTool::strip_xml_arg(dictState,"name");
     
     for(int i=0;i<ListService->ListAction.size();i++)
     {
         for(int j=0;j<ListService->ListAction[i].ListParametreAction.size();j++)
         {
             char * ArgName = vectorTool::get_value_of_arg(ListService->ListAction[i].ListParametreAction[j].Dic,"relatedStateVariable"); 
             for(int k=0;k<listDictState.size();k++)
             {
                 for(int l =0; l<listDictState[k].size();l++)
                 {
                    char * Name = listDictState[k][l].value;
                    if(Name != NULL && ArgName!=NULL)
                    {
                        if(strcmp(Name,ArgName)==0)
                        {
                            for(int count =0;count<listDictState[k].size();count++)
                            {
                                if(listDictState[k][count].name != NULL && listDictState[k][count].value!=NULL)
                                {
                                    Dictionnaire d;
                                    d.name = new char[strlen(listDictState[k][count].name)+1];
                                    d.value = new char[strlen(listDictState[k][count].value)+1];
                                    strcpy(d.name,listDictState[k][count].name);
                                    strcpy(d.value,listDictState[k][count].value);
                                    ListService->ListAction[i].ListParametreAction[j].DicEtat.push_back(d);
                                }
                            }
                            break;
                        }
                    }
                 }
             }
         }
     }
    return true;
}


 bool UpnpManager::ParseAndAddDevice(std::vector<Dictionnaire> dict , UpnpRoot *uStruct)
 {
     int nbDevice = vectorTool::count_number_of_arg(dict,"deviceType");
     if(nbDevice <=0)
     {
         return false;
     }
     
     //Get device
     std::vector< std::vector<Dictionnaire> > deviceArray = vectorTool::strip_xml_arg(dict,"deviceType");
     long l = deviceArray.size();
     if(l != nbDevice )
     {
         return false;
     }
     //Parcours and parse device
     for(int i = 0;i<l;i++)
     {
         //Add device to root;
         UpnpListDevice upnpListDevice;
         upnpListDevice.IdDevice = i;
         upnpListDevice.Dic = deviceArray[i];
         //Get and Add device type
         char * deviceType = vectorTool::get_value_of_arg(upnpListDevice.Dic,"deviceType");
         if(deviceType != 0)
         {
            qDebug() << "Device type " <<  deviceType;
            char *pch = strstr (deviceType,"MediaServer");
            if(pch!=NULL)
            {
                upnpListDevice.Isreader = false;
                upnpListDevice.IsUnknow = false;
            }
            else
            {
                pch = strstr (deviceType,"MediaRenderer");
                if(pch!=NULL)
                {
                    upnpListDevice.Isreader = true;
                    upnpListDevice.IsUnknow = false;
                }
                else
                {
                    upnpListDevice.IsUnknow = true;
                }
            }
            uStruct->upnpListDevice.push_back(upnpListDevice);
         }
         else
         {
             return false;
         }
         //Get and Add icon information
         nbDevice = vectorTool::count_number_of_arg(dict,"mimetype");
         if(nbDevice !=0)
         {
             std::vector< std::vector<Dictionnaire> > iconArray = vectorTool::strip_xml_arg(dict,"mimetype");
             for(int j=0;j<iconArray.size();j++)
             {
                 UpnpListIcon upnpListIcon;
                 upnpListIcon.IdDevice = i;
                 upnpListIcon.IdIcon = j;
                 upnpListIcon.Dic = iconArray[j];
                 uStruct->upnpListIcon.push_back(upnpListIcon);
             }
         }
         
         //Get and Add service information
         nbDevice = vectorTool::count_number_of_arg(dict,"serviceType");
         if(nbDevice !=0)    
         {
             std::vector< std::vector<Dictionnaire> > serviceArray = vectorTool::strip_xml_arg(dict,"serviceType");
             for(int k=0;k<serviceArray.size();k++)
             {
                 UpnpListService upnpListService;
                 
                 upnpListService.IdDevice = i;
                 upnpListService.IdService = k;
                 upnpListService.Dic = serviceArray[k];
                 //GetType Of service
                 char * ServiceType = vectorTool::get_value_of_arg(upnpListService.Dic,"serviceType");
                 qDebug() << "Service type " <<  ServiceType;
                 char *pch = strstr (ServiceType,"RenderingControl");
                 if(pch!=NULL)
                 {
                    upnpListService.IsConnectionManager = false; 
                    upnpListService.IsRenderingControl = true;
                    upnpListService.IsContentDirectory = false;
                    upnpListService.IsAvTransport = false;
                    upnpListService.IsUnknow = false;
                    qDebug() << "SIsRenderingControl" ;
                 }
                 else
                 {
                    pch = strstr (ServiceType,"AVTransport");
                    if(pch!=NULL)
                    {
                        upnpListService.IsConnectionManager = false;
                        upnpListService.IsRenderingControl = false;
                        upnpListService.IsContentDirectory = false;
                        upnpListService.IsAvTransport = true;
                        upnpListService.IsUnknow = false;
                        qDebug() << "SISAVTransport" ;
                    }
                    else
                    {
                        pch = strstr (ServiceType,"ContentDirectory");
                         if(pch!=NULL)
                        {
                            upnpListService.IsConnectionManager = false; 
                            upnpListService.IsRenderingControl = false;
                            upnpListService.IsContentDirectory = true;
                            upnpListService.IsAvTransport = false;
                            upnpListService.IsUnknow = false;
                            qDebug() << "SISContentDirectory" ;
                        }
                        else
                        {
                            pch = strstr (ServiceType,"ConnectionManager"); 
                             if(pch!=NULL)
                            {
                                upnpListService.IsConnectionManager = true; 
                                upnpListService.IsRenderingControl = false;
                                upnpListService.IsContentDirectory = false;
                                upnpListService.IsAvTransport = false;
                                upnpListService.IsUnknow = false;
                                qDebug() << "SISConnectionManager" ;
                            }
                            else
                            {
                            upnpListService.IsConnectionManager = false;            
                            upnpListService.IsRenderingControl = false;
                            upnpListService.IsContentDirectory = false;
                            upnpListService.IsAvTransport = false;
                            upnpListService.IsUnknow = true;     
                            qDebug() << "SIIsUnknow" ;
                            }
                        }
                             
                    }
                }
                 //Get list of action    
                 char add[250];
                 memset(add,'\0',sizeof(add));
                 char * SCPDURL =   vectorTool::get_value_of_arg(upnpListService.Dic,"SCPDURL"); 
                 sprintf(add,"%s%s",uStruct->UrlBase,SCPDURL);
                 if(UpnpDownloadXmlDoc(add,&upnpListService.xmlDocAction)== UPNP_E_SUCCESS)
                 {
                    //Parse action
                    ParseAndAddServiceAction(&upnpListService);
                    //Subscribe to service
                    upnpListService.Subscribe_time = 3600;
                    memset(add,'\0',sizeof(add));
                    char *eventSubUrl = vectorTool::get_value_of_arg(upnpListService.Dic,"eventSubURL");
                    sprintf(add,"%s%s",uStruct->UrlBase,eventSubUrl);
                    //CAppLogger::Instance().Log(eventSubUrl, Poco::Message::PRIO_DEBUG);  
                    int retval = UpnpSubscribe(UpnpDiscover::GetInstance().GetHandle(),add,&upnpListService.Subscribe_time, upnpListService.SubsId);
                    if(retval == UPNP_E_SUCCESS)
                    {
                       upnpListService.Subscribe = true; 
                    }
                    else
                    {
                        upnpListService.Subscribe = false; 
                    }
                 }
                 else
                 {
                    upnpListService.Subscribe = false;     
                 }
                 
                 //Download icon 
                  if(uStruct->upnpListIcon.empty() == false)
                  {
                      for(int nbIcon=0;nbIcon<uStruct->upnpListIcon.size();nbIcon++)
                      {
                        char * realIconName = vectorTool::get_value_of_arg(uStruct->upnpListDevice[i].Dic,"friendlyName");    
                        char * size = vectorTool::get_value_of_arg(uStruct->upnpListIcon[nbIcon].Dic,"width");  
                        if(strcmp(size,"48")==0)
                        {
                            char * iconName= vectorTool::get_value_of_arg(uStruct->upnpListIcon[nbIcon].Dic,"url");
                            if(iconName != NULL)
                            {
                                char save[500];
                                memset(save,'\0',500);
                                memset(uStruct->Icon,'\0',100);
                                char * mimeType= vectorTool::get_value_of_arg(uStruct->upnpListIcon[nbIcon].Dic,"mimetype");
                                if(strcmp(mimeType,"image/jpeg")==0)
                                {
                                    sprintf(save,"./html/%s.jpeg",realIconName);
                                    sprintf(uStruct->Icon,"%s.jpeg",realIconName);
                                }
                                else  if(strcmp(mimeType,"image/png")==0)
                                {
                                   sprintf(save,"./html/%s.png",realIconName);
                                   sprintf(uStruct->Icon,"%s.png",realIconName);
                                }
                                else
                                {
                                    sprintf(save,"./html/%s.png",realIconName);
                                    sprintf(uStruct->Icon,"f%s.png",realIconName);
                                }
                                
                                            
                               sprintf(uStruct->Icon,"%s%s",uStruct->UrlBase,iconName);           
                                
                                strcpy(uStruct->PathIcon,save);
                                if(htmlTool::downloadAndSave(uStruct->UrlBase,iconName,save) == true)
                                {
                                    uStruct->icon = true;
                                }
                                else
                                {
                                    uStruct->icon = false;  
                                }
                            }
                            break;
                        }
                      }
                  }
                 
                 uStruct->upnpListService.push_back(upnpListService);
             }
         }         
     }
     return true;
 }


 UpnpRoot UpnpManager::AddDevice(Upnp_Discovery * uDiscover)
 {
     pthread_mutex_lock(&mutexManager);
     UpnpRoot uStruct;
     uStruct.idRoot = -1;
     int ret = -1;
     bool exist = true;
     if(uDiscover != NULL)
     {
        exist = false; 
        if(strlen(uDiscover->DeviceId) > 0)
        {
            for(int i=0; i<UpnpServiceArray.size();i++)
            {
                if(strcmp(uDiscover->DeviceId,UpnpServiceArray[i].u->DeviceId)==0)
                {
                    exist = true;
                    ret = -1;
                }
            }
        }
     }
     if(exist==false)
     {
         ret = UpnpServiceArray.size();
         uStruct.idRoot = ret;
         uStruct.u = new Upnp_Discovery();
         *uStruct.u = *uDiscover;
         if(UpnpDownloadXmlDoc(uDiscover->Location,&uStruct.xmlDoc)== UPNP_E_SUCCESS)
         {
            std::vector<Dictionnaire> tmp1 = xmlTool::get_list_arg_value(uStruct.xmlDoc,"URLBase",""); 
            if(tmp1.empty())
            {
              char s=':';
              int ii=0;
              int trouveSlash = 0;
              for(int i =0; i<strlen(uStruct.u->Location); i++)
              {
                  if(uStruct.u->Location[i]==s)
                  {
                          s='/';
                  }
                  if(uStruct.u->Location[i]==s)
                  {
                      trouveSlash++;
                      if(trouveSlash == 3)
                      {
                        ii = i;  
                        break;
                      }
                  }
                   
              }
              uStruct.UrlBase = new char[ii+1];
              memset(uStruct.UrlBase,'\0',ii+1);
              strncpy(uStruct.UrlBase,uStruct.u->Location,ii);
            }
            else
            {
                uStruct.UrlBase = vectorTool::get_value_of_arg(tmp1,"URLBase");
            }
            
            std::vector<Dictionnaire> tmp = xmlTool::get_list_arg_value(uStruct.xmlDoc,"device","");
            ParseAndAddDevice(tmp,&uStruct);
            UpnpServiceArray.push_back(uStruct);
            //WriteInfoService(&uStruct);
         }
         else
         {
             ret = -1;
         }
     }
     pthread_mutex_unlock(&mutexManager);
     return uStruct;;
 }



UpnpManager & UpnpManager::GetInstance()
{
  return m_instance;
}

UpnpManager::~UpnpManager()
{
    
}

