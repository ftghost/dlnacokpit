#include "DataManager.h"
#include <QDebug>




DataManager DataManager::m_instance=DataManager();


DataManager & DataManager::GetInstance()
{
  return m_instance;
}


DataManager::DataManager()
{
    NewData = true;
}



DataManager::~DataManager()
{

}


void DataManager::parseTermine(int index)
{
  QThread::sleep ( 5 );  
  delete getDeviceData[index];  
  qDebug() << "Deleted Index" << index;
}



Dictionnaire * DataManager::GetNextArstist(int i)
{
    Dictionnaire * dic= NULL; 
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



Dictionnaire * DataManager::SearchArstist(char *d)
{
    Dictionnaire * dic=(Dictionnaire *)chainedData->SearchArtist(d);
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

bool DataManager::EventNewDeviceAdded(int index)
{
    //TODO GESTION DU TABLEAU
    qDebug() << "Index" << index;
    
    if(index > NbDeviceMax || index == -1) return false;
    getDeviceData[index] = new GetDeviceData(index);
    QObject::connect(getDeviceData[index], SIGNAL(termine(int)), &DataManager::GetInstance() , SLOT(parseTermine(int)));
    getDeviceData[index]->start();
    return true;
}