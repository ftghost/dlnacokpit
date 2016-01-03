/* 
 * File:   UpnpActionFactory.cpp
 * Author: ghost
 * 
 * Created on 12 août 2015, 17:45
 */

#include "UpnpActionFactory.h"
#include <QSettings>
#include "vectorTool.h"
#include "xmlTool.h"
#include "UpnpDiscover.h"
#include <upnp/upnptools.h>
#include <QThread>
#include <QDebug>

UpnpActionFactory::UpnpActionFactory() 
{
  
       
}
pthread_mutex_t UpnpActionFactory::mutexAction;
UpnpActionFactory UpnpActionFactory::m_instance=UpnpActionFactory();

bool UpnpActionFactory::CreateAction(UpnpListAction &Action,char * ActionName,char *url,char * ServiceType,std::vector<Dictionnaire> data,char *UrlBase)
{
    pthread_mutex_lock(&mutexAction);
    try
    {
        //Get ini file
        QSettings settings("./conf/config.ini", QSettings::IniFormat);
        settings.beginGroup(ActionName);
        Action.xmlActionRequest = NULL;
        Action.xmlActionResponse = NULL;
        for(int j =0;j<Action.ListParametreAction.size();j++)
        {
            char * InOut = vectorTool::get_value_of_arg(Action.ListParametreAction[j].Dic,"direction");
            if(InOut == NULL)
            {
                continue;
            }
            else
            {
                if(strcmp(InOut,"in")==0)
                {
                    //Get the name
                    char * ParameterName = vectorTool::get_value_of_arg(Action.ListParametreAction[j].Dic,"name");
                    if(ParameterName==NULL)
                    {
                        continue;
                    }
                    else
                    {
                       //Search the value in data
                       char * ParameterValue = NULL;
                       if(data.size()>0)
                       {
                            ParameterValue = vectorTool::get_value_of_arg(data,ParameterName);
                       }

                       if(ParameterValue == NULL)
                       {
                           //Try to ini file
                           if(settings.contains(ParameterName)==true)
                           {
                                QString tmp  = settings.value(ParameterName).toString();
                                QByteArray ba = tmp.toLatin1();
                                ParameterValue = (char *)ba.data();
                                if(strcmp(ParameterValue,"empty")==0)
                                {
                                    strcpy(ParameterValue,"");
                                }
                                int  i_res = UpnpAddToAction(&Action.xmlActionRequest, ActionName,ServiceType,ParameterName, ParameterValue );
                                if ( i_res != UPNP_E_SUCCESS )
                                {
                                    settings.endGroup();
                                    pthread_mutex_unlock(&mutexAction);
                                    return false;
                                }
                           }
                           else
                           {
                               settings.endGroup();
                               return false;
                           }
                       }
                       else
                       {
                            //qDebug() << "Parametre Name : " << ParameterName<<" ** : "<<ParameterValue;  
                            int  i_res = UpnpAddToAction(&Action.xmlActionRequest, ActionName,ServiceType,ParameterName, ParameterValue );
                            if ( i_res != UPNP_E_SUCCESS )
                            {
                               settings.endGroup();
                               pthread_mutex_unlock(&mutexAction);
                               return false;

                            } 
                       }
                   }

               }
           }
        }
        settings.endGroup();

        int  i_res = UpnpSendAction( UpnpDiscover::GetInstance().GetHandle(), url,ServiceType, NULL, Action.xmlActionRequest, &Action.xmlActionResponse );
        if ( i_res != UPNP_E_SUCCESS )
        {
            qDebug() << i_res;
            pthread_mutex_unlock(&mutexAction);
            return false;
        }
        else
        {
           Action.DicReponse.clear();
           Action.DicReponse.swap(Action.DicReponse);
           for(int j =0;j<Action.ListParametreAction.size();j++)
           {
                   char * InOut = vectorTool::get_value_of_arg(Action.ListParametreAction[j].Dic,"direction");
                   if(InOut==NULL)
                   {
                       continue;
                   }
                   else
                   {
                    if(strcmp(InOut,"out")==0)
                    {
                         char * ParameterName = vectorTool::get_value_of_arg(Action.ListParametreAction[j].Dic,"name");
                         if(ParameterName==NULL)
                         {
                             continue;
                         }
                         else
                         {
                             char * result = xmlTool::get_argument_value(Action.xmlActionResponse ,ParameterName);
                             Dictionnaire d;
                             d.name = new char[strlen(ParameterName)+1];
                             d.value = new char[strlen(result)+1];
                             strcpy(d.name,ParameterName);
                             strcpy(d.value,result);
                             Action.DicReponse.push_back(d);
                         }
                    }
                   }
           }
        }
        ixmlDocument_free( Action.xmlActionRequest );
        ixmlDocument_free( Action.xmlActionResponse );
        pthread_mutex_unlock(&mutexAction);
        return true;
    }
    catch(...)
    {
        pthread_mutex_unlock(&mutexAction);
        return false;
    }
}

UpnpActionFactory & UpnpActionFactory::GetInstance()
{
  return m_instance;
}

UpnpActionFactory::~UpnpActionFactory()
{
    
}

