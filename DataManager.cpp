#include "DataManager.h"
#include "UpnpManager.h"
#include <QDebug>




DataManager DataManager::m_instance=DataManager();


DataManager & DataManager::GetInstance()
{
  return m_instance;
}


DataManager::DataManager()
{
    NewData = true;
    ready = false;
    LecteurReady = false;
}



DataManager::~DataManager()
{

}


void DataManager::parseTermine(int index,bool isOk,bool deviceType)
{
  QThread::sleep ( 1 );  
  if(isOk==false)
  {
    if(deviceType == false)  
        delete getDeviceTransport[index];  
    if(deviceType == true)     
        delete getDeviceData[index];  
  }
  else
  {
      if(deviceType == true)
      {
          ready = true;
          delete getDeviceData[index]; 
      }
      if(deviceType == false)
      {
        MyLecteur.push_back(index);
        LecteurReady=true;
      }
  }
  
      
  qDebug() << "Deleted Index" << index;
}





Dictionnaire * DataManager::GetNextArstist(int i)
{
    Dictionnaire * dic= NULL; 
    if(ready == false)
    {
        return  NULL; 
    }
    
    if(i==0)
    {
        if(chainedData->GetArstistRoot()!=NULL)
            dic=(Dictionnaire *)chainedData->GetArstistRoot()->ReturnValue();
    }
    else
    {
        if(chainedData->GetNextArtist()!=NULL)
        {
            dic=(Dictionnaire *)chainedData->GetNextArtist()->ReturnValue();
            chainedData = chainedData->GetNextArtist();
        }
    }
            
    //qDebug() << dic->value;
    return dic;
}



Dictionnaire * DataManager::SearchTrackFull(char *d)
{
    Dictionnaire * dic= NULL; 
    if(ready == false)
    {
        return  NULL; 
    }
    dic=(Dictionnaire *)chainedData->SearchTrackFull(d);
//    qDebug() << dic->value;
    return dic;
}


Dictionnaire * DataManager::SearchArstist(char *d)
{
    Dictionnaire * dic= NULL; 
    if(ready == false)
    {
        return  NULL; 
    }
    dic=(Dictionnaire *)chainedData->SearchArtist(d);
    qDebug() << dic->value;
    return dic;
}


void DataManager::AddTrackToList(Dictionnaire *d,char * Art)
{
    chainedData->AddTrack((void *)d,Art);
}



void DataManager::AddAlbumToList(Dictionnaire *d,char * Art)
{
    chainedData->AddAlbum((void *)d,Art);
}

void DataManager::AddDataToList(Dictionnaire *d)
{
    if(NewData==true)
    {
        chainedData = new ChainedData((void*)d);
        NewData=false;
    }
    else
    {
        chainedData->AddArtist((void *)d);
    }
    
}


bool DataManager::Play(Dictionnaire* d)
{
    for(int i=0;i<MyLecteur.size();i++)
    {
        bool res = getDeviceTransport[MyLecteur[i]]->PrepareUri(d);
        if(res == true)
        {
            getDeviceTransport[MyLecteur[i]]->Play();
        }
    }

    return true;
}





bool DataManager::EventNewDeviceAdded(int index)
{
    //TODO GESTION DU TABLEAU
    qDebug() << "Index" << index;
    if(index > NbDeviceMax || index == -1) return false;
    /*
    getDeviceData[index] = new GetDeviceData(index);
    getDeviceData[index]->start();
     */ 
   
    UpnpRoot u = UpnpManager::GetInstance().GetStructureDeviceByIndex(index);
    if(u.idRoot ==-1) 
        return false;
    for(int i=0;i<u.upnpListDevice.size();i++)
    {
       
        if(u.upnpListDevice[i].IsUnknow == false)
        {
            if(u.upnpListDevice[i].Isreader == true)
            {
                getDeviceTransport[index] = new TransportManager(index);
                QObject::connect(getDeviceTransport[index], SIGNAL(termine(int,bool,bool)), &DataManager::GetInstance() , SLOT(parseTermine(int,bool,bool)));
                getDeviceTransport[index]->start();                
            }
            else
            {
               getDeviceData[index] = new GetDeviceData(index);
               QObject::connect(getDeviceData[index], SIGNAL(termine(int,bool,bool)), &DataManager::GetInstance() , SLOT(parseTermine(int,bool,bool)));
               getDeviceData[index]->start();
            }
        }
    }
    return true;
}