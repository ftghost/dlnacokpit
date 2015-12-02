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
    QObject::connect(&DataManager::GetInstance(), SIGNAL(AddReader(int,char *)),this, SLOT(AddReaderReceive(int,char *)));
}


void JavaScriptOperations::AddReaderReceive(int i ,char * Icon)
{
   qDebug() << Icon;
   const QString arg = QString::fromUtf8(Icon); 
   const QString arg1 = QString::number(i);
   QString info = QString("AddReader('%1','%2')").arg(arg,arg1);
   qDebug() << info;
   view->page()->mainFrame()->evaluateJavaScript(info);
}



void JavaScriptOperations::SetReader(QString val)
{
  qDebug() << val;    
  DataManager::GetInstance().SetReader(val.toInt());  
}


void JavaScriptOperations::pause()
{
  DataManager::GetInstance().Pause();  
}

void JavaScriptOperations::stop()
{
  DataManager::GetInstance().Stop();  
}

void JavaScriptOperations::next()
{
  DataManager::GetInstance().Next();  
}

void JavaScriptOperations::play()
{
  DataManager::GetInstance().Play();  
}

QVariantList JavaScriptOperations::search(QString val,QString type)
{
    
  QList<QString> qlS = DataManager::GetInstance().Search(val, type);
  QVariantList newList;
  foreach( QString item, qlS )
        newList << item;
  return newList;
}




QString JavaScriptOperations::display(QString val)
{
    qDebug() << val;
    Dictionnaire * d =DataManager::GetInstance().SearchTrack((char*)val.toStdString().c_str());
    if(d!=NULL)
    {
       DataManager::GetInstance().Play(d);
    }
    return "";
}


JavaScriptOperations::JavaScriptOperations(const JavaScriptOperations& orig) {
}

JavaScriptOperations::~JavaScriptOperations() {
}

