/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "record.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>



Record::Record(){
    this->n = this->colz.size();
}
Record::~Record(){
}
int Record::getCol(Column *x, uint64 n){
    if ( n >= this->n)
        return ErrColumnGet;
    
    x = &(this->colz[n]);
    return NormalOK;
}
void Record::show(){
    cout<<"---------------Record---------------";
    for (int i=0; i<this->n; i++) {
        Column co = this->colz[i];
        cout<<"(type:"<<co.getType()<<"):  ";
        switch (co.getType()) {
            case COL_INT:
            case COL_NUM:
            case COL_UTF8:
            case COL_BLOB:
            case COL_TYPED:
            default :
                break;
        }
     
    }
}
uint64 Record::getNum() { return this->n; }
uint64 Record::getTableID() { return this->tid; }
int Record::setTid(const uint64 &t){
    this->tid = t;
    if (this->tid <1 )
        return ErrTableID;
    return NormalOK;
}
int Record::addCol(const Column &x){
    
    this->colz.push_back(x);
    this->n = this->colz.size();
    return NormalOK;
}


