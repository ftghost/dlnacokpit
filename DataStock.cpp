/* 
 * File:   DataStock.cpp
 * Author: ghost
 * 
 * Created on 1 novembre 2015, 12:36
 */

#include "DataStock.h"


DataStock DataStock::m_instance=DataStock();


DataStock & DataStock::GetInstance()
{
  return m_instance;
}


DataStock::DataStock()
{
    
}



DataStock::~DataStock()
{

}




