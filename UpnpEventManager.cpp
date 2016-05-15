/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UpnpEventManager.cpp
 * Author: ghost
 * 
 * Created on 4 janvier 2016, 18:50
 */

#include "UpnpEventManager.h"
#include "UpnpManager.h"
#include "DataManager.h"
#include "congig.h"
#include "xmlTool.h"
#include <QDebug>
#include <qt4/QtCore/qstring.h>

UpnpEventManager UpnpEventManager::m_instance=UpnpEventManager();

UpnpEventManager & UpnpEventManager::GetInstance()
{
  return m_instance;
}


UpnpEventManager::UpnpEventManager()
{
    
}



UpnpEventManager::~UpnpEventManager()
{

}


bool UpnpEventManager::SetEvent(Upnp_Event * myEvent)
{
    e_event = myEvent;
    qDebug() << "Event set";
    return true;
}

bool UpnpEventManager::SetSelected(int index)
{
   SelectedIndex = index;
   qDebug() << "Index set";
   return true;
}

bool UpnpEventManager::SetNextUriSet(bool nextUri)
{
    NextUriSet = nextUri;
}

bool UpnpEventManager::SetDataMangerStopped(bool dataMangerStopped )
{
    IsDataMangerStopped = dataMangerStopped;
}




bool UpnpEventManager::Run()
{
    //Get ssid
    bool traite = false;
    UpnpRoot u = UpnpManager::GetInstance().GetStructureDeviceByIndex(SelectedIndex);
    qDebug() << "u.idRoot : " << u.idRoot;
    if(u.idRoot ==-1) 
        return false;
    for(int i=0;i<u.upnpListService.size();i++)
    {
        qDebug() << "u.upnpListService[i].SubsId : " << u.upnpListService[i].SubsId << " &&& " << e_event->Sid;
        if(strcmp(u.upnpListService[i].SubsId,e_event->Sid)==0)
        {
           traite = true; 
           break;
        }
    }
    
    if(traite==false) return false;
    char * Sta =NULL;
    char * inf=NULL;
    inf = xmlTool::get_argument_value( e_event->ChangedVariables,"LastChange");
    Sta = xmlTool::get_VolumeChange(inf);
    if(Sta != NULL)
    {
        qDebug() << "traite true" << " sequence number : " << e_event->EventKey << " Volume : " << Sta;
        DataManager::GetInstance().UpdateVolume(Sta);
        delete Sta;
        Sta=NULL;
    }
    
    Sta = xmlTool::get_lastChange(inf);
    if(Sta != NULL)
    {
        QString str = QString::fromUtf8(Sta);
        qDebug() << "traite true" << " sequence number : " << e_event->EventKey << " LastChange : " << str;
        if(str==STOPPED && IsDataMangerStopped==true) IsStopped = true;
        
        if(str==PLAYING && IsStopped == true)
        {
            IsStopped = false;
            DataManager::GetInstance().SetSameUri();
        }
        else if(str==PLAYING )
        {
           IsStopped = false; 
           DataManager::GetInstance().updateInfo(); 
           DataManager::GetInstance().SetNextUri() ; 
        }
        else if((str==NO_MEDIA_PRESENT ||str==STOPPED)  &&  IsStopped == false)
        {
           DataManager::GetInstance().PlayAndSetUri() ;  
           qDebug() << "PlayAndSetUri";
        }
        delete Sta;
    }
    
    return true;
}