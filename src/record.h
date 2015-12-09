/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   record.h
 * Author: hanson
 *
 * Created on December 9, 2015, 3:09 PM
 */

#ifndef RECORD_H
#define RECORD_H

#include "datatype.h"



class Column{
public:
    char type;      /* Record type in SQLITE4 */
    char *text;     /* STRING, BLOB, and TYPED */
    uint64 size;    /* Size of text  */
    real rnum;     /* REAL */
    int num;       /* INT */
    
    int set(char *text, int n);
    int set(real n);
    int set(int n);
    Column();
    ~Column();
};

class Record{
public:
    Column *p;      /* Columns */
    int n;          /* Number of Columns */
    Record();
    ~Record();
    int addColumn(Column x);
};

#endif /* RECORD_H */

