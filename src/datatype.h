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
enum ColType{
     COL_NULL, COL_ZERO, COL_ONE, COL_INT, COL_NUM,         
     COL_UTF8, COL_UTF16LE, COL_UTF16BE, COL_BLOB,
     COL_TYPED
};

#endif /* DATATYPE_H */

