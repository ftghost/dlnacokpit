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
    
public Q_SLOTS:
    Q_INVOKABLE
    void submit();
    
 
    Q_INVOKABLE 
    QString display();

    private:
        QWebView * view;
        int i;

};

#endif	/* JAVASCRIPTOPERATIONS_H */

