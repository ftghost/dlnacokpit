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

  pthread_mutex_t htmlTool::mutexHtml;  



size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
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

