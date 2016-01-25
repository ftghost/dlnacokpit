/* 
 * File:   congig.h
 * Author: ghost
 *
 * Created on 26 juillet 2015, 17:10
 */

#ifndef CONGIG_H
#define	CONGIG_H
#include <upnp/upnp.h>
#include <upnp/ixml.h>
#include <cstddef>
#include <stdio.h>
#include <string.h>
#include <vector>



enum ChainedType { ARTIST, ALBUM, TRACK };
enum LastChangedType { PLAY, STOP , TRANSITION ,PAUSE , PAUSE_PLAY  };



typedef struct
{
    char *Name;
    char *Genre;
}UiDictionnaire;



typedef struct
{
    int res;
    char *name=NULL;
    char *value=NULL;
    char *id=NULL;
    char *parentId=NULL;
    char *protocol=NULL;
    char *Playurl=NULL;
    char *Imgurl=NULL;
    char *BitRate=NULL;
    bool IsContainer;
    bool IsItem;
}Dictionnaire;





typedef struct
{
    int IdDevice;
    int IdIcon;
    std::vector<Dictionnaire> Dic;
}UpnpListIcon;


typedef struct
{
    int IdDevice;
    bool Isreader;
    bool IsUnknow;
    std::vector<Dictionnaire> Dic;
}UpnpListDevice;






typedef struct
{
    int IdDevice;
    int IdService;
    int IdAction;
    int IdParametre;
    std::vector<Dictionnaire> Dic;
    std::vector<Dictionnaire> DicEtat;
}UpnpListParametreAction;



typedef struct
{
    int IdDevice;
    int IdService;
    int IdAction;
    int IdParametre;
    IXML_Document* xmlActionRequest;
    IXML_Document* xmlActionResponse;
    std::vector<Dictionnaire> Dic;
    std::vector<UpnpListParametreAction> ListParametreAction;
    std::vector<Dictionnaire> DicReponse;
}UpnpListAction;



typedef struct
{
    bool IsContentDirectory;
    bool IsConnectionManager;
    bool IsRenderingControl;
    bool IsAvTransport;
    bool IsUnknow;
    int IdDevice;
    int IdService;
    bool Subscribe;
    int Subscribe_time;
    Upnp_SID SubsId;
    IXML_Document* xmlDocAction;
    std::vector<UpnpListAction> ListAction;
    std::vector<Dictionnaire> Dic;
    
}UpnpListService;





typedef struct
{
  bool icon;
  Upnp_Discovery * u; 
  IXML_Document* xmlDoc;
  char * UrlBase;
  char Icon[100];
  char PathIcon[500];
  int idRoot ;
  std::vector<UpnpListDevice> upnpListDevice;
  std::vector<UpnpListService> upnpListService;
  std::vector<UpnpListIcon> upnpListIcon;
}UpnpRoot;

#endif	/* CONGIG_H */

