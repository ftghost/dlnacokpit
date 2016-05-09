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
    static QList<QString>  SearchAndSave(char * Adresse ,char * SaveLocation,bool Again );
    static bool SearchAndSave(char * Adresse ,char * SaveLocation);
    static QString ReplaceCarTohml(QString);
    static QString ReplaceHtmlToCar(QString);
    static QString ReplaceUrlToCar(QString);
private:
    static pthread_mutex_t mutexHtml;

};

#endif	/* HTMLTOOL_H */

