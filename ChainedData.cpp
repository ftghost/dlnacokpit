#include "ChainedData.h"
#include <QDebug>


//Constructeur

ChainedData::ChainedData()
{
    //Pointeur d'identification
	//root element et premiere element liste artiste
	First=NULL;
	//root element 
	ArstistRoot=NULL;
	AlbumRoot==NULL;
	TrackRoot=NULL;
	//First �lement
	FirstArtist=NULL;
	FirstAlbum=NULL;
	FirstTrack=NULL;
	//dernier element 
	LastArstist=NULL;
	LastAlbum=NULL;
	LastTrack=NULL;

	//Pointeur de navigation
	//Next
	NextArtist=NULL;
	NextAlbum=NULL;
	NextTrack=NULL;
	//Previous
	PreviousArtist=NULL;
	PreviousAlbum=NULL;
	PreviousTrack=NULL;
}


ChainedData::ChainedData(void * Value,bool a)
{
    if(a==false)
    {
        value = new Dictionnaire();
        memcpy ( value, Value, sizeof(Dictionnaire) );
    }
    else
    {
        value =(Dictionnaire *)Value;
    }
    
	First =  this;
	LastArstist =   this;
	ArstistRoot = this;
	chainedType = ARTIST;
//root element et premiere element liste artiste
	
	//root element 
	AlbumRoot==NULL;
	TrackRoot=NULL;
	//First �lement
	FirstArtist=NULL;
	FirstAlbum=NULL;
	FirstTrack=NULL;
	//dernier element 
	LastAlbum=NULL;
	LastTrack=NULL;

	//Pointeur de navigation
	//Next
	NextArtist=NULL;
	NextAlbum=NULL;
	NextTrack=NULL;
	//Previous
	PreviousArtist=NULL;
	PreviousAlbum=NULL;
	PreviousTrack=NULL;        
}


ChainedData::~ChainedData(void)
{
	//delete value;
}

//FIN Constructeur

bool ChainedData::Delete()
{
	if(this->GetNextArtist()!=NULL)
        {
            
        }    
}



//**********RECHERCHE*************/

QList<Dictionnaire *>  ChainedData::SearchArtistFull(void * val)
{
        QList<Dictionnaire *> dList;
	ChainedData * chainedData = this->GetFirst();
	ChainedData * chaineDataAlbum;

	while(chainedData->GetNextArtist()!=NULL)
	{
            Dictionnaire *dartist = (Dictionnaire *)chainedData->GetNextArtist()->ReturnValue(); 
            if(strcasestr(dartist->value,(char*)val)!=NULL)
            {
		if(chainedData->GetNextArtist()->GetLastAlbum()!=NULL)
		{
			chaineDataAlbum = chainedData->GetNextArtist()->GetLastAlbum()->GetAlbumRoot();
                        Dictionnaire *d = (Dictionnaire *)chaineDataAlbum->ReturnValue(); 
			dList.push_back((Dictionnaire*)chaineDataAlbum->ReturnValue());
			while(chaineDataAlbum->GetNextAlbum() != NULL)
			{
        		    Dictionnaire * test = (Dictionnaire *)chaineDataAlbum->GetNextAlbum()->ReturnValue();
                            dList.push_back(test);
			    chaineDataAlbum = chaineDataAlbum->GetNextAlbum();
			}
		}
            }
            chainedData = chainedData->GetNextArtist();
	}
	return dList;
}


QList<Dictionnaire *>  ChainedData::SearchAlbumFull(void * val)
{
        QList<Dictionnaire *> dList;
	ChainedData * chainedData = this->GetFirst();
	ChainedData * chaineDataAlbum;

	while(chainedData->GetNextArtist()!=NULL)
	{
		if(chainedData->GetLastAlbum()!=NULL)
		{
			chaineDataAlbum = chainedData->GetLastAlbum()->GetAlbumRoot();
                        Dictionnaire *d = (Dictionnaire *)chaineDataAlbum->ReturnValue(); 
			if(strcasestr(d->value,(char*)val)!=NULL)
			{
				dList.push_back((Dictionnaire*)chaineDataAlbum->ReturnValue());
			}
			while(chaineDataAlbum->GetNextAlbum() != NULL)
			{
				Dictionnaire * test = (Dictionnaire *)chaineDataAlbum->GetNextAlbum()->ReturnValue();
                                
				if(strcasestr(test->value,(char*)val)!=NULL)
				{
					dList.push_back(test);
				}
				chaineDataAlbum = chaineDataAlbum->GetNextAlbum();
			}
		}
		chainedData = chainedData->GetNextArtist();
	}
	return dList;
}





Dictionnaire * ChainedData::SearchByUrl(void *val)
{
   ChainedData * chainedData = this->GetFirst();
   ChainedData * chaineDataAlbum;
   ChainedData * chaineDataTrack;
   while(chainedData!=NULL)
   {
        if(chainedData->GetLastAlbum()!=NULL)
	{	
                chaineDataAlbum = chainedData->GetLastAlbum()->GetAlbumRoot();
                while(chaineDataAlbum!=NULL)
		{
                    if(chaineDataAlbum->GetLastTrack()!=NULL)
                    {
			chaineDataTrack = chaineDataAlbum->GetLastTrack()->GetTrackRoot();
                        Dictionnaire * ret = (Dictionnaire *)chaineDataTrack->ReturnValue();
			if(strcmp(ret->Playurl,(char*)val)==0)
                        {
                            /*
                            Dictionnaire * art = (Dictionnaire *)chainedData->ReturnValue();
                            Dictionnaire * alb = (Dictionnaire *)chaineDataAlbum->ReturnValue();
                            ret->Filler = new char[strlen(art->value)+strlen(alb->value)+3];
                            strcpy(ret->Filler,art->value);
                            strcat(ret->Filler,":");
                            strcat(ret->Filler,alb->value);
                            strcat(ret->Filler,"-");
                            strcat(ret->Filler,ret->value);
                            */ 
                            return ret;
			}
                        
			while(chaineDataTrack->GetNextTrack() != NULL)
			{
                            Dictionnaire * ret = (Dictionnaire *)chaineDataTrack->GetNextTrack()->ReturnValue();
                            if(strcmp(ret->Playurl,(char*)val)==0)
                            {
                                /*
                                Dictionnaire * art = (Dictionnaire *)chainedData->ReturnValue();
                                Dictionnaire * alb = (Dictionnaire *)chaineDataAlbum->ReturnValue();
                                ret->Filler = new char[strlen(art->value)+strlen(alb->value)+3];
                                strcpy(ret->Filler,art->value);
                                strcat(ret->Filler,":");
                                strcat(ret->Filler,alb->value);
                                strcat(ret->Filler,"-");
                                strcat(ret->Filler,ret->value);
                                */ 
                                return ret;
                            }
                            chaineDataTrack = chaineDataTrack->GetNextTrack();
			}
         	    }
		chaineDataAlbum = chaineDataAlbum->GetNextAlbum();
		}
	}
    chainedData = chainedData->GetNextArtist();
    }
    return NULL;     
}


QList<Dictionnaire *>  ChainedData::SearchTrackFull(void * val)
{
        QList<Dictionnaire *> dList;
	ChainedData * chainedData = this->GetFirst();
	ChainedData * chaineDataAlbum;
	ChainedData * chaineDataTrack;
	while(chainedData!=NULL)
	{
		if(chainedData->GetLastAlbum()!=NULL)
		{	
			chaineDataAlbum = chainedData->GetLastAlbum()->GetAlbumRoot();
			while(chaineDataAlbum!=NULL)
			{
				if(chaineDataAlbum->GetLastTrack()!=NULL)
				{
						chaineDataTrack = chaineDataAlbum->GetLastTrack()->GetTrackRoot();
                                                Dictionnaire * d = (Dictionnaire *)chaineDataTrack->ReturnValue();
						if(strcasestr(d->value,(char*)val)!=NULL)
						{
							dList.push_back((Dictionnaire *)chaineDataAlbum->ReturnValue());
						}
						while(chaineDataTrack->GetNextTrack() != NULL)
						{
							Dictionnaire * d = (Dictionnaire *)chaineDataTrack->GetNextTrack()->ReturnValue();
							if(strcasestr(d->value,(char*)val)!=NULL)
							{
								dList.push_back((Dictionnaire *)chaineDataAlbum->ReturnValue());
							}
                                                        chaineDataTrack = chaineDataTrack->GetNextTrack();
						}

				}
				chaineDataAlbum = chaineDataAlbum->GetNextAlbum();
			}
			
		}
		chainedData = chainedData->GetNextArtist();
	}
	return dList;    
}


void * ChainedData::SearchArtist(void * val)
{
	ChainedData * chainedData = this->GetFirst();
	Dictionnaire * test =(Dictionnaire * ) chainedData->ReturnValue();
	if(strcmp(test->value,(char*)val)==0)
	{
		return test;
	}

	while(chainedData->GetNextArtist() != NULL)
	{
		test = (Dictionnaire * ) chainedData->GetNextArtist()->ReturnValue();
		if(strcmp(test->value,(char*)val)==0)
		{
			return test;
		}
		chainedData = chainedData->GetNextArtist();
	}
        return NULL;
}


void * ChainedData::SearchTrack(void * val,void * pid)
{
	ChainedData * chainedData = this->GetFirst();
	ChainedData * chaineDataAlbum;
	ChainedData * chaineDataTrack;
	while(chainedData!=NULL)
	{
		if(chainedData->GetLastAlbum()!=NULL)
		{	
			chaineDataAlbum = chainedData->GetLastAlbum()->GetAlbumRoot();
			while(chaineDataAlbum!=NULL)
			{
                            if(strcmp((char *)pid,"")==0)
                            {
				if(chaineDataAlbum->GetLastTrack()!=NULL)
				{
                                    chaineDataTrack = chaineDataAlbum->GetLastTrack()->GetTrackRoot();
                                    Dictionnaire * d = (Dictionnaire *)chaineDataTrack->ReturnValue();
                                    if(strcmp(d->value,(char*)val)==0)
                                    {
					return chaineDataTrack->ReturnValue();
                                    }
                                    while(chaineDataTrack->GetNextTrack() != NULL)
                                    {
					Dictionnaire * d = (Dictionnaire *)chaineDataTrack->GetNextTrack()->ReturnValue();
					if(strcmp(d->value,(char*)val)==0)
					{
                                            return d;
					}
                                        chaineDataTrack = chaineDataTrack->GetNextTrack();
                                    }

				}
                            }
                            else
                            {
                                Dictionnaire * dpid = (Dictionnaire *)chaineDataAlbum->ReturnValue();
                                if(strcmp((char*)pid,dpid->id)==0)
                                {
                                    if(chaineDataAlbum->GetLastTrack()!=NULL)
                                    {
                                        chaineDataTrack = chaineDataAlbum->GetLastTrack()->GetTrackRoot();
                                        Dictionnaire * d = (Dictionnaire *)chaineDataTrack->ReturnValue();
                                        if(strcmp(d->value,(char*)val)==0)
                                        {
                                            return chaineDataTrack->ReturnValue();
                                        }
                                        while(chaineDataTrack->GetNextTrack() != NULL)
                                        {
                                            Dictionnaire * d = (Dictionnaire *)chaineDataTrack->GetNextTrack()->ReturnValue();
                                            if(strcmp(d->value,(char*)val)==0)
                                            {
                                                return d;
                                            }
                                            chaineDataTrack = chaineDataTrack->GetNextTrack();
                                        }

                                    }
                                }
                            }
                            chaineDataAlbum = chaineDataAlbum->GetNextAlbum();
			}
			
		}
		chainedData = chainedData->GetNextArtist();
	}
	return NULL;
}


void * ChainedData::SearchAlbum(void * val)
{
	ChainedData * chainedData = this->GetFirst();
	ChainedData * chaineDataAlbum;

	while(chainedData->GetNextArtist()!=NULL)
	{
		if(chainedData->GetLastAlbum()!=NULL)
		{
			chaineDataAlbum = chainedData->GetLastAlbum()->GetAlbumRoot();
                        Dictionnaire *d = (Dictionnaire *)chaineDataAlbum->ReturnValue(); 
			if(strcmp(d->value,(char*)val)==0)
			{
				return chaineDataAlbum->ReturnValue();
			}
			while(chaineDataAlbum->GetNextAlbum() != NULL)
			{
				Dictionnaire * test = (Dictionnaire *)chaineDataAlbum->GetNextAlbum()->ReturnValue();
                                
				if(strcmp(test->value,(char*)val)==0)
				{
					return test;
				}
				chaineDataAlbum = chaineDataAlbum->GetNextAlbum();
			}
		}
		chainedData = chainedData->GetNextArtist();
	}
	return NULL;
}

ChainedData * ChainedData::SearchAlbumPrivate(void * val,void * pid)
{
	ChainedData * chainedData = this->GetFirst();
	ChainedData * chaineDataAlbum;
        Dictionnaire *parentid = (Dictionnaire *)pid; 
	while(chainedData!=NULL)
	{
		if(chainedData->GetLastAlbum()!=NULL)
		{
			chaineDataAlbum = chainedData->GetLastAlbum()->GetAlbumRoot();
                        Dictionnaire *d = (Dictionnaire *)chaineDataAlbum->ReturnValue(); 
			if(strcmp(d->value,(char*)val)==0)
			{
                            if(d->id!=NULL && parentid->parentId!=NULL)
                            {
                                if(strcmp(d->id,parentid->parentId)==0)
                                {
                                    return chaineDataAlbum;
                                }
                            }
                            else
                                return chaineDataAlbum;
			}
			while(chaineDataAlbum->GetNextAlbum() != NULL)
			{
				Dictionnaire *d = (Dictionnaire *)chaineDataAlbum->GetNextAlbum()->ReturnValue();
				if(strcmp(d->value,(char*)val)==0)
				{
                                    if(d->id!=NULL && parentid->parentId!=NULL)
                                    {
                                        if(strcmp(d->id,parentid->parentId)==0)
                                        {
                                            return chaineDataAlbum->GetNextAlbum();
                                        }
                                    }
                                    else
					return chaineDataAlbum->GetNextAlbum();
				}
				chaineDataAlbum = chaineDataAlbum->GetNextAlbum();
			}
		}
		chainedData = chainedData->GetNextArtist();
	}
	return NULL;
}

ChainedData * ChainedData::SearchArtistPrivate(void * val,void * d)
{
	ChainedData * chainedData = this->GetFirst();
	Dictionnaire * test = (Dictionnaire*)chainedData->ReturnValue();
        Dictionnaire * testParent = (Dictionnaire*)d;
        
	if(strcmp(test->value,(char*)val)==0)
	{
            if(test->id!=NULL && testParent->parentId!=NULL)
            {
                if(strcmp(test->id,testParent->parentId)==0)
                {
                    return chainedData;
                }
            }
            else
                return chainedData;
	}

	while(chainedData->GetNextArtist() != NULL)
	{
		test = (Dictionnaire*)chainedData->GetNextArtist()->ReturnValue();
		if(strcmp(test->value,(char*)val)==0)
		{
                    if(test->id!=NULL && testParent->parentId!=NULL)
                    {
                        if(strcmp(test->id,testParent->parentId)==0)
                        {
                            return chainedData->GetNextArtist();
                        }
                    }
                    else
                    {
                        return chainedData->GetNextArtist();
                    }
		}
		chainedData = chainedData->GetNextArtist();
	}
	return NULL;
}

QList<Dictionnaire *> ChainedData::SearchTrackOfAlbum(void * val,void *val1)
{
    QList<Dictionnaire *>  listDic;
    Dictionnaire * dparent = new Dictionnaire;
    dparent->parentId = new char[strlen((char*)val1)+1];
    strcpy(dparent->parentId,(char*)val1);
    ChainedData * chainedData = SearchAlbumPrivate(val,dparent);
    if(chainedData!=NULL)
    {
       listDic.push_back((Dictionnaire *)chainedData->ArstistRoot->ReturnValue());   
       listDic.push_back((Dictionnaire *)chainedData->ReturnValue()); 
       if(chainedData->GetLastTrack()!=NULL)
       {
            chainedData = chainedData->GetLastTrack()->GetTrackRoot();
            Dictionnaire * d = (Dictionnaire *)chainedData->ReturnValue();
            listDic.push_back(d);
	    while(chainedData->GetNextTrack() != NULL)
	    {
		Dictionnaire * d = (Dictionnaire *)chainedData->GetNextTrack()->ReturnValue();
                listDic.push_back(d);
                chainedData = chainedData->GetNextTrack();
            }
	}
    }
    delete dparent->parentId;
    delete dparent;
    return listDic;
}




/***************COMMUN*****************/

ChainedType ChainedData::GetType()
{
	return chainedType;
}


bool ChainedData::SetType(ChainedType type)
{
	chainedType = type;
	return true;
}


bool ChainedData::SetValue(void * Value , bool copy)
{
    if(copy == false)
    {
        value = new Dictionnaire();
        memcpy ( value, Value, sizeof(Dictionnaire) );
    }
    else
        value = (Dictionnaire *)Value;
    
    return true;
}

void* ChainedData::ReturnValue()
{
	return (void*)value;
}




ChainedData* ChainedData::GetFirst()
{
	return First;
}



bool ChainedData::SetFirst(ChainedData * Value)
{
	First = Value;
	return true;
}


/*************ARTISTE**************************/

ChainedData* ChainedData::GetNextArtist()
{
	return NextArtist;
}

ChainedData* ChainedData::GetPreviousArtist()
{
	return PreviousArtist;
}


ChainedData* ChainedData::GetLastArtist()
{
	return LastArstist;
}



bool ChainedData::SetNextArtist(ChainedData * Value)
{
	NextArtist = Value;
	return true;
}

bool ChainedData::SetPreviousArtist(ChainedData * Value)
{
	PreviousArtist = Value;
	return true;
}

bool ChainedData::SetLastArtist(ChainedData * Value)
{
	LastArstist = Value;
	return true;
}


bool ChainedData::AddArtist(void * Value, bool a)
{
    
    	//Create new class
	ChainedData *chainedData = new ChainedData();
	//Set the value
	chainedData->SetValue(Value,a);
	//Set the type
	chainedData->SetType(ARTIST);
	//Set the last pointer artist
	LastArstist->SetNextArtist(chainedData);
	//Set the previous pointeur
	chainedData->SetPreviousArtist(LastArstist);
        // qDebug() << "Previous" << LastArstist; 
	chainedData->SetFirst(First);
	chainedData->SetLastArtist(chainedData);
	LastArstist = chainedData;
        //qDebug() << "Last" << LastArstist; 
	return true;	
}


/*************ALBUM**************************/

ChainedData* ChainedData::GetNextAlbum()
{
	return NextAlbum;
}

ChainedData* ChainedData::GetPreviousAlbum()
{
	return PreviousAlbum;
}


ChainedData* ChainedData::GetLastAlbum()
{
	return LastAlbum;
}



bool ChainedData::SetNextAlbum(ChainedData * Value)
{
	NextAlbum = Value;
	return true;
}

bool ChainedData::SetPreviousAlbum(ChainedData * Value)
{
	PreviousAlbum = Value;
	return true;
}

bool ChainedData::SetLastAlbum(ChainedData * Value)
{
	LastAlbum = Value;
	return true;
}

bool ChainedData::SetArstistRoot(ChainedData * Value)
{
	ArstistRoot = Value;
	return true;
}

bool ChainedData::SetAlbumRoot(ChainedData * Value)
{
	AlbumRoot = Value;
	return true;
}


/*************TRACK**************************/
bool ChainedData::SetTrackRoot(ChainedData * Value)
{
	TrackRoot = Value;
	return true;
}

ChainedData* ChainedData::GetArstistRoot()
{
	return ArstistRoot;
}

ChainedData* ChainedData::GetAlbumRoot()
{
	return AlbumRoot;
}

ChainedData* ChainedData::GetTrackRoot()
{
	return TrackRoot;
}

ChainedData* ChainedData::GetLastTrack()
{
	return LastTrack;
}

ChainedData* ChainedData::GetNextTrack()
{
	return NextTrack;
}

ChainedData* ChainedData::GetPreviousTrack()
{
	return PreviousTrack;
}


bool ChainedData::SetNextTrack(ChainedData * Value)
{
	NextTrack = Value;
	return true;
}

bool ChainedData::SetPreviousTrack(ChainedData * Value)
{
	PreviousTrack = Value;
	return true;
}

bool ChainedData::SetLastTrack(ChainedData * Value)
{
	LastTrack = Value;
	return true;
}



bool ChainedData::AddTrack(void * val ,char * Album)
{
    	ChainedData * chainedData = SearchAlbumPrivate(Album,val);
	if(chainedData == NULL)
	{
		return false;
	}
	//Get the last track of Album 
	if(chainedData->GetLastTrack()!=NULL)
	{
		return AddTrack(val,chainedData->GetLastTrack());
	}
	else
	{
		return AddTrack(val,chainedData);
	}

}

bool ChainedData::AddTrack(void * Value,ChainedData *chainedAlbum)
{
        
	bool ret = false;
	switch (chainedAlbum->chainedType)
	{
		ChainedData *chainedData;
		case ALBUM:
			//Create new class
			chainedData = new ChainedData();
			//Set the value
			chainedData->SetValue(Value);
			//Set the type
			chainedData->SetType(TRACK);
			//Set the last pointer artist
			chainedAlbum->SetNextTrack(chainedData);
			//Set the previous pointeur
			chainedData->SetPreviousTrack(NULL);
			//Set the root element
			chainedData->SetFirst(First);
			//Set the root Artist element
			chainedData->SetArstistRoot(chainedAlbum->GetArstistRoot());
			//Set the root album element
			chainedData->SetAlbumRoot(chainedAlbum);
			chainedData->SetLastAlbum(chainedAlbum);
			//Set the root track element
			chainedData->SetTrackRoot(chainedData);
			chainedData->SetLastTrack(chainedData);
			chainedAlbum->SetLastTrack(chainedData);
			ret = true;
			break;

		case TRACK:
			//Create new class
			chainedData = new ChainedData();
			//Set the value
			chainedData->SetValue(Value);
			//Set the type
			chainedData->SetType(TRACK);
			//Set the last pointer track
			chainedAlbum->SetNextTrack(chainedData);
			//Set the previous pointeur
			chainedData->SetPreviousTrack(chainedAlbum);
			//Set the root element
			chainedData->SetFirst(First);
			//Set the root Artist element
			chainedData->SetArstistRoot(chainedAlbum->GetArstistRoot());
			//Set the root album element
			chainedData->SetAlbumRoot(chainedAlbum->GetAlbumRoot());
			chainedData->SetLastAlbum(chainedAlbum->GetLastAlbum());
			//Set the root track element
			chainedData->SetTrackRoot(chainedAlbum->GetTrackRoot());
			chainedAlbum->SetLastTrack(chainedData);
			chainedAlbum->GetAlbumRoot()->SetLastTrack(chainedData);
			chainedData->SetLastTrack(chainedData);
			ret = true;			
			break;

		case ARTIST:
			ret = false;
			break;
	}
	return ret;
	return true;
}



bool ChainedData::AddAlbum(void * val ,char * Artist)
{
	ChainedData * chainedData = SearchArtistPrivate(Artist,val);
 	if(chainedData == NULL)
	{
		return false;
	}
        
	//Get the last Album of artist
	if(chainedData->GetLastAlbum()!=NULL)
	{
		return AddAlbum(val,chainedData->GetLastAlbum());
	}
	else
	{
		return AddAlbum(val,chainedData);
	}

}


bool ChainedData::AddAlbum(void * Value,ChainedData *chainedArstist)
{
	bool ret = false;
	switch (chainedArstist->chainedType)
	{
		ChainedData *chainedData;
		case ARTIST:
			//Create new class
			chainedData = new ChainedData();
			//Set the value
			chainedData->SetValue(Value);
			//Set the type
			chainedData->SetType(ALBUM);
			//Set the last pointer artist
			chainedArstist->SetNextAlbum(chainedData);
			//Set the previous pointeur
			chainedData->SetPreviousAlbum(NULL);
	//Search Artist
			//Set the root element
			chainedData->SetFirst(First);
			//Set the root Artist element
			chainedArstist->SetArstistRoot(chainedArstist);
			chainedData->SetArstistRoot(chainedArstist);
			//Set the root album elementchar*)test
			chainedData->SetAlbumRoot(chainedData);
			chainedData->SetLastAlbum(chainedData);
			chainedArstist->SetLastAlbum(chainedData);
	//Search Artist
			ret = true;
			break;
 
 
		case ALBUM:
			//Create new class
			chainedData = new ChainedData();
			//Set the value
			chainedData->SetValue(Value);
                	//Set the type
			chainedData->SetType(ALBUM);
			//Set the last pointer artist
			chainedArstist->SetNextAlbum(chainedData);
			//Set the previous pointeur
			chainedData->SetPreviousAlbum(chainedArstist);
			//Set the root element
			chainedData->SetFirst(First);
			//Set the root Artist element
			chainedData->SetArstistRoot(chainedArstist->GetArstistRoot());
			//Set the root album element
			chainedData->SetAlbumRoot(chainedArstist->GetAlbumRoot());
			chainedData->SetLastAlbum(chainedData);
			chainedArstist->SetLastAlbum(chainedData);
			chainedArstist->GetAlbumRoot()->SetLastAlbum(chainedData);
			chainedArstist->GetArstistRoot()->SetLastAlbum(chainedData);
			ret = true;			
			break;

		case TRACK:
			ret = false;
			break;
	}
	return ret;
}






