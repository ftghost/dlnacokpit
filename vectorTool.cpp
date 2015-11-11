/* 
 * File:   vectorTool.cpp
 * Author: ghost
 * 
 * Created on 6 août 2015, 14:02
 */

#include "vectorTool.h"



int vectorTool::count_number_of_arg(std::vector<Dictionnaire> dict,char * arg)
{
    
    int count = 0;
    if(arg==NULL)
    {
        return -1;
    }
         
    if(dict.size()>0)
    {
        for (std::vector<Dictionnaire>::iterator it = dict.begin() ; it != dict.end(); ++it)
        {
            if(it->name != NULL)
            {
                if(strcmp(it->name,arg)==0)
                {
                    count++;
                }
            }
        }
    }
    return count;
}




bool vectorTool::InsertOrModifyVector(std::vector<Dictionnaire> &res,char * name,char * value)
{
	if(name==NULL || value == NULL)
	{
		return false;
	}



	for(int i=0;i<res.size();i++)
	{
		if(strcmp(res[i].name,name)==0)
		{
			strcpy(res[i].value,value);
			return true;
		}
	}

	Dictionnaire d;
        d.name = new char[strlen(name)+1];
        d.value = new char[strlen(value)+1];
	strcpy(d.name,name);
	strcpy(d.value,value);
	res.push_back(d);
	return true;

}
   
 

bool vectorTool::CleanVector(std::vector<Dictionnaire> &dict)
{
    for(int i=0;i<dict.size();i++)
    {
        if(dict[i].id != NULL)
        {
            delete dict[i].id;
            dict[i].id =NULL;
        }
        if(dict[i].name != NULL)
        {
            delete dict[i].name;
            dict[i].name =NULL;
        }
        if(dict[i].value != NULL)
        {
            delete dict[i].value;
            dict[i].value =NULL;
        }
        if(dict[i].parentId != NULL)
        {
            delete dict[i].parentId;
            dict[i].parentId =NULL;
        }
    }
    dict.clear();
    dict.swap(dict);
    return true;
}


char* vectorTool::get_value_of_arg(std::vector<Dictionnaire> dict,char * arg)
{
   char * ret = NULL; 
   if(arg!=NULL)
   {
    if(dict.size()>0)  
    {
     for (std::vector<Dictionnaire>::iterator it = dict.begin() ; it != dict.end(); ++it)
     {
        if(it->name!=NULL)
        {
            if(strcmp(it->name,arg)==0) 
            {
                if(it->value != NULL)
                {
                  //TODO MEMORY LEAK  
                  ret = new char[strlen(it->value)+1];
                  strcpy(ret,it->value);
                }
                break;
            }  
        }
     }
    }
   }
   return ret;
}


std::vector< std::vector<Dictionnaire> > vectorTool::strip_xml_arg(std::vector<Dictionnaire> dict,char * arg)
{
   std::vector< std::vector<Dictionnaire> > ret; 
   if(arg!=NULL)
   {
    if(dict.size()>0)
    {
         bool first = true;
         std::vector<Dictionnaire>::iterator itTmp = dict.begin() ;
         for (std::vector<Dictionnaire>::iterator it = dict.begin() ; it != dict.end(); ++it)
         {
             if(strcmp(it->name,arg)==0)
             {
                 if(first==true)
                 {  
                    first = false; 
                    itTmp = it;
                 }
                 else
                 {
                     std::vector<Dictionnaire>::iterator itTmpReal = it;
                     std::vector<Dictionnaire> DicTmp(itTmp,itTmpReal);
                     ret.push_back(DicTmp);
                     itTmp = it;
                 }
             }
         } 
         if(first==false)
         {
             std::vector<Dictionnaire> DicTmp(itTmp,dict.end());
             ret.push_back(DicTmp);        
         }
    }
   }
   return ret;
}

vectorTool::vectorTool() {
}

vectorTool::vectorTool(const vectorTool& orig) {
}

vectorTool::~vectorTool() {
}

