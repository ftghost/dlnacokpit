/* 
 * File:   QthreadMainWorker.cpp
 * Author: ghost
 * 
 * Created on 8 novembre 2015, 15:56
 */

#include "UpnpDiscover.h"
#include "QthreadMainWorker.h"

QthreadMainWorker::QthreadMainWorker() {
}

QthreadMainWorker::QthreadMainWorker(const QthreadMainWorker& orig) {
}

QthreadMainWorker::~QthreadMainWorker() {
}

void QthreadMainWorker::run()
{
    UpnpDiscover::GetInstance().start();
}