/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tableSchema.h
 * Author: hansone123
 *
 * Created on December 16, 2015, 12:50 AM
 */

#ifndef TABLESCHEMA_H
#define TABLESCHEMA_H

#include <string>
#include <vector>
#include "datatype.h"

using namespace std;

struct tableSchema{
    string name;
    vector<string> colname;
    vector<string> coltyp;
    uint64 coln;
};

class tableSchemaCache {

private:
    
public:
    tableSchemaCache();
    tableSchemaCache(const tableSchema& orig);
    virtual ~tableSchemaCache();

    

};

#endif /* TABLESCHEMA_H */

