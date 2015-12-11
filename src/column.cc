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
#include <iostream>
#include "stdio.h"
#include "datatype.h"
#include "ErrMsg.h"
#include <string.h>

using namespace std;

Column::Column(){
    this->type = COL_NULL;
}
const char *Column::getData(uint64 &n){
    n = this->size;
    return this->data;
}
ColType Column::getType(){
    return this->type;
}
int Column::set(uchar *z, int n){
    this->size = n;
    this->data = new char(n);
    copy(z, z+n, this->data);
    
    return NormalOK;
}
int Column::set(char *z, int n){
    this->size = n;
    this->data = new char(n);
    copy(z, z+n, this->data);
    
    return NormalOK;
}
int Column::setType(ColType c){
    this->type = c;
    
    return NormalOK;
}
Column::Column(const Column &col){
    this->size = col.size;
    this->type = col.type;
    this->data = new char[col.size];
    copy(col.data, col.data + col.size, this->data);
            
}
Column::Column(ColType type){
    this->type = type;
}

Column::~Column(){
}