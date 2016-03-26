/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileTool.h
 * Author: ghost
 *
 * Created on 19 mars 2016, 14:31
 */

#ifndef FILETOOL_H
#define FILETOOL_H
#include <QString>

class FileTool {
public:
    FileTool();
    FileTool(const FileTool& orig);
    virtual ~FileTool();
    static QString ReadFile(QString);
private:

};

#endif /* FILETOOL_H */

