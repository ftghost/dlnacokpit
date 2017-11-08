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
#include "htmlTool.h"
#include "congig.h"

JavaScriptOperations::JavaScriptOperations(QWebView * View) 
{
    view = View;
    i=0;
    QObject::connect(&DataManager::GetInstance(), SIGNAL(AddReader(int,char *)),this, SLOT(AddReaderReceive(int,char *)));
    QObject::connect(&DataManager::GetInstance(), SIGNAL(AddToScreen(char *,char*,char*)),this, SLOT(AddMainContent(char *,char *,char * )));
    QObject::connect(&DataManager::GetInstance(), SIGNAL(UpdateVol(char *)),this, SLOT(UpdateVol(char *)));
    QObject::connect(&DataManager::GetInstance(), SIGNAL(UpdateTitre(char *)),this, SLOT(UpdateTitre(char *)));
    QObject::connect(&DataManager::GetInstance(), SIGNAL(UpdateRange(int,int,QString)),this, SLOT(UpdateRange(int,int,QString)));
}


void JavaScriptOperations::UpdateRange(int max ,int value,QString maxString)
{
//qDebug() << Icon;
   const QString arg = QString::number(max); 
   const QString arg1 = QString::number(value); 
   QString info = QString("setRange('%1','%2','%3')").arg(arg,arg1,maxString);
   //qDebug() << info;
   view->page()->mainFrame()->evaluateJavaScript(info);   
}


void JavaScriptOperations::UpdateTitre(char* vol)
{
   
  //QString arg1 = QString::fromUtf8(vol); 
  //QString arg = arg1.replace("'"," ");
  QString arg = htmlTool::ReplaceCarTohml(QString::fromUtf8(vol));
  qDebug() <<"JavaScriptOperations : " << arg;   
  QString info = QString("AddTitreInfo('%1')").arg(arg);
  view->page()->mainFrame()->evaluateJavaScript(info);
}

void JavaScriptOperations::UpdateVol(char* vol)
{
   
  QString arg1 = QString::fromUtf8(vol); 
  //qDebug() <<"JavaScriptOperations : " << arg1;   
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

void  JavaScriptOperations::AddMainContent(char * name , char * url,char * info1)
{
   //qDebug()<<"Info 1 : "<< htmlTool::ReplaceCarTohml(info1);
   //QString arg2 = QString::fromUtf8(name); 
   QString arg = htmlTool::ReplaceCarTohml(QString::fromUtf8(name));
   //const QString arg = arg2.replace("'","|");
   const QString arg1 =  QString::fromUtf8(url); 
   QString arg2 = htmlTool::ReplaceHtmlToCar(QString::fromUtf8(info1));
   //qDebug()<<"Info 1 After: "<< arg2;
   QString info = QString("AddMainContent('%1','%2','%3')").arg(arg,arg1,arg2);
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


bool JavaScriptOperations::SetVolume(QString val)
{
    DataManager::GetInstance().SetVolume((char*)val.toStdString().c_str()); 
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


void JavaScriptOperations::ClearQueue()
{
  DataManager::GetInstance().ClearQueue();    
}


QVariantList JavaScriptOperations::search(QString val,QString Type)
{
  type = Type;  
  QList<QString> qlS = DataManager::GetInstance().Search(val, type);
  QVariantList newList;
  int i=0;
  foreach( QString item, qlS )
  {
    if(i==0)
    {
      QString arg = htmlTool::ReplaceCarTohml(item); 
      newList << arg;
    }
    else
    {
        newList << item;
    }
    i++;
    if(i>1)i=0;
    //qDebug() << item;
  }
  return newList;
}

QVariantList JavaScriptOperations::getAllInfo(QString val)
{
  QString val2 = htmlTool::ReplaceHtmlToCar(val);  
  QList<QString> qlS = DataManager::GetInstance().getAllInfo(val2);  
  QVariantList newList;
  foreach( QString item, qlS )
  {
   
      QString arg = htmlTool::ReplaceCarTohml(item); 
      //qDebug() << arg;
      newList << arg;
  }
  return  newList; 
}


QVariantList JavaScriptOperations::addToQueue(QString val,QString genre)
{
    QString val2 = htmlTool::ReplaceHtmlToCar(val); 
    qDebug() << val2;
    QList<QString> qlS = DataManager::GetInstance().AddToPlayList((char*)val2.toStdString().c_str(),(char*)genre.toStdString().c_str()); 
    QVariantList newList;
    foreach( QString item, qlS )
    {

        QString arg = htmlTool::ReplaceCarTohml(item); 
        qDebug() << arg;
        newList << arg;
    }
    return  newList; 
}



QString JavaScriptOperations::display(QString val,QString genre)
{
    //qDebug() << val;
    //QString val1 = val.replace("#",",");
    //QString val2 = val1.replace("|","'");
    QString val2 = htmlTool::ReplaceHtmlToCar(val);
    if(genre=="Morceau")
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

