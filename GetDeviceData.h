/* 
 * File:   GetDeviceData.h
 * Author: ghost
 *
 * Created on 31 octobre 2015, 10:42
 */

#ifndef GETDEVICEDATA_H
#define	GETDEVICEDATA_H

#include <QThread>
#include "congig.h"



class GetDeviceData :public QThread
{
Q_OBJECT

public:
    GetDeviceData(int);
    GetDeviceData(const GetDeviceData& orig);
    virtual ~GetDeviceData();
    char * GetInstanceId();

signals:
    void termine(int index,bool isOk,bool IsServer);
    
private:
    char InstanceId[10];
    int rootIndex;
    UpnpRoot u;
    UpnpListService serviceContentDirectory;
    UpnpListAction  actionBrowseDirectory;
    UpnpListService serviceConnectionManager;
    UpnpListAction  actionConnectionManager;    
    char urlControl[500]; 
    char ServiceType[500]; 
    bool GetSerciceType();
    bool GetSerciceUrlControl();
    UpnpListService GetServiceContentDirectory();
    UpnpListAction GetActionContentDirectory(char *);
    UpnpListService GetServiceConnectionManager();
    UpnpListAction GetActionConnectionManager(char *);
    std::vector<Dictionnaire>  GetRootData();
    std::vector<Dictionnaire>  GetNexttData(Dictionnaire );
    void run();
};

#endif	/* GETDEVICEDATA_H */

