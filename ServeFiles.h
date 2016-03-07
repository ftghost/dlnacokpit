/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServeFiles.h
 * Author: ghost
 *
 * Created on 7 mars 2016, 13:28
 */

#ifndef SERVEFILES_H
#define SERVEFILES_H

#include <microhttpd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

class ServeFiles {
public:
    ServeFiles();
    ServeFiles(const ServeFiles& orig);
    virtual ~ServeFiles();
private:
    struct MHD_Daemon *d;
    static ssize_t file_reader (void *cls,uint64_t pos,char *buf, size_t max);
    static int ahc_echo (void *cls,struct MHD_Connection *connection,const char *url,const char *method,const char *version,const char *upload_data,size_t *upload_data_size, void **ptr);
     static void free_callback (void *cls);
    

};

#endif /* SERVEFILES_H */

