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
    QObject::connect(&DataManager::GetInstance(), SIGNAL(AddToScreen(char *,char*)),this, SLOT(AddMainContent(char *,char *)));
    QObject::connect(&DataManager::GetInstance(), SIGNAL(UpdateVol(char *)),this, SLOT(UpdateVol(char *)));
    QObject::connect(&DataManager::GetInstance(), SIGNAL(UpdateTitre(char *)),this, SLOT(UpdateTitre(char *)));
}



void JavaScriptOperations::UpdateTitre(char* vol)
{
   
  QString arg1 = QString::fromUtf8(vol); 
  qDebug() <<"JavaScriptOperations : " << arg1;   
  QString info = QString("AddTitreInfo('%1')").arg(arg1);
  view->page()->mainFrame()->evaluateJavaScript(info);
}

void JavaScriptOperations::UpdateVol(char* vol)
{
   
  QString arg1 = QString::fromUtf8(vol); 
  qDebug() <<"JavaScriptOperations : " << arg1;   
  QString info = QString("AddVolInfo('%1')").arg(arg1);
  view->page()->mainFrame()->evaluateJavaScript(info);
}



void JavaScriptOperations::AddReaderReceive(int i ,char * Icon)
{
   //qDebug() << Icon;
   const QString arg = QString::fromUtf8(Icon); 
   const QString arg1 = QString::number(i);
   QString info = QString("AddReader('%1','%2')").arg(arg,arg1);
   //qDebug() << info;
   view->page()->mainFrame()->evaluateJavaScript(info);
}

void  JavaScriptOperations::AddMainContent(char * name , char * url)
{

   QString arg2 = QString::fromUtf8(name); 
   const QString arg = arg2.replace("'","|");
   const QString arg1 =  QString::fromUtf8(url); 
   QString info = QString("AddMainContent('%1','%2')").arg(arg,arg1);
   //qDebug() << info;
   view->page()->mainFrame()->evaluateJavaScript(info);
}


void JavaScriptOperations::SetReader(QString val)
{
  //qDebug() << val;    
  char * vol = DataManager::GetInstance().SetReader(val.toInt());  
  QString arg1 = QString::fromUtf8(vol); 
  QString info = QString("AddVolInfo('%1')").arg(arg1);
  view->page()->mainFrame()->evaluateJavaScript(info);
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

QVariantList JavaScriptOperations::search(QString val,QString Type)
{
  type = Type;  
  QList<QString> qlS = DataManager::GetInstance().Search(val, type);
  QVariantList newList;
  foreach( QString item, qlS )
  {
    QString i1 = item.replace(",","#");
    QString i2 = i1.replace("'","|");
    newList << i2;
    //qDebug() << item;
  }
  return newList;
}




QString JavaScriptOperations::display(QString val)
{
    //qDebug() << val;
    QString val1 = val.replace("#",",");
    QString val2 = val1.replace("|","'");
    if(type=="Morceau")
    {
        Dictionnaire * d =DataManager::GetInstance().SearchTrack((char*)val2.toStdString().c_str());
        if(d!=NULL)
        {
           DataManager::GetInstance().Play(d);
        }
    }
    else 
    {
        DataManager::GetInstance().PlayAlbum((char*)val2.toStdString().c_str());
    }
    
    return "";
}


JavaScriptOperations::JavaScriptOperations(const JavaScriptOperations& orig) {
}

JavaScriptOperations::~JavaScriptOperations() {
}

