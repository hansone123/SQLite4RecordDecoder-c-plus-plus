/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "record.h"
#include "rd.h"
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
    cout<<"---------------Record---------------\n";
    cout<<"table_id: "<<this->getTableID()<<"\n";
    cout<<"Column num: "<<this->getNum()<<endl;
    for (int i=0; i<this->n; i++) {
        Column co = this->colz[i];
        ColType type = co.getType();
        cout<<"(type:"<<type<<"):  ";
        uint64 sz = 0;
        int64 num = 0;
        uchar* p = (uchar*)co.getData(sz);
        real rnum;
        
        switch (type) {            
            case COL_INT:
                                
                if (TypChg::GetInt(p, sz, num) >0)
                    cout<<num;
                break;
            case COL_NUM:
                
                if (TypChg::GetReal(p, sz, rnum)){
                    cout<<(rnum.sign?"+":"-")<<rnum.m<<"*10^"<<rnum.e;
                }
                break;
            case COL_UTF8:
                char *z;
                z= co.getData(sz);
                for(int j=0; j<sz; j++)
                    printf("%c", *(z+j));
                break;
            case COL_BLOB:
            case COL_TYPED:
                break;
            default :
                
                break;
        }
        cout<<" ";
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


