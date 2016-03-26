/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileTool.cpp
 * Author: ghost
 * 
 * Created on 19 mars 2016, 14:31
 */

#include "FileTool.h"
#include <QFile>
#include <QTextStream>

FileTool::FileTool() {
}

FileTool::FileTool(const FileTool& orig) {
}

FileTool::~FileTool() {
}

QString FileTool::ReadFile(QString file)
{
    QFile f(file);
    if (!f.open(QFile::ReadOnly | QFile::Text)) 
    {
        return "";
    }
    QTextStream s1(&f);
    QString res = s1.readAll();
    f.close();
    return res;
}