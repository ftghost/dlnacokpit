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

class DataManager : public QObject
{
Q_OBJECT

public slots:
  void  parseTermine(int,bool,bool);
    
 signals:
  void  AddReader(int,char *);
 

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
     Dictionnaire *  SearchTrack(char *d);
     QList<QString> Search(QString,QString);
     bool Play(Dictionnaire *d);
     bool Play();
     bool Stop();
     bool Pause();
     bool Next();
     bool SetReader(int index);
     

private :
    int SelectedIndex;
    bool NewData;
    bool ready;
    bool LecteurReady;
    std::vector<int> MyLecteur;
    ChainedData * chainedData;
    const int NbDeviceMax=50;
    GetDeviceData *getDeviceData[50];   
    TransportManager *getDeviceTransport[50];   
    DataManager& operator= (const DataManager&){}
    DataManager (const DataManager&){}
    DataManager();
    static DataManager m_instance;
    
};


#endif	/* DATAMANAGER_H */

