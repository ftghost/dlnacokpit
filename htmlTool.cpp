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

 
 
 bool htmlTool::SearchAndSave(char * Adresse , char * fileName,char * SaveLocation,bool Again)
 {
     pthread_mutex_lock(&mutexHtml);  
     
     CURL *curl;
      FILE *fp;
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
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, "false");
        curl_easy_setopt(curl, CURLOPT_VERBOSE, "true");
        //curl_easy_setopt(curl, CURLOPT_RETURNTRANSFER, "true");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Opera/9.80 (J2ME/MIDP; Opera Mini/4.2.14912/870; U; id) Presto/2.4.15");
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com/search?q=GUIDONI,DJEMILA,YOUTUBE");
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
        if(Again==true)
        {
            fp = fopen(SaveLocation,"r");
            if(fp == NULL) 
            {
                return false;
            }         
            else
            {
               char bufRead[500];
               bool continu = true;
               while(fgets (bufRead , 500 , fp) && continu==true)
               {
                       char * first = strcasestr(bufRead,"<A HREF=\"");
                       if(first!=NULL)
                       {
                           char * second = strcasestr(bufRead,"\">here");
                           if(second!=NULL)
                           {
                               //Get url
                               char url[500]="";
                               strncpy(url,&bufRead[strlen("<A HREF=\"")],second-bufRead-strlen("\">here")-3);
                               continu = false;
                               qDebug()<<url;
                           }
                       }

               }
               fclose(fp);
            }
        }
        
        
        
        return retour;
     }
     else
    {
        pthread_mutex_unlock(&mutexHtml);  
        return false;
    }  
     /*
     $ch = curl_init();
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
curl_setopt($ch, CURLOPT_VERBOSE, true);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_USERAGENT, $agent);
curl_setopt($ch, CURLOPT_URL,$url);
$result=curl_exec($ch);
var_dump($result);
      */ 
    return true; 
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

