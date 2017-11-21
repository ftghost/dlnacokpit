/* 
 * File:   htmlTool.h
 * Author: ghost
 *
 * Created on 15 août 2015, 14:23
 */

#ifndef HTMLTOOL_H
#define	HTMLTOOL_H
#include <pthread.h>
#include <QString>
#include <QList>

class htmlTool {
public:
    htmlTool();
    htmlTool(const htmlTool& orig);
    virtual ~htmlTool();
    static bool downloadAndSave(char * Adresse , char * fileName,char * SaveLocation);
    static QList<QString>  SearchAndSave(char *);
    static QString ReplaceCarTohml(QString);
    static QString ReplaceHtmlToCar(QString);
    static QString ReplaceUrlToCar(QString);
private:
    struct MemoryStruct {
                        char *memory;
                        size_t size;
                        };
    static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
    static pthread_mutex_t mutexHtml;

};

#endif	/* HTMLTOOL_H */

