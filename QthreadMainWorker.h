/* 
 * File:   QthreadMainWorker.h
 * Author: ghost
 *
 * Created on 8 novembre 2015, 15:56
 */

#ifndef QTHREADMAINWORKER_H
#define	QTHREADMAINWORKER_H

#include <QThread>
#include <QObject>

class QthreadMainWorker :public QThread
{
Q_OBJECT
public:
    QthreadMainWorker();
    QthreadMainWorker(const QthreadMainWorker& orig);
    virtual ~QthreadMainWorker();
private:
    void run();

};

#endif	/* QTHREADMAINWORKER_H */

