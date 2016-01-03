/* 
 * File:   htmlTool.cpp
 * Author: ghost
 * 
 * Created on 15 août 2015, 14:23
 */

#include "htmlTool.h"

#include <sys/types.h>
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
#include <QSettings>
#include <QDebug>

  pthread_mutex_t htmlTool::mutexHtml;  



size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}  
  



 QString htmlTool::ReplaceCarTohml(QString val)
 {
    //Get ini file
    QString res = val; 
    QSettings settings("./conf/config.ini", QSettings::IniFormat);
    settings.beginGroup("CarToHtml");
    //const QStringList childKeys = settings.childKeys(); 
   
    for(int i=0;i<val.length();i++)
    {
       QString m= val.mid(i,1 );
       //qDebug() << m;
       if(settings.contains(m)==true)
       {
          QString tmp  = settings.value(m).toString()+";"; 
          res = res.replace(val[i],tmp); 
       }
    }
    return res;
 }
    
 QString htmlTool::ReplaceHtmlToCar(QString val)
 {
     //Get ini file
    QString res = val; 
    QSettings settings("./conf/config.ini", QSettings::IniFormat);
    settings.beginGroup("CarToHtml");
    const QStringList childKeys = settings.childKeys(); 
   
    for(int i=0;i<childKeys.count();i++)
    {
        if(val.contains(settings.value(childKeys[i]).toString())==true)
        {
            QString tmp = settings.value(childKeys[i]).toString()+";";
            res = val.replace(tmp,childKeys[i]);
        }
    }
    return res;    
 }

bool htmlTool::downloadAndSave(char * Adresse , char * fileName,char * SaveLocation)
{
   pthread_mutex_lock(&mutexHtml);  
   FILE *fp;
   CURL *curl;
   CURLcode res;
   char url[500];
   memset(url,'\0',500);
   sprintf(url,"%s%s",Adresse,fileName);
   
   
   
   curl = curl_easy_init();
   if (curl) 
   {
       
        fp = fopen(SaveLocation,"wb");
        if(fp == NULL) 
        {
             curl_easy_cleanup(curl);
             pthread_mutex_unlock(&mutexHtml);  
            return false;
        }
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        bool retour = true;
        res = curl_easy_perform(curl);
        if(res!=CURLE_OK) 
            retour= false;
        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
        pthread_mutex_unlock(&mutexHtml);  
        return retour;
   }
   else
   {
        pthread_mutex_unlock(&mutexHtml);  
        return false;
   }
 }




htmlTool::htmlTool() {
}

htmlTool::htmlTool(const htmlTool& orig) {
}

htmlTool::~htmlTool() {
}

