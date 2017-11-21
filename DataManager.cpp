#include "DataManager.h"
#include "UpnpManager.h"
#include  "UpnpDiscover.h"
#include <QDebug>
#include <QList>
#include <QDir>
#include "htmlTool.h"
#include "UpnpEventManager.h"
#include "HttpClientManager.h"




DataManager DataManager::m_instance=DataManager();
pthread_mutex_t DataManager::mutexUri;

DataManager & DataManager::GetInstance()
{
  return m_instance;
}


DataManager::DataManager()
{
    InitNext = false;
    Init = false;
    NewData = true;
    ready = false;
    LecteurReady = false;
    SelectedIndex = -1;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateInfo()));  
}



DataManager::~DataManager()
{

}


void DataManager::updateInfo()
{
    if(SelectedIndex==-1)return;
    getDeviceTransport[SelectedIndex]->GetInfo();
    QList<QString> res = getDeviceTransport[SelectedIndex]->GetInfoExt();
    QString maxString;
    int max=0;
    int current=0;
    for(int i=0;i<res.length();i++)
    {
        if(i==1)
        {
            maxString = res[i];
            QStringList myStringList = res[i].split(":");
        
            for(int index =0;index < myStringList.length();index++)
            {
                if(index==1)
                {
                    int val = myStringList[index].toInt();
                    max= val*60;
                }
                if(index==2)
                {
                    int val = myStringList[index].toInt();
                    max= max+val;
                }   
            }
        }
        
        if(i==2)
        {
            QStringList myStringList = res[i].split(":");
            for(int index =0;index < myStringList.length();index++)
            {
                if(index==1)
                {
                    int val = myStringList[index].toInt();
                    current= val*60;
                }
                if(index==2)
                {
                    int val = myStringList[index].toInt();
                    current= current+val;
                }   
            }
        }
        
    }
    UpdateRange(max,current,maxString);    
    return;
}



void DataManager::parseTermine(int index,bool isOk,bool deviceType)
{
  QThread::sleep ( 1 );  
  if(isOk==false)
  {
    if(deviceType == false)  
    {
        delete getDeviceTransport[index];  
    }
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
}


void DataManager::CanaddToScreen()
{
        ChainedData * ChainedDataAdd = chainedData;
        ChainedDataAdd = chainedData->GetFirst();
	ChainedData * chaineDataAlbum;

	while(ChainedDataAdd!=NULL)
	{
                char valeurArtiste[500]="";
               
                
		if(ChainedDataAdd->GetLastAlbum()!=NULL)
		{
                     if(ChainedDataAdd->GetLastAlbum()->GetArstistRoot()!=NULL)
                     {
                        Dictionnaire *artiste = (Dictionnaire *)ChainedDataAdd->GetLastAlbum()->GetArstistRoot()->ReturnValue();
                        //qDebug() << "Artiste : " <<  artiste->value;
                        strcpy(valeurArtiste,artiste->value);
                     }
                     
                        char valeurAffiche[500]="";
			chaineDataAlbum = ChainedDataAdd->GetLastAlbum()->GetAlbumRoot();
                        Dictionnaire *d = (Dictionnaire *)chaineDataAlbum->ReturnValue(); 
                        strcpy(valeurAffiche,valeurArtiste);
                        strcat(valeurAffiche," : ");
                        strcat(valeurAffiche,d->value);
                        if(d->Imgurl !=NULL)
                        {
                            AddToScreen(d->value,d->Imgurl,valeurAffiche,d->id);
                        }
                        else
                        {
                            AddToScreen(d->value,"guer.jpeg",valeurAffiche,d->id);
                        }
			while(chaineDataAlbum->GetNextAlbum() != NULL)
			{
				d = (Dictionnaire *)chaineDataAlbum->GetNextAlbum()->ReturnValue();
                                strcpy(valeurAffiche,valeurArtiste);
                                strcat(valeurAffiche," : ");
                                strcat(valeurAffiche,d->value);
                                if(d->Imgurl !=NULL)
                                {
                                    AddToScreen(d->value,d->Imgurl,valeurAffiche,d->id);
                                }
                                else
                                {
                                    AddToScreen(d->value,"guer.jpeg",valeurAffiche,d->id);
                                }
				chaineDataAlbum = chaineDataAlbum->GetNextAlbum();
			}
		}
		ChainedDataAdd = ChainedDataAdd->GetNextArtist();
	} 
}


bool DataManager::UpdateVolume(char * vol)
{
    char v[5];
    memset(v,sizeof(v),'\0');
    strcpy(v,vol);
    if(SelectedIndex==-1)return false;
    getDeviceTransport[SelectedIndex]->SetVolumeExt(v);
    UpdateVol(getDeviceTransport[SelectedIndex]->GetVolumeExt());
    return true;
}

bool DataManager::SetVolume(char * vol)
{
    if(SelectedIndex==-1)return false;
    return getDeviceTransport[SelectedIndex]->SetVolume(vol);
}

char * DataManager::SetReader(int i)
{
    SelectedIndex= i;
    UpnpEventManager::GetInstance().SetSelected(SelectedIndex);
    char * v = getDeviceTransport[SelectedIndex]->GetVolumeExt();
    timer->stop();
    timer->start(1000);
    SetStopUri();
    //Test
    /*
    Dictionnaire * dic= new Dictionnaire();
    dic->Playurl = new char[strlen("http://192.168.0.20:8081//home/ghost/Musique/mp3/Arno_Modern_Incognito/1.flac")+1];
    strcpy(dic->Playurl,"http://192.168.0.20:8081//home/ghost/Musique/mp3/Arno_Modern_Incognito/1.flac");
    getDeviceTransport[SelectedIndex]->PrepareUri(dic);   
    getDeviceTransport[SelectedIndex]->Play();
    delete dic->Playurl;
    delete dic;
     */ 
    //Fin test
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
        {
            dic=(Dictionnaire *)chainedData->GetArstistRoot()->ReturnValue();
        }
    }
    else
    {
        if(chainedData->GetNextArtist()!=NULL)
        {
            dic=(Dictionnaire *)chainedData->GetNextArtist()->ReturnValue();
            chainedData = chainedData->GetNextArtist();
        }
    }
    return dic;
}



Dictionnaire *  DataManager::SearchTrack(char *d,char * pid)
{
    Dictionnaire *  dic = NULL; 
    if(ready == false)
    {
        return  dic; 
    }
    dic = (Dictionnaire *)chainedData->SearchTrack(d,pid);
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



QList<QString>  DataManager::AddToPlayList(char * val , char * genre,char * pid)
{
    QList<QString> qls;
    if(SelectedIndex==-1)return qls;
   
    if(strcmp(genre,"Morceau")==0)
    {
        Dictionnaire *d = SearchTrack(val,pid);
        if(d!=NULL)
        {
            if(chaineDataTrackList[SelectedIndex] == NULL)
            {
                chaineDataTrackList[SelectedIndex] = new ChainedData((void *)d,true);
                if(d->Imgurl!=NULL)
                    qls.push_back(d->Imgurl);
                else
                {
                    qls.push_back("guer.jpeg");
                }
                qls.push_back(d->value);
            }
            else
            {
                chaineDataTrackList[SelectedIndex]->GetFirst()->AddArtist((void *)d,true);
                 if(d->Imgurl!=NULL)
                    qls.push_back(d->Imgurl);
                else
                    qls.push_back("guer.jpeg");
                qls.push_back(d->value);
            }
            qls.push_back(d->value);
        }
        
    }
    else if(strcmp(genre,"Album")==0)
    {
        Dictionnaire * dico= new Dictionnaire();
        dico->parentId = new char[strlen(pid)+1];
        strcpy(dico->parentId,pid);
        ChainedData * d = chainedData->SearchAlbumPrivate(val,dico);
        if(d!=NULL)
        {
            if(d->GetLastTrack() != NULL)
            {
                d=d->GetLastTrack()->GetTrackRoot();
                Dictionnaire * dic=(Dictionnaire *)d->ReturnValue();
                if(dic!=NULL)              
                {
                    if(chaineDataTrackList[SelectedIndex] == NULL)
                    {
                        chaineDataTrackList[SelectedIndex] = new ChainedData((void *)dic,true);
                        if(dic->Imgurl!=NULL)
                            qls.push_back(dic->Imgurl);
                        else
                        {
                            qls.push_back("guer.jpeg");
                        }
                        qls.push_back(dic->value);
                    }
                    else
                    {
                        chaineDataTrackList[SelectedIndex]->GetFirst()->AddArtist((void *)dic,true);
                        if(dic->Imgurl!=NULL)
                            qls.push_back(dic->Imgurl);
                        else
                            qls.push_back("guer.jpeg");

                        qls.push_back(dic->value);
                    } 
                    qls.push_back(dic->value);
                }
                while(d->GetNextTrack()!=NULL)
                {
                    chaineDataTrackList[SelectedIndex]->GetFirst()->AddArtist(d->GetNextTrack()->ReturnValue());
                    dic=(Dictionnaire *)d->GetNextTrack()->ReturnValue();
                    if(dic->Imgurl!=NULL)
                        qls.push_back(dic->Imgurl);
                    else
                        qls.push_back("guer.jpeg");
                    qls.push_back(dic->value);
                    qls.push_back(dic->value);
                    d= d->GetNextTrack();
                }
            }
        }
        delete dico->parentId;
        delete dico;
    }
    
    if(UpnpEventManager::GetInstance().GetNextUriSet()==false)
    {
        SetNextUri();
    }
    return qls;
}
            
 



void DataManager::ClearQueue()
{
  if(chaineDataTrackList[SelectedIndex] != NULL)
  {       
    if(chaineDataTrackList[SelectedIndex]->GetLastArtist()!=NULL)  
    {
        chaineDataTrackList[SelectedIndex] = chaineDataTrackList[SelectedIndex]->GetLastArtist();
        while(chaineDataTrackList[SelectedIndex]->GetPreviousArtist() != NULL)
        {
           chaineDataTrackList[SelectedIndex] = chaineDataTrackList[SelectedIndex]->GetPreviousArtist();
           delete chaineDataTrackList[SelectedIndex]->GetNextArtist();
        }
        delete chaineDataTrackList[SelectedIndex]->GetFirst();
    }
    chaineDataTrackList[SelectedIndex] = NULL;
  }
  
  if(chaineDataTrack != NULL)
  {       
    if(chaineDataTrack->GetLastArtist()!=NULL)  
    {
        chaineDataTrack = chaineDataTrack->GetLastArtist();
        while(chaineDataTrack->GetPreviousArtist() != NULL)
        {
           chaineDataTrack = chaineDataTrack->GetPreviousArtist();
           delete chaineDataTrack->GetNextArtist();
        }
        delete chaineDataTrack->GetFirst();
    }
    chaineDataTrack = NULL;
  }
  Init =false;
  InitNext=false;
  SetStopUri();
}




bool DataManager::SetStopUri()
{
    if(SelectedIndex==-1)return true;
    Dictionnaire d ;
    d.Playurl = new char[strlen("")+1];
    strcpy(d.Playurl,"");
    getDeviceTransport[SelectedIndex]->Stop();
    bool ret = getDeviceTransport[SelectedIndex]->PrepareNextUri(&d); 
    ret = getDeviceTransport[SelectedIndex]->PrepareUri(&d);
    UpnpEventManager::GetInstance().SetDataMangerStopped(true);
    UpnpEventManager::GetInstance().SetNextUriSet(false);
    return true;
}



bool DataManager::SetSameUri()
{
    if(SelectedIndex==-1)return false;
    pthread_mutex_lock(&mutexUri);
    if(chaineDataTrack != NULL)
    {
        Dictionnaire *dic= (Dictionnaire *)chaineDataTrack->ReturnValue();
        if(dic!=NULL)
        {
            getDeviceTransport[SelectedIndex]->PrepareNextUri(dic);
            UpnpEventManager::GetInstance().SetNextUriSet(true);
        }
    }
    else
    {
        if(chaineDataTrackList[SelectedIndex] != NULL)
        {
            Dictionnaire *dic= (Dictionnaire *)chaineDataTrackList[SelectedIndex]->ReturnValue();
            if(dic!=NULL)
            {
                getDeviceTransport[SelectedIndex]->PrepareNextUri(dic); 
                UpnpEventManager::GetInstance().SetNextUriSet(true);                
            }
        }
    }
    pthread_mutex_unlock(&mutexUri);
}




bool DataManager::PlayAndSetUri()
{
        if(SelectedIndex==-1 || IsStop == true)return false;
        pthread_mutex_lock(&mutexUri);
        if(chaineDataTrack != NULL)
        {
            if(Init==false)
            {
                Dictionnaire *dic= (Dictionnaire *)chaineDataTrack->ReturnValue();
                if(dic!=NULL)
                {
                    getDeviceTransport[SelectedIndex]->PrepareUri(dic);
                    getDeviceTransport[SelectedIndex]->Play();
                    //UpdateTitre(dic->value);
                }
                Init = true;
            }
            else
            {
                if(chaineDataTrack->GetNextTrack() != NULL)
                {
                    Dictionnaire *dic= (Dictionnaire *)chaineDataTrack->GetNextTrack()->ReturnValue();
                    if(dic!=NULL)
                    {
                        getDeviceTransport[SelectedIndex]->PrepareUri(dic);
                        getDeviceTransport[SelectedIndex]->Play();
                        //UpdateTitre(dic->value);
                        chaineDataTrack = chaineDataTrack->GetNextTrack();
                    }
                }
                else
                {
                    chaineDataTrack = chaineDataTrack->GetNextTrack();
                }
            }
        }
        else
        {
            if(InitNext==true)
            {
                if(chaineDataTrackList[SelectedIndex] != NULL)
                {
                    Dictionnaire *dic= (Dictionnaire *)chaineDataTrackList[SelectedIndex]->ReturnValue();
                    if(dic!=NULL)
                    {
                        getDeviceTransport[SelectedIndex]->PrepareUri(dic);   
                        getDeviceTransport[SelectedIndex]->Play();
                        //UpdateTitre(dic->value);
//                        chaineDataTrackList[SelectedIndex] = chaineDataTrackList[SelectedIndex]->GetNextArtist();
                    }
                }
            }
            else
            {
                if(chaineDataTrackList[SelectedIndex] != NULL)
                {       
                    if(chaineDataTrackList[SelectedIndex]->GetFirst()!=NULL)
                    {
                        Dictionnaire *dic= (Dictionnaire *)chaineDataTrackList[SelectedIndex]->GetFirst()->ReturnValue();
                        if(dic!=NULL)
                        {
                            getDeviceTransport[SelectedIndex]->PrepareUri(dic);   
                            getDeviceTransport[SelectedIndex]->Play();
                            //UpdateTitre(dic->value);
                            chaineDataTrackList[SelectedIndex] = chaineDataTrackList[SelectedIndex]->GetFirst();
                        }                        
                        InitNext=true;
                    }
                    else
                    {
                        chaineDataTrackList[SelectedIndex] = chaineDataTrackList[SelectedIndex]->GetFirst();
                    }
                }
            }
        }
        pthread_mutex_unlock(&mutexUri);
}



bool DataManager::SetNextUri()
{ 
    if(SelectedIndex==-1)return false;
    pthread_mutex_lock(&mutexUri);
    bool IsSetNextUri = false;
    if(chaineDataTrack != NULL)
    {
        if(chaineDataTrack->GetNextTrack() != NULL)
        {
            
            Dictionnaire * dic= (Dictionnaire *)chaineDataTrack->GetNextTrack()->ReturnValue();
            if(dic!=NULL)
            {
                getDeviceTransport[SelectedIndex]->PrepareNextUri(dic); 
                UpnpEventManager::GetInstance().SetNextUriSet(true);
                if(chaineDataTrack->GetNextTrack()!=NULL)
                {
                    chaineDataTrack = chaineDataTrack->GetNextTrack();
                }
                IsSetNextUri = true;
            }
        }
        else
        {
            chaineDataTrack = chaineDataTrack->GetNextTrack();
            UpnpEventManager::GetInstance().SetNextUriSet(false);
        }
    }
  
    
    if(IsSetNextUri==false)
    {
        if(chaineDataTrackList[SelectedIndex] != NULL)
        {
            if(InitNext == false)
            {
                Dictionnaire *dic= (Dictionnaire *)chaineDataTrackList[SelectedIndex]->ReturnValue();
                if(dic!=NULL)
                {
                    getDeviceTransport[SelectedIndex]->PrepareNextUri(dic);
                    UpnpEventManager::GetInstance().SetNextUriSet(true);
                    if(chaineDataTrackList[SelectedIndex]->GetNextArtist()!=NULL)
                    {
                        chaineDataTrackList[SelectedIndex] = chaineDataTrackList[SelectedIndex]->GetNextArtist();
                    }
                }
                else
                {
                    UpnpEventManager::GetInstance().SetNextUriSet(false);
                }
                InitNext = true;
            }
            else
            {
                if(chaineDataTrackList[SelectedIndex]->GetNextArtist() != NULL)
                {
                    Dictionnaire *dic= (Dictionnaire *)chaineDataTrackList[SelectedIndex]->GetNextArtist()->ReturnValue();
                    if(dic!=NULL)
                    {
                        getDeviceTransport[SelectedIndex]->PrepareNextUri(dic);
                        UpnpEventManager::GetInstance().SetNextUriSet(true);
                        if(chaineDataTrackList[SelectedIndex]->GetNextArtist()!=NULL)
                        {
                            chaineDataTrackList[SelectedIndex] = chaineDataTrackList[SelectedIndex]->GetNextArtist();
                        }
                    }
                    else
                    {
                        UpnpEventManager::GetInstance().SetNextUriSet(false);
                    }
                } 
            }
        }
        else
        {
            UpnpEventManager::GetInstance().SetNextUriSet(false);
        }
    }
    pthread_mutex_unlock(&mutexUri);
}


bool DataManager::UpdateTitreFull(char * Url)
{
    if(UpnpEventManager::GetInstance().GetDataMangerStopped()==true) return true;
    char UrlTest[500]="";
    strcpy(UrlTest,Url);
    Dictionnaire * dic=(Dictionnaire *)chainedData->SearchByUrl(UrlTest);
    if(dic!=NULL)
    { 
        qDebug() << "Not null" << dic->value;
        UpdateTitre(dic->value);
    }
    return true;
}

bool DataManager::PlayAlbum(char * val,char * pid)
{
    if(SelectedIndex==-1)return false;
    pthread_mutex_lock(&mutexUri);
    Dictionnaire * dico= new Dictionnaire();
    dico->parentId = new char[strlen(pid)+1];
    strcpy(dico->parentId,pid);
    ChainedData * d = chainedData->SearchAlbumPrivate(val,dico);
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
                   //UpdateTitre(dic->value);
                }   
            }
        }
    }
    delete dico->parentId;
    delete dico;
    pthread_mutex_unlock(&mutexUri);
    return true;
}




bool DataManager::Play(Dictionnaire* d)
{
    if(SelectedIndex==-1)return false;
    bool res = getDeviceTransport[SelectedIndex]->PrepareUri(d);
    if(res == true)
    {
       getDeviceTransport[SelectedIndex]->Play();
       //UpdateTitre(d->value);
    }
    return true;
}


bool DataManager::Play()
{
    if(SelectedIndex==-1)return false;
    IsStop = false;
    UpnpEventManager::GetInstance().SetDataMangerStopped(false);
    bool ret = getDeviceTransport[SelectedIndex]->Play();
    if(ret==false)
    {
        PlayAndSetUri();
    }
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
    bool ret = getDeviceTransport[SelectedIndex]->Next();
    IsStop = false;
    UpnpEventManager::GetInstance().SetDataMangerStopped(false);
    if(ret==false)
    {
       PlayAndSetUri(); 
    }
    return true;
}

bool DataManager::Stop()
{
    if(SelectedIndex==-1)return false;
    IsStop = true;
    UpnpEventManager::GetInstance().SetDataMangerStopped(true);
    getDeviceTransport[SelectedIndex]->Stop();
    return true;
}


QList<QString> DataManager::getAllInfo(QString val,QString val1)
{
    QList<QString> list; 
    QList<Dictionnaire*> dList=chainedData->SearchTrackOfAlbum((char*)val.toStdString().c_str(),(char*)val1.toStdString().c_str());
    for(int i=0;i<dList.size();i++)
    {
        if(i==1)
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
        else
        {
          list.push_back(dList[i]->value);  
        }
    }
   return list;
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
             list.push_back(dList[i]->id);
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
             list.push_back(dList[i]->id);
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
             list.push_back(dList[i]->id);
         }
      }
      
      if(type=="Video")
      {
          
      }
      
      if(type=="Web")
      {
          HttpClientManager *h = new HttpClientManager();
          h->PostUrl();
         //delete h;
      }
          
      
      return list;
 }



bool DataManager::EventNewDeviceAdded(int index)
{
    //TODO GESTION DU TABLEAUChainedData * d = chainedData->SearchAlbumPrivate(val);
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