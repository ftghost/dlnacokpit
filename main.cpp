/*
 * File:   main.cpp
 * Author: ghost
 *
 * Created on 31 octobre 2015, 07:54
 */
#include <QApplication>
#include <QtWebKitWidgets/QWebView>
#include "QthreadMainWorker.h"
#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebPage>
#include <QtWebKitWidgets/QWebView>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QWebSettings>
#include <QVariant>
#include "JavaScriptOperations.h"




int main(int argc, char *argv[]) 
{
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);
    QApplication app(argc, argv);
    QthreadMainWorker worker ;
    worker.start();
    QWebView *view;
    view = new QWebView();
    JavaScriptOperations * java = new JavaScriptOperations(view);
    view->page()->mainFrame()->addToJavaScriptWindowObject("myoperations",java);
    view->load(QUrl("qrc:///html/index.html"));
    view->show();

    // create and show your widgets here

    return app.exec();
}
