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
#include <qt4/QtCore/qnamespace.h>
#include "JavaScriptOperations.h"
#include "ServeFiles.h"
#include "htmlTool.h"





int main(int argc, char *argv[]) 
{
    
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);
    QApplication app(argc, argv);
    ServeFiles * sF = new ServeFiles();
    htmlTool::SearchAndSave("http://www.my-ajax-site.com \'https://ajax.googleapis.com/ajax/services/search/web?v=1.0&q=Paris%20Hilton'","","test.txt");
    QWebView *view;
    view = new QWebView();
    view->setContextMenuPolicy(Qt::NoContextMenu);
    view->setAttribute(Qt::WA_AcceptTouchEvents, false);
    view->page()->settings()->setAttribute(QWebSettings::AutoLoadImages,true);
    JavaScriptOperations * java = new JavaScriptOperations(view);
    view->page()->mainFrame()->addToJavaScriptWindowObject("myoperations",java);
    view->load(QUrl("qrc:///html/index.html"));
    view->show();
    QthreadMainWorker worker ;
    worker.start();

    // create and show your widgets here
   // QObject::connect(&app, SIGNAL(aboutToQuit()), view, SLOT(closing()));
    return app.exec();
}
