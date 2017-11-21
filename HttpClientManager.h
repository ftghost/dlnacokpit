/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpClientManager.h
 * Author: ghost
 *
 * Created on 18 novembre 2017, 13:25
 */

#include <QObject>
#include <QNetworkAccessManager>
#include <QWidget>
#include "QNetworkReply"
#ifndef HTTPCLIENTMANAGER_H
#define HTTPCLIENTMANAGER_H

class HttpClientManager : public QWidget
{
 Q_OBJECT    
public:
    HttpClientManager();
    HttpClientManager(const HttpClientManager& orig);
    bool PostUrl();
    virtual ~HttpClientManager();
private:
    QNetworkAccessManager *_uploadManager;
    
private slots:
     void replyFinished(QNetworkReply *reply);
     void upLoadError(QNetworkReply::NetworkError errorCode);
     void OnUploadProgress(qint64 bytesSent, qint64 bytesTotal);    

};

#endif /* HTTPCLIENTMANAGER_H */

