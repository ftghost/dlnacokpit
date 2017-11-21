/* 
 * File:   htmlTool.cpp
 * Author: ghost
 * 
 * Created on 15 août 2015, 14:23
 */

#include "htmlTool.h"
#include "FileTool.h"
#include <sys/types.h>
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
#include <QSettings>
#include <QString>
#include <QDebug>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QDir>
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
       //qDebug() << "Replace car " << m;
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
 
 
 QString htmlTool::ReplaceUrlToCar(QString val)
 {
     
/*
\>  =   %3E
\#  =   %23
\%  =   %25
\{  =   %7B
\}  =   %7D
\|  =   %7C
\\  =   %5C
\^  =   %5E
\~  =   %7E
\[  =   %5B
\]  =   %5D
\`  =   %60
\/  =   %2F
\:  =   %3A
\@  =   %40
\&  =   %26
\$  =   %24
\+  =   %2B
\"  =   %2
\;  =   %3B
*/     
   QStringList childKeys;
  
   childKeys.append("%");
   childKeys.append("%25");  
   
   childKeys.append(" ");
   childKeys.append("%20");   
   
   childKeys.append("!");
   childKeys.append("%21");
   
   childKeys.append("\"");
   childKeys.append("%22");   
   
   childKeys.append("#");
   childKeys.append("%23");   
   
   childKeys.append("$");
   childKeys.append("%24");   
   
    
   
   childKeys.append("&");
   childKeys.append("%26");   
   
   childKeys.append("'");
   childKeys.append("%27");   
   
   childKeys.append("(");
   childKeys.append("%28");   
   
   childKeys.append(")");
   childKeys.append("%29");   
   
   childKeys.append("*");
   childKeys.append("%2A");   
   
   childKeys.append("+");
   childKeys.append("%2B");   
   
   childKeys.append(",");
   childKeys.append("%2C");   
   
   childKeys.append("-");
   childKeys.append("%2D");   
   
   childKeys.append(".");
   childKeys.append("%2E");   
   
   childKeys.append("/");
   childKeys.append("%2F");   
   
   
   childKeys.append("0");
   childKeys.append("%30");   
   childKeys.append("1");
   childKeys.append("%31");   
   childKeys.append("2");
   childKeys.append("%32");   
   childKeys.append("3");
   childKeys.append("%33");   
   childKeys.append("4");
   childKeys.append("%34");   
   childKeys.append("5");
   childKeys.append("%35");   
   childKeys.append("6");
   childKeys.append("%36");   
   childKeys.append("7");
   childKeys.append("%37");   
   childKeys.append("8");
   childKeys.append("%38");   
   childKeys.append("9");
   childKeys.append("%39");      

  
   childKeys.append(":");
   childKeys.append("%3A");   
   
   childKeys.append(";");
   childKeys.append("%3B");   
   
   childKeys.append("<");
   childKeys.append("%3C");   
   
   childKeys.append("=");
   childKeys.append("%3D");   
   
   childKeys.append(">");
   childKeys.append("%3E");   
  
   childKeys.append("?");
   childKeys.append("%3F");
   
   childKeys.append("@");
   childKeys.append("%40");   
   
   childKeys.append("@");
   childKeys.append("%40");   
   childKeys.append("A");
   childKeys.append("%41");   
   childKeys.append("B");
   childKeys.append("%42");   
   childKeys.append("C");
   childKeys.append("%43");   
   childKeys.append("D");
   childKeys.append("%44");   
   childKeys.append("E");
   childKeys.append("%45");   
   childKeys.append("F");
   childKeys.append("%46");   
   childKeys.append("G");
   childKeys.append("%47");   
   childKeys.append("H");
   childKeys.append("%48");   
   
   
   
  //  qDebug() << val;
   // qDebug() << childKeys.count();
    QString res;
    for(int i=0;i<childKeys.count();i++)
    {
        while(val.contains(childKeys[i+1])==true)
        {
            res = val.replace(childKeys[i+1],childKeys[i]);
            val= res;
        }
        i++;
    }
    return res;    
 }

 
 
 
size_t htmlTool::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) 
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory =(char*)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) 
  {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;    
}

 
 
QList<QString> htmlTool::SearchAndSave(char * query)
 {
     
    QList<QString> l;
    QSettings settings("./conf/config.ini", QSettings::IniFormat);
    settings.beginGroup("webSearch");
    pthread_mutex_lock(&mutexHtml); 
    //Save location
    char SaveAbsoluteLocation[500];
    memset(SaveAbsoluteLocation,'\0',500);
    //Url
    char UrlToCall[500];
    memset(UrlToCall,'\0',500);
    
    if(settings.contains("url")==true)
    {
        strcpy(UrlToCall,settings.value("url").toString().toStdString().c_str());
    }
    else
    {
        pthread_mutex_unlock(&mutexHtml);  
        return l;
    }
    
    if(settings.contains("save")==true)
    {
        strcpy(SaveAbsoluteLocation,QDir::currentPath().toStdString().c_str());
        strcat(SaveAbsoluteLocation,settings.value("url").toString().toStdString().c_str());
    }
    else
    {
        pthread_mutex_unlock(&mutexHtml);  
        return l;
    }
    
    CURL *curl;
    struct MemoryStruct chunk;
    static const char *postthis = "query=djemila guidoni";
 
    
    chunk.memory = (char*)malloc(1);  /* will be grown as needed by realloc above */ 
    chunk.size = 0;    /* no data at this point */ 
 
     curl_global_init(CURL_GLOBAL_ALL);
     curl = curl_easy_init();
     if (curl) 
     {
        
        CURLcode res;
        /*
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, "false");
        curl_easy_setopt(curl, CURLOPT_VERBOSE, "true");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Opera/9.80 (J2ME/MIDP; Opera Mini/4.2.14912/870; U; id) Presto/2.4.15");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION,true);
        */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, "false");
        curl_easy_setopt(curl, CURLOPT_URL, UrlToCall);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
        res = curl_easy_perform(curl);
        if(res!=CURLE_OK) 
        {
            qDebug()<< "retour= false";
        }
        else
        {
            qDebug()<< "memory";
            qDebug()<< "memory : \n"<< chunk.memory;
        }
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        free(chunk.memory);
        pthread_mutex_unlock(&mutexHtml);  
     }
     return l;
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
   char SaveAbsoluteLocation[500];
   memset(SaveAbsoluteLocation,'\0',500);
   strcpy(SaveAbsoluteLocation,QDir::currentPath().toStdString().c_str());
   strcat(SaveAbsoluteLocation,SaveLocation);
   //qDebug()<<"Liste jpeg info : " << Adresse << "***" <<SaveLocation ;
   
   curl = curl_easy_init();
   if (curl) 
   {
       
        fp = fopen(SaveAbsoluteLocation,"wb");
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

