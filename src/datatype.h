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
#define COLUMN_TYPE_NULL        0x00
#define COLUMN_TYPE_ZERO        0x01
#define COLUMN_TYPE_ONE         0x02
#define COLUMN_TYPE_INT         0x03
#define COLUMN_TYPE_NUM         0x04
#define COLUMN_TYPE_UTF8        0x05
#define COLUMN_TYPE_UTF16LE     0x06
#define COLUMN_TYPE_UTF16BE     0x07
#define COLUMN_TYPE_BLOB        0x08
//#define COLUMN_TYPE_KEY        10
//#define COLUMN_TYPE_TYPED      11

#endif /* DATATYPE_H */

