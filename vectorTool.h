/* 
 * File:   vectorTool.h
 * Author: ghost
 *
 * Created on 6 août 2015, 14:02
 */

#ifndef VECTORTOOL_H
#define	VECTORTOOL_H
#include "congig.h"

class vectorTool {
public:
    vectorTool();
    vectorTool(const vectorTool& orig);
    virtual ~vectorTool();
    static int count_number_of_arg(std::vector<Dictionnaire> ,char * arg);
    static char* get_value_of_arg(std::vector<Dictionnaire> ,char * arg);
    static std::vector< std::vector<Dictionnaire> > strip_xml_arg(std::vector<Dictionnaire> ,char * arg);
    static bool InsertOrModifyVector(std::vector<Dictionnaire> &,char * name, char *value);
    static bool CleanVector(std::vector<Dictionnaire> &);
private:

};

#endif	/* VECTORTOOL_H */

