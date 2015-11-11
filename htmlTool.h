/* 
 * File:   htmlTool.h
 * Author: ghost
 *
 * Created on 15 août 2015, 14:23
 */

#ifndef HTMLTOOL_H
#define	HTMLTOOL_H
#include <pthread.h>

class htmlTool {
public:
    htmlTool();
    htmlTool(const htmlTool& orig);
    virtual ~htmlTool();
    static bool downloadAndSave(char * Adresse , char * fileName,char * SaveLocation);
private:
    static pthread_mutex_t mutexHtml;

};

#endif	/* HTMLTOOL_H */

