/* 
 * File:   DataManager.h
 * Author: ghost
 *
 * Created on 31 octobre 2015, 10:29
 */

#ifndef DATAMANAGER_H
#define	DATAMANAGER_H
#include <QObject>
#include "GetDeviceData.h"
#include "TransportManager.h"
#include "ChainedData.h"
#include <QTimer>

class DataManager : public QObject
{
Q_OBJECT

public slots:
  void  parseTermine(int,bool,bool);
  
public slots:  
  void updateInfo();



    
 signals:
  void  AddReader(int,char *);
 signals:
  void  AddToScreen(char*,char*);
 signals:
  void  UpdateVol(char*);
 signals:
    void UpdateTitre(char *);
 signals:
    void UpdateRange(int,int,QString);

public:
     static DataManager & GetInstance();
     virtual ~DataManager();
     bool EventNewDeviceAdded(int );
     void AddDataToList(Dictionnaire *);
     void AddAlbumToList(Dictionnaire *d,char *);
     void AddTrackToList(Dictionnaire *d,char *);
     Dictionnaire *  SearchArstist(char *d);
     Dictionnaire * GetNextArstist(int i);
     QList<Dictionnaire *>   SearchTrackFull(char *d);
     QList<Dictionnaire *>   SearchAlbumFull(char *d);
     QList<Dictionnaire *>   SearchArtistFull(char *d);
     Dictionnaire *  SearchTrack(char *d);
     QList<QString> Search(QString,QString);
     bool Play(Dictionnaire *d);
     bool Play();
     bool Stop();
     bool Pause();
     bool Next();
     char *  SetReader(int index);
     void  CanaddToScreen();
     bool PlayAlbum(char *d);
     bool SetNextUri();
     bool PlayAndSetUri();
     bool SetSameUri();
     bool UpdateVolume(char*);
     bool UpdateTitre();
     bool SetVolume(char *);
     bool AddToPlayList(char *, char *);
     QList<QString> getAllInfo(QString val);

private :
    QList<UiDictionnaire *> PlayList;
    QTimer *timer;
    int NbServeur=0;
    int SelectedIndex;
    bool NewData;
    bool ready;
    bool LecteurReady;
    bool Isplaying;
    bool IsSetNextUri;
    std::vector<int> MyLecteur;
    ChainedData * chainedData;
    ChainedData * chaineDataTrack;
    ChainedData * chaineDataTrackList[50];
    const int NbDeviceMax=50;
    GetDeviceData *getDeviceData[50];   
    TransportManager *getDeviceTransport[50];   
    DataManager& operator= (const DataManager&){}
    DataManager (const DataManager&){}
    DataManager();
    static DataManager m_instance;
    
};


#endif	/* DATAMANAGER_H */

