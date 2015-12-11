/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   column.h
 * Author: hanson
 *
 * Created on December 10, 2015, 1:57 AM
 */

#ifndef COLUMN_H
#define COLUMN_H
#include "datatype.h"

class Column{
private:
    ColType type;      /* Record type in SQLITE4 */
    char *data;     /* STRING, BLOB, and TYPED */
    uint64 size;    /* Size of data  */
public: 
    
    int set(uchar* z, int n);
    int set(char *z, int n);
    int setType(ColType c);
    const char *getData(uint64 &n);
    ColType getType();
    Column();
    Column(const Column &col);
    Column(ColType type);
    ~Column();
};


#endif /* COLUMN_H */

