#include <stdio.h>
#include <string.h>
#include "congig.h"
#include <QList>



class ChainedData
{
public:
	ChainedData(void );
	ChainedData(void * value);
	~ChainedData(void);
	/*********************/
	ChainedType GetType();
	/*********************/
	ChainedData * GetFirst();
	/*********************/
	ChainedData * GetLastArtist();
	ChainedData * GetLastAlbum();
	ChainedData * GetLastTrack();
	/*********************/
	ChainedData * GetNextArtist();
	ChainedData * GetNextAlbum();
	ChainedData * GetNextTrack();
	/*********************/
	ChainedData * GetPreviousArtist();
	ChainedData * GetPreviousAlbum();
	ChainedData * GetPreviousTrack();
	/*********************/
	ChainedData * GetArstistRoot();
	ChainedData * GetAlbumRoot();
	ChainedData * GetTrackRoot();
	/*********************/
	bool AddAlbum(void * val ,char * Artist);
	bool AddArtist(void * val);
	bool AddTrack(void * val,char * Artist);
	/*********************/
        QList<Dictionnaire *> SearchTrackFull(void * val);
        QList<Dictionnaire *> SearchAlbumFull(void * val);
	void * SearchArtist(void * val);
	void * SearchAlbum(void * val);
	void * SearchTrack(void * val);
	void * SearchAll(void *val);
	void * ReturnValue();
      	ChainedData * SearchArtistPrivate(void * val);
	ChainedData * SearchAlbumPrivate(void * val);


private:
	/**********************/
	//Type de liste
	ChainedType chainedType;
	bool SetType(ChainedType);
	/*********************/
	bool SetFirst(ChainedData *);
	/*********************/
	bool SetLastArtist(ChainedData *);
	bool SetLastAlbum(ChainedData *);
	bool SetLastTrack(ChainedData *);
	/*********************/
	bool SetNextArtist(ChainedData *);
	bool SetNextAlbum(ChainedData *);
	bool SetNextTrack(ChainedData *);
	/*********************/
	bool SetPreviousArtist(ChainedData *);
	bool SetPreviousAlbum(ChainedData *);
	bool SetPreviousTrack(ChainedData *);
	/*********************/
	bool SetArstistRoot(ChainedData *);
	bool SetAlbumRoot(ChainedData *);
	bool SetTrackRoot(ChainedData *);
	/*********************/
	bool SetValue(void *);
	/*********************/
	bool AddTrack(void * val,ChainedData *chainedArstist);
	bool AddAlbum(void * val,ChainedData *chainedAlbum);

	//Pointeur d'identification
	//root element et premiere element liste artiste
	ChainedData * First;
	//root element 
	ChainedData * ArstistRoot;
	ChainedData * AlbumRoot;
	ChainedData * TrackRoot;
	//First �lement
	ChainedData * FirstArtist;
	ChainedData * FirstAlbum;
	ChainedData * FirstTrack;
	//dernier element 
	ChainedData * LastArstist;
	ChainedData * LastAlbum;
	ChainedData * LastTrack;

	//Pointeur de navigation
	//Next
	ChainedData * NextArtist;
	ChainedData * NextAlbum;
	ChainedData * NextTrack;
	//Previous
	ChainedData * PreviousArtist;
	ChainedData * PreviousAlbum;
	ChainedData * PreviousTrack;
	//Value
	Dictionnaire *value;

};

