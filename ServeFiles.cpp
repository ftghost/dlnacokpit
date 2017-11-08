/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServeFiles.cpp
 * Author: ghost
 * 
 * Created on 7 mars 2016, 13:28
 */

#include "ServeFiles.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <QDebug>
#include <QSettings>
#define PAGE "<html><head><title>File not found</title></head><body>File not found</body></html>"

ServeFiles::ServeFiles() 
{
    //Get ini file
    QSettings settings("./conf/config.ini", QSettings::IniFormat);
    settings.beginGroup("HttpServ");
    int Port = 8081;
    if(settings.contains("Port")==true)
    {
        bool ok;
        Port = settings.value("Port").toInt(&ok);
        if(ok==false)
        {
          Port = 8081;  
        }
    }
    //qDebug()<< "Port = " << Port;
   
    d = MHD_start_daemon (MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
                        Port,
                        NULL, NULL, &ahc_echo, (void*)PAGE, MHD_OPTION_END);

}



 ssize_t ServeFiles::file_reader (void *cls,uint64_t pos,char *buf, size_t max)
 {
   FILE *file = (FILE*)cls;
  (void)  fseek (file, pos, SEEK_SET);
   return fread (buf, 1, max, file);  
 }
 
 void ServeFiles::free_callback (void *cls)
{
  FILE *file = (FILE *)cls;
  fclose (file);
}
 
 
 
 int ServeFiles::ahc_echo (void *cls,struct MHD_Connection *connection,const char *url,const char *method,const char *version,const char *upload_data,size_t *upload_data_size, void **ptr)
 {
     static int aptr;
     struct MHD_Response *response;
     int ret;
     FILE *file;
     int fd;
     struct stat buf;

     if ( (0 != strcmp (method, MHD_HTTP_METHOD_GET)) &&  (0 != strcmp (method, MHD_HTTP_METHOD_HEAD)) )  return MHD_NO;              /* unexpected method */
     if (&aptr != *ptr)
       {
         /* do never respond on first call */
         *ptr = &aptr;
         return MHD_YES;
       }
     *ptr = NULL;                  /* reset when done */
     file = fopen (&url[1], "rb");
     qDebug()<< "Url = " << &url[1];
     if (NULL != file)
       {
         fd = fileno (file);
         if (-1 == fd)
           {
             (void) fclose (file);
             return MHD_NO; /* internal error */
           }
         if ( (0 != fstat (fd, &buf)) ||
              (! S_ISREG (buf.st_mode)) )
           {
             /* not a regular file, refuse to serve */
             fclose (file);
             file = NULL;
           }
       }
     if (NULL == file)
       {
         response = MHD_create_response_from_buffer (strlen (PAGE),
                                                     (void *) PAGE,
                                                     MHD_RESPMEM_PERSISTENT);
         ret = MHD_queue_response (connection, MHD_HTTP_NOT_FOUND, response);
         MHD_destroy_response (response);
       }
     else
       {
         response = MHD_create_response_from_callback (buf.st_size, 32 * 1024,     /* 32k page size */
                                                       &file_reader,
                                                       file,
                                                       &free_callback);
         if (NULL == response)
           {
             fclose (file);
             return MHD_NO;
           }
         ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
         MHD_destroy_response (response);
       }
     return ret;     
 }



ServeFiles::ServeFiles(const ServeFiles& orig) {
}

ServeFiles::~ServeFiles() 
{
    MHD_stop_daemon (d);
}

