/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpClientManager.cpp
 * Author: ghost
 * 
 * Created on 18 novembre 2017, 13:25
 */

#include "HttpClientManager.h"
#include "QString"
#include "QNetworkRequest"
#include "QByteArray";
#include <QDebug>

HttpClientManager::HttpClientManager() {
}

HttpClientManager::HttpClientManager(const HttpClientManager& orig) {
}

HttpClientManager::~HttpClientManager() 
{
}

bool HttpClientManager::PostUrl()
{
    QNetworkReply *_reply;
    QUrl url = QString("https://www.mp3juices.cc");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");
    //request.setRawHeader("filename", uploadFilename.section('/', -1, -1).toUtf8() );
    
    QByteArray mydata ;
    mydata.append("query=guidoni");
    
    _uploadManager =  new QNetworkAccessManager(this);
    _reply = _uploadManager->post(request,mydata);
 
     connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(upLoadError(QNetworkReply::NetworkError)));
     connect(_reply, SIGNAL(uploadProgress ( qint64 ,qint64 )), this, SLOT( OnUploadProgress(qint64 ,qint64 )));
     connect(_uploadManager,SIGNAL(finished(QNetworkReply*)),SLOT(replyFinished(QNetworkReply*)));
    return true;
}



 void HttpClientManager::replyFinished(QNetworkReply *reply)
 {
     if(reply->error() == QNetworkReply::NoError)
     {
         qDebug()<<"no error.....";
         QByteArray bytes = reply->readAll();  
         QString result(bytes);  
         qDebug()<<result;
     }
     else{
         qDebug() << "replyFinished:  " << reply->error() << " " <<reply->errorString();
     }
 
     QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
     qDebug()<<status_code;
 }

void HttpClientManager::upLoadError(QNetworkReply::NetworkError errorCode)
 {
     qDebug() << "upLoadError  errorCode: " << (int)errorCode;
 }
 
void HttpClientManager::OnUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
     qDebug() << "bytesSent: " << bytesSent << "  bytesTotal: "<< bytesTotal;
}