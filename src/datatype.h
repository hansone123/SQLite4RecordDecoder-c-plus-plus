/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   datatype.h
 * Author: hansone123
 *
 * Created on December 8, 2015, 12:34 AM
 */

#ifndef DATATYPE_H
#define DATATYPE_H


typedef unsigned char uchar;
typedef unsigned long long int uint64;
typedef long long int int64;
typedef struct real_num {
  unsigned char sign;     /* Sign of the overall value */
  unsigned char approx;   /* True if the value is approximate */
  short e;                /* The exponent. */
  uint64 m;       /* The significant */
}real;


/*for record type*/
#define COLUMN_TYPE_NULL        1
#define COLUMN_TYPE_ZERO        2
#define COLUMN_TYPE_ONE         3
#define COLUMN_TYPE_INT         4
#define COLUMN_TYPE_REAL        5
#define COLUMN_TYPE_UTF8        6
#define COLUMN_TYPE_UTF16LE     7
#define COLUMN_TYPE_UTF16BE     8
#define COLUMN_TYPE_BLOB        9
#define COLUMN_TYPE_KEY        10
#define COLUMN_TYPE_TYPED      11

#endif /* DATATYPE_H */

