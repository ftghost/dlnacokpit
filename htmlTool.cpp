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

 

 
 
bool htmlTool::SearchAndSave(char * Adresse , char * SaveLocation)
 {
     

     pthread_mutex_lock(&mutexHtml);  
     char SaveAbsoluteLocation[500];
     memset(SaveAbsoluteLocation,'\0',500);
     strcpy(SaveAbsoluteLocation,QDir::currentPath().toStdString().c_str());
     strcat(SaveAbsoluteLocation,SaveLocation);
     bool retour = true;     
     CURL *curl;
     FILE *fp;
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
        
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, "false");
        curl_easy_setopt(curl, CURLOPT_VERBOSE, "true");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Opera/9.80 (J2ME/MIDP; Opera Mini/4.2.14912/870; U; id) Presto/2.4.15");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION,true);
        curl_easy_setopt(curl, CURLOPT_URL, Adresse);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        if(res!=CURLE_OK) 
            retour= false;
        curl_easy_cleanup(curl);
        fclose(fp);
        pthread_mutex_unlock(&mutexHtml);  
     }
     return retour;
}
 
 
 QList<QString> htmlTool::SearchAndSave(char * Adresse , char * SaveLocation,bool Again)
 {
     //qDebug()<< "SearchAndSave  : " << Adresse;
     QList<QString> l;
     pthread_mutex_lock(&mutexHtml);  
     char SaveAbsoluteLocation[500];
     memset(SaveAbsoluteLocation,'\0',500);
     strcpy(SaveAbsoluteLocation,QDir::currentPath().toStdString().c_str());
     strcat(SaveAbsoluteLocation,SaveLocation);
     CURL *curl;
     FILE *fp;
     curl = curl_easy_init();
     if (curl) 
     {
        fp = fopen(SaveAbsoluteLocation,"wb");
        if(fp == NULL) 
        {
            //qDebug()<< "fp NULL  : " << Adresse;
             curl_easy_cleanup(curl);
             pthread_mutex_unlock(&mutexHtml);  
            return l;
        }  
        
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, "false");
        curl_easy_setopt(curl, CURLOPT_VERBOSE, "false");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.2) Gecko/20090729 Firefox/3.5.2 GTB5");
        curl_easy_setopt(curl, CURLOPT_URL, Adresse);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        bool retour = true;
        res = curl_easy_perform(curl);
        if(res!=CURLE_OK) 
        {
            //qDebug()<< "CURLE_OK FALSE  : ";
            retour= false;
        }
        curl_easy_cleanup(curl);
        fclose(fp);
        pthread_mutex_unlock(&mutexHtml);  
     }
     if(Again==true)     
     {
        //qDebug()<< "Again  : ";
        QString res = FileTool::ReadFile(SaveAbsoluteLocation);
        QWebPage page;
        page.mainFrame()->setHtml(res);
        QWebElement htmlElement = page.mainFrame()->findFirstElement("A");
        QString href = htmlElement.attribute("href");
        if (!href.isEmpty())
        {
            //qDebug()<<"Href  : " << (char*)href.toStdString().c_str() ;
            return SearchAndSave((char*)href.toStdString().c_str(),"/tmp/test1.txt",false);
        }
        else
        {
            //qDebug()<<"Href  : empty";
        }
     }
     else
     {
        QString res = FileTool::ReadFile(SaveAbsoluteLocation);
        QWebPage page;
        page.mainFrame()->setHtml(res);
        QWebElementCollection collection = page.mainFrame()->findAllElements("A");
        int i=0;
        foreach (QWebElement element, collection)
        {
            
            QString href = element.attribute("href");
            if(href.contains("https://www.youtube.com/watch%"))
            {
                int pos=href.indexOf("%3Fv%3D");
                QString id = href.mid(pos+strlen("%3Fv%3D"),11);  
                QString url = "http://www.youtube.com/get_video_info?video_id="+id;
                QString loc = "/tmp/info"+QString::number(i);

                
                SearchAndSave((char*)url.toStdString().c_str(),(char*)loc.toStdString().c_str());
                QString absoluteLoc = QDir::currentPath()+loc;
                QString resu = FileTool::ReadFile(absoluteLoc);
                QStringList myStringList = resu.split("&");
                QString urlJpeg="";
                bool isJpeg = false;
                foreach (QString el, myStringList)
                {
                    if(el.startsWith("iurl") && isJpeg==false)
                    {
                        isJpeg = true;
                        urlJpeg = ReplaceUrlToCar(el.mid(el.indexOf("http")));
                    }
                    
                    if(el.startsWith("url_encoded_fmt_stream_map"))
                    {
                        //qDebug()<<"Liste video info : " << el << "***" ;
                        QStringList myStringList1 = el.split("%26");
                        foreach (QString el1, myStringList1)
                        {
                            if(el1.startsWith("url%3D"))
                            {
                                QString e =ReplaceUrlToCar(el1.mid(strlen("url%3D")));
                                l.append(e);
                                l.append(urlJpeg);
                                htmlTool::downloadAndSave((char*)e.toStdString().c_str() , "","/tmp/video.avi");
                                //qDebug()<<"Liste jpeg info : " << e << "***" <<urlJpeg ;
                                return l;
                            }
                        }
                    }
                }
                i++;
            }
        }
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

