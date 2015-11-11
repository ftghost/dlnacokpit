/* 
 * File:   xmlTool.cpp
 * Author: ghost
 * 
 * Created on 1 août 2015, 14:58
 */

#include "xmlTool.h"
#include <QXmlStreamReader>
#include <QDebug>


 std::vector<Dictionnaire> xmlTool::ListOfValue ;
 char * xmlTool::get_argument_value(IXML_Document* doc, const char* item)
  {
    char *ret = NULL;     
    if(doc!=NULL && item != NULL)
    {
        IXML_NodeList *nodeList = NULL;
        IXML_Node *textNode = NULL;
        IXML_Node *tmpNode = NULL;
        nodeList = ixmlDocument_getElementsByTagName(doc, (char *)item);
        if(nodeList) 
        {
            if((tmpNode = ixmlNodeList_item(nodeList, 0))) 
            {
                textNode = ixmlNode_getFirstChild(tmpNode);
                ret = strdup(ixmlNode_getNodeValue(textNode));
            }
            ixmlNodeList_free( nodeList );
        }
    }
    return ret;
 }

 
 
void xmlTool::private_get_list_arg_value(IXML_NodeList* nodelist)
{
        IXML_Node *tmpNode = NULL;
        if(nodelist) 
        {
            int count = ixmlNodeList_length (nodelist );
            for(int i=0;i<count ; i++)
            {    
               tmpNode = ixmlNodeList_item(nodelist, i); 
               if(tmpNode)
               {
                    IXML_NodeList * nodeListTmp= ixmlNode_getChildNodes(tmpNode);  
                    if(nodeListTmp)
                    {
                        int countTmp = ixmlNodeList_length (nodeListTmp );
                        if(countTmp == 1)
                        {
                             Dictionnaire dict;
                             const char * test = ixmlNode_getNodeValue(ixmlNodeList_item(nodeListTmp, 0));
                             if(test !=NULL)
                             {
                                dict.name = new char[strlen(ixmlNode_getNodeName(tmpNode))+1];
                                dict.value = new char[strlen(ixmlNode_getNodeValue(ixmlNodeList_item(nodeListTmp, 0)))+1]; 
                                strcpy(dict.value ,ixmlNode_getNodeValue(ixmlNodeList_item(nodeListTmp, 0))); 
                                strcpy(dict.name , ixmlNode_getNodeName(tmpNode)); 
                             }
                             
                             ListOfValue.push_back(dict);   
                             try
                             {
                                 ixmlNodeList_free( nodeListTmp );
                             }
                             catch(...)
                             {

                             }
                        }
                        else if(nodeListTmp && countTmp!=0)
                        {
                          private_get_list_arg_value(nodeListTmp);  
                        }
                    }
               }
            }
            try
            {
                ixmlNodeList_free( nodelist );
            }
            catch(...)
            {
                
            }
        }
}
 





std::vector<Dictionnaire> xmlTool::get_list_arg_value_by_char(char* docchar, const char* item , const char* item1)
{
    std::vector<Dictionnaire> res;
    Dictionnaire dic; 
    bool adD = false;
    try
    {
        if(docchar ==NULL || item==NULL)
        {
            return res;
        }
        
        //QString test = QString::fromLocal8Bit(docchar);
        QXmlStreamReader xml(docchar);
        while(!xml.atEnd() && !xml.hasError()) 
        {
            if(xml.isEndDocument()==true)
            {
                break;
            }
            
            if(xml.isStartDocument()==true)
            {
                xml.readNext();
                continue;
            }
            
            
            if (xml.isStartElement()==true && xml.name()!=NULL)
            {
               if(xml.name()!=NULL)
               {
                   if(xml.name()=="container"  ||   xml.name()=="item")
                   {
                       if(xml.name()=="container")
                       {
                           dic.IsContainer = true;
                           dic.IsItem = false;
                       }
                       else if(xml.name()=="item")
                       {
                           dic.IsItem = true;
                           dic.IsContainer = false;
                       }
                       else
                       {
                           dic.IsItem = false;
                           dic.IsContainer = false;
                       }
                       foreach(const QXmlStreamAttribute &attr, xml.attributes()) 
                       {
                           if(attr.name() != NULL && attr.value()!=NULL)
                           {
                               if (attr.name().toString() == QLatin1String("id")) 
                               {
                                   dic.id = new char[strlen(attr.value().toString().toStdString().c_str())+1];
                                   strcpy(dic.id,attr.value().toString().toStdString().c_str());
                               }   
                               if (attr.name().toString() == QLatin1String("parentID")) 
                               {
                                   dic.parentId = new char[strlen(attr.value().toString().toStdString().c_str())+1];
                                   strcpy(dic.parentId,attr.value().toString().toStdString().c_str());
                               }   
                           }

                       }
                   }
                   if(xml.name()=="res")
                   {
                     
                       foreach(const QXmlStreamAttribute &attr, xml.attributes()) 
                       {
                           if(attr.name() != NULL && attr.value()!=NULL)
                           {
                               if (attr.name().toString() == QLatin1String("protocolInfo")) 
                               {
                                   dic.protocol = new char[strlen(attr.value().toString().toStdString().c_str())+1];
                                   strcpy(dic.protocol,attr.value().toString().toStdString().c_str());
                               }   
                           }

                       }
                       QString val = xml.readElementText();
                      if(val!=NULL)
                      {
                        dic.Playurl = new char[strlen(val.toStdString().c_str())+1];
                        strcpy(dic.Playurl,val.toStdString().c_str());
                      }
                   }
                   if(xml.name()==item) 
                   {
                       
                      QString val = xml.readElementText();
                      if(val!=NULL)
                      {
                       adD = true;   
                       //TODO MEMORY LEAK      
                       dic.name = new char[strlen(xml.name().toString().toStdString().c_str())+1];
                       dic.value = new char[strlen(val.toStdString().c_str())+1]; 
                       strcpy(dic.name,xml.name().toString().toStdString().c_str());
                       strcpy(dic.value,val.toStdString().c_str());
                      }
                   }
                   
                   
               }
       
            }
            xml.readNext();
            if(xml.hasError()) 
            {
                break;
            }
      }
      if(adD==true)  
        res.push_back(dic);    
      xml.clear();
    }
    catch(...)
    {
        return res;
    }


  return res;
}


std::vector<Dictionnaire> xmlTool::get_list_arg_value(IXML_Document* doc, const char* item , const char* item1)
{
    ListOfValue.clear();
    ListOfValue.swap(ListOfValue);
        
    if(doc == NULL || item==NULL)
    {
        return ListOfValue;
    }
    IXML_NodeList *nodeList = NULL;
    nodeList = ixmlDocument_getElementsByTagName(doc, (char *)item);
    if(nodeList) 
    {
       private_get_list_arg_value(nodeList);
    }
    return ListOfValue;
}
 

xmlTool::xmlTool() 
{
}

xmlTool::xmlTool(const xmlTool& orig) {
}

xmlTool::~xmlTool() {
}

