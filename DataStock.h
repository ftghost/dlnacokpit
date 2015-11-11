/* 
 * File:   DataStock.h
 * Author: ghost
 *
 * Created on 1 novembre 2015, 12:36
 */

#ifndef DATASTOCK_H
#define	DATASTOCK_H

class DataStock 
{

public:
     static DataStock & GetInstance();
     virtual ~DataStock();
     

private :
    DataStock& operator= (const DataStock&){}
    DataStock (const DataStock&){}
    DataStock();
    static DataStock m_instance;

};

#endif	/* DATASTOCK_H */

