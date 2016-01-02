#include "DataManager.h"
#include "UpnpManager.h"
#include  "UpnpDiscover.h"
#include <QDebug>
#include <QList>




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
    SelectedIndex = -1;
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
    {
        delete getDeviceData[index];  
        NbServeur--;
     
    }
  }
  else
  {
      if(deviceType == true)
      {
          ready = true;
          delete getDeviceData[index]; 
          NbServeur--;
          if(NbServeur == 0)
          {
            CanaddToScreen(); 
          }
      }
      if(deviceType == false)
      {
        MyLecteur.push_back(index);
        LecteurReady=true;
        AddReader(index,getDeviceTransport[index]->GetIconPath());
      }
  }
  
      
  //qDebug() << "Deleted Index" << index;
}


void DataManager::CanaddToScreen()
{
    
        ChainedData * ChainedDataAdd = chainedData;
        ChainedDataAdd = chainedData->GetFirst();
	ChainedData * chaineDataAlbum;

	while(ChainedDataAdd!=NULL)
	{
		if(ChainedDataAdd->GetLastAlbum()!=NULL)
		{
			chaineDataAlbum = ChainedDataAdd->GetLastAlbum()->GetAlbumRoot();
                        Dictionnaire *d = (Dictionnaire *)chaineDataAlbum->ReturnValue(); 
                        if(d->Imgurl !=NULL)
                        {
                            AddToScreen(d->value,d->Imgurl);
                        }
                        else
                        {
                            AddToScreen(d->value,"guer.jpeg");
                        }
			qDebug()<<d->value;
                        
			while(chaineDataAlbum->GetNextAlbum() != NULL)
			{
				d = (Dictionnaire *)chaineDataAlbum->GetNextAlbum()->ReturnValue();
                                if(d->Imgurl !=NULL)
                                    AddToScreen(d->value,d->Imgurl);
                                else
                                {
                                    AddToScreen(d->value,"guer.jpeg");
                                }
                                qDebug()<<d->value;
				chaineDataAlbum = chaineDataAlbum->GetNextAlbum();
			}
		}
		ChainedDataAdd = ChainedDataAdd->GetNextArtist();
	} 
    
    
   
            
    
    //AddToScreen(name,url);
}


bool DataManager::UpdateVolume(char * vol)
{
    char v[5];
    memset(v,sizeof(v),'\0');
    strcpy(v,vol);
    if(SelectedIndex==-1)return false;
    qDebug()<<"Volume set to " << v;
    getDeviceTransport[SelectedIndex]->SetVolumeExt(v);
    UpdateVol(getDeviceTransport[SelectedIndex]->GetVolumeExt());
    return true;
}


char * DataManager::SetReader(int i)
{
    SelectedIndex= i;
    char * v = getDeviceTransport[SelectedIndex]->GetVolumeExt();
    return v;
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
            
    ////qDebug() << dic->value;
    return dic;
}



Dictionnaire *  DataManager::SearchTrack(char *d)
{
    Dictionnaire *  dic = NULL; 
    if(ready == false)
    {
        return  dic; 
    }
    dic = (Dictionnaire *)chainedData->SearchTrack(d);
    return dic;
}


QList<Dictionnaire *>  DataManager::SearchArtistFull(char *d)
{
    QList<Dictionnaire *>  dic; 
    if(ready == false)
    {
        return  dic; 
    }
    dic=chainedData->SearchArtistFull(d);
    return dic;   
}




QList<Dictionnaire *>  DataManager::SearchAlbumFull(char *d)
{
    QList<Dictionnaire *>  dic; 
    if(ready == false)
    {
        return  dic; 
    }
    dic=chainedData->SearchAlbumFull(d);
    return dic;   
}

QList<Dictionnaire *>  DataManager::SearchTrackFull(char *d)
{
    QList<Dictionnaire *>  dic; 
    if(ready == false)
    {
        return  dic; 
    }
    dic=chainedData->SearchTrackFull(d);
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
    //qDebug() << dic->value;
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


bool DataManager::SetSameUri()
{
    if(chaineDataTrack != NULL)
    {
        Dictionnaire *dic= (Dictionnaire *)chaineDataTrack->ReturnValue();
        if(dic!=NULL)
        {
            getDeviceTransport[SelectedIndex]->PrepareNextUri(dic);   
            //chaineDataTrack = chaineDataTrack->GetNextTrack();
        }
    }
}



bool DataManager::SetNextUri()
{
    if(chaineDataTrack->GetNextTrack() != NULL)
    {
        Dictionnaire *dic= (Dictionnaire *)chaineDataTrack->GetNextTrack()->ReturnValue();
        if(dic!=NULL)
        {
            getDeviceTransport[SelectedIndex]->PrepareNextUri(dic);   
            chaineDataTrack = chaineDataTrack->GetNextTrack();
        }
    }
}


bool DataManager::UpdateTitre()
{
    if(chaineDataTrack!=NULL)
    {
        if(chaineDataTrack->GetPreviousTrack()!=NULL)
        {
            Dictionnaire *dic= (Dictionnaire *)chaineDataTrack->GetPreviousTrack()->ReturnValue();
            if(dic!=NULL)
                UpdateTitre(dic->value);
        }
    }
    return true;
}

bool DataManager::PlayAlbum(char * val)
{
    if(SelectedIndex==-1)return false;
    UpnpDiscover::GetInstance().Started = true;
    ChainedData * d = chainedData->SearchAlbumPrivate(val);
    Dictionnaire * dic =NULL;
    if(d!=NULL)
    {
        if(d->GetLastTrack() != NULL)
        {
            chaineDataTrack = d->GetLastTrack()->GetTrackRoot();
            dic=(Dictionnaire *)chaineDataTrack->ReturnValue();
            if(dic!=NULL)
            {
                bool res = getDeviceTransport[SelectedIndex]->PrepareUri(dic);
                if(res == true)
                {
                   getDeviceTransport[SelectedIndex]->Play();
                   UpdateTitre(dic->value);
                }   
            }
        }
     }
}




bool DataManager::Play(Dictionnaire* d)
{
    if(SelectedIndex==-1)return false;
    bool res = getDeviceTransport[SelectedIndex]->PrepareUri(d);
    if(res == true)
    {
       getDeviceTransport[SelectedIndex]->Play();
       UpdateTitre(d->value);
    }


    return true;
}


bool DataManager::Play()
{
    if(SelectedIndex==-1)return false;
    getDeviceTransport[SelectedIndex]->Play();
    return true;
}


bool DataManager::Pause()
{
    if(SelectedIndex==-1)return false;
    getDeviceTransport[SelectedIndex]->Pause();
    return true;
}

bool DataManager::Next()
{
    if(SelectedIndex==-1)return false;
    getDeviceTransport[SelectedIndex]->Next();
    return true;
}

bool DataManager::Stop()
{
    if(SelectedIndex==-1)return false;
    getDeviceTransport[SelectedIndex]->Stop();
    return true;
}


 QList<QString> DataManager::Search(QString val,QString type)
 {
      QList<QString> list;
      if(type=="Artiste")
      {
         QList<Dictionnaire*> dList=SearchArtistFull((char*)val.toStdString().c_str());
         for(int i=0;i<dList.size();i++)
         {
             list.push_back(dList[i]->value);
             if(dList[i]->Imgurl == NULL)
             {
                 list.push_back("guer.jpeg");
             }
             else
             {
                list.push_back(dList[i]->Imgurl);
             }
         } 
      }
      
      if(type=="Album")
      {
        QList<Dictionnaire*> dList=SearchAlbumFull((char*)val.toStdString().c_str());
         for(int i=0;i<dList.size();i++)
         {
             list.push_back(dList[i]->value);
             if(dList[i]->Imgurl == NULL)
             {
                 list.push_back("guer.jpeg");
             }
             else
             {
                list.push_back(dList[i]->Imgurl);
             }
         }
      }
      
      if(type=="Morceau")
      {
         QList<Dictionnaire*> dList=SearchTrackFull((char*)val.toStdString().c_str());
         for(int i=0;i<dList.size();i++)
         {
             list.push_back(dList[i]->value);
             if(dList[i]->Imgurl == NULL)
             {
                 list.push_back("guer.jpeg");
             }
             else
             {
                list.push_back(dList[i]->Imgurl);
             }
         }
      }
      
      if(type=="Video")
      {
          
      }
          
      
      return list;
 }



bool DataManager::EventNewDeviceAdded(int index)
{
    //TODO GESTION DU TABLEAU
    //qDebug() << "Index" << index;
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
               NbServeur++; 
               getDeviceData[index] = new GetDeviceData(index);
               QObject::connect(getDeviceData[index], SIGNAL(termine(int,bool,bool)), &DataManager::GetInstance() , SLOT(parseTermine(int,bool,bool)));
               getDeviceData[index]->start();
            }
        }
    }
    return true;
}