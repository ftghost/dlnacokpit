/* 
 * File:   xmlTool.h
 * Author: ghost
 *
 * Created on 1 août 2015, 14:58
 */

#ifndef XMLTOOL_H
#define	XMLTOOL_H
#include "congig.h"

class xmlTool {
public:
    xmlTool();
    xmlTool(const xmlTool& orig);
    virtual ~xmlTool();
    static char * get_argument_value(IXML_Document * doc, const char *item);
    static std::vector<Dictionnaire> get_list_arg_value(IXML_Document* doc, const char* item , const char* item1);
    static std::vector<Dictionnaire> get_list_arg_value_by_char(char* doc, const char* item , const char* item1);
    static char * get_lastChange(char* doc);
    static char * get_VolumeChange(char* doc);
    
private:
    static void private_get_list_arg_value(IXML_NodeList * nodelist);
    static std::vector<Dictionnaire> ListOfValue ;

};

#endif	/* XMLTOOL_H */

