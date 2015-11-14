/* 
 * File:   JavaScriptOperations.cpp
 * Author: ghost
 * 
 * Created on 8 novembre 2015, 17:55
 */

#include "JavaScriptOperations.h"
#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebPage>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QWebSettings>
#include <QVariant>
#include "DataManager.h"
#include "congig.h"

JavaScriptOperations::JavaScriptOperations(QWebView * View) 
{
    view = View;
    i=0;
    qDebug() << "In constructor";
}

void JavaScriptOperations::submit()
{
    QVariant f1result = view->page()->mainFrame()->evaluateJavaScript("test()");
    qDebug() << f1result.toString();
}


QString JavaScriptOperations::display(QString val)
{
    
    qDebug() << "In display method";
    Dictionnaire *d = DataManager::GetInstance().SearchTrackFull((char*)val.toStdString().c_str());
    if(d!=NULL)
    {
        DataManager::GetInstance().Play(d);
       return QString::fromUtf8(d->value);
    }
    else
        return QString::fromUtf8("");
}


JavaScriptOperations::JavaScriptOperations(const JavaScriptOperations& orig) {
}

JavaScriptOperations::~JavaScriptOperations() {
}

