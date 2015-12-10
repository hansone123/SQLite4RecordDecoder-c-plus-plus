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

class Colmn{
private:
public:
    char type;
    static void *make_Colmn(char typ);
    int showTyp();
    char getTyp();
//    virtual int get() = 0;
//    virtual int show() = 0;
};

class ColNull:public Colmn{         /*NULL TYPE*/
private:
public:
    ColNull();
    ColNull(const ColNull&);
    int get();
    int show();
};
class ColZero:public Colmn{         /*ZERO TYPE*/
private:
public:
    ColZero();
    int get();
    int show();
};
class ColOne:public Colmn{          /*ONE TYPE*/
private:
public:
    ColOne();
    int get();
    int show();
};
class ColInt:public Colmn{          /*INT TYPE*/
private:
    uint64 num;
public:
    ColInt();
    int set(uint64 x);
    int get();
    int show();
};
class ColStr:public Colmn{       /* STRING TYPE      UTF8 UTF16-LE UTF16-BE    */ 
private:
    char *str;
    uint64 n;
public:
    ColStr(char typ);
    ~ColStr();
    int set(char *z, int n);
    int get();
    int show();
};

class ColNum:public Colmn{      /* NUM TYPE */
private:
    real rnum;
public:
    ColNum();
    int set(real num);
    int get();
    int show();
};

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

