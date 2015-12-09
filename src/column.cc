/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   column.cc
 * Author: hanson
 * 
 * Created on December 10, 2015, 1:57 AM
 */

#include "column.h"
#include "datatype.h"
#include "ErrMsg.h"
#include <string.h>

int Column::set(char* z, int n, char flag){
    this->size = n;
    this->text = new char(n);
    memcpy(this->text, z, n);
    this->type = flag;
    
    return NormalOK;
}
int Column::set(real n){
    this->rnum = n;
    this->type = COLUMN_TYPE_INT;
    return NormalOK;
}
int Column::set(int n){
    this->num = n;
    this->type = COLUMN_TYPE_REAL;
    return NormalOK;
}
Column::Column(const Column &col){
    this->num = col.num;
    this->rnum = col.rnum;
    this->size = col.size;
    this->type = col.type;
    this->text = new char[col.size];
    memcpy(this->text, col.text, col.size);
            
}
Column::Column(){
    type = COLUMN_TYPE_NULL;
    size = 0;
}

Column::~Column(){
}