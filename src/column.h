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
public:
    char type;      /* Record type in SQLITE4 */
    char *text;     /* STRING, BLOB, and TYPED */
    uint64 size;    /* Size of text  */
    real rnum;     /* REAL */
    int num;       /* INT */
    
    int set(char* z, int n, char flag);
    int set(real n);
    int set(int n);
    Column(const Column &col);
    Column();
    ~Column();
};


#endif /* COLUMN_H */

