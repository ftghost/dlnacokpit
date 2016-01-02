/* 
 * File:   JavaScriptOperations.h
 * Author: ghost
 *
 * Created on 8 novembre 2015, 17:55
 */

#ifndef JAVASCRIPTOPERATIONS_H
#define	JAVASCRIPTOPERATIONS_H
#include <QObject>
#include <QtWebKitWidgets/QWebView>


class JavaScriptOperations : public QObject
{
Q_OBJECT    
public:
    JavaScriptOperations(QWebView * );
    JavaScriptOperations(const JavaScriptOperations& orig);
    virtual ~JavaScriptOperations();
    QString type="";

    
public Q_SLOTS:
    void  AddReaderReceive(int,char *);
public Q_SLOTS:    
    void  AddMainContent(char *,char*);
public Q_SLOTS:        
    void UpdateVol(char *);
public Q_SLOTS:            
    void UpdateTitre(char*);
    
    
    Q_INVOKABLE 
    QString display(QString val);

    Q_INVOKABLE 
    void SetReader(QString val);

    Q_INVOKABLE 
    void play();

    Q_INVOKABLE 
    void pause();
    
    Q_INVOKABLE 
    void stop();
    
    Q_INVOKABLE 
    void next();

    Q_INVOKABLE 
    QVariantList search(QString val,QString type);
    
    private:
        QWebView * view;
        int i;

};

#endif	/* JAVASCRIPTOPERATIONS_H */

