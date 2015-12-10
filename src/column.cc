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

ColNull::ColNull() { this->type = COLUMN_TYPE_NULL ;}
ColZero::ColZero() { this->type = COLUMN_TYPE_ZERO ;}
ColOne::ColOne() { this->type = COLUMN_TYPE_ONE ;}
ColInt::ColInt() { this->type = COLUMN_TYPE_INT ;}
ColNum::ColNum() { this->type = COLUMN_TYPE_NUM ;}
ColStr::ColStr(char typ) { this->type = typ ;}

int Colmn::showTyp(){

    cout<<"Column type is: ";
    switch(this->type){
        case COLUMN_TYPE_NULL:
            cout<<"COLUMN_TYPE_NULL";
            break;
        case COLUMN_TYPE_ZERO:
            cout<<"COLUMN_TYPE_ZERO";
            break;
        case COLUMN_TYPE_ONE:
            cout<<"COLUMN_TYPE_ONE";
            break;
        case COLUMN_TYPE_INT:
            cout<<"COLUMN_TYPE_INT";
            break;
        case COLUMN_TYPE_NUM:
            cout<<"COLUMN_TYPE_NUM";
            break;
        case COLUMN_TYPE_UTF8:
            cout<<"COLUMN_TYPE_UTF8";
            break;
        case COLUMN_TYPE_UTF16LE:
            cout<<"COLUMN_TYPE_UTF16LE";
            break;
        case COLUMN_TYPE_UTF16BE:   
            cout<<"COLUMN_TYPE_UTF16BE";
            break;
        case COLUMN_TYPE_BLOB:  
            cout<<"COLUMN_TYPE_BLOB";
            break;
    }
    cout<<endl;
}
char Colmn::getTyp(){ return this->type; }
int ColInt::set(uint64 x){ this->num = x; }
int ColStr::set(char* z, int n) {
    this->str = new char[n];
    for (int i=0; i<n; i++)
        *(this->str +i) = *(z+i);
    this->n = n;
}
int ColNum::set(real x) {    this->rnum = x; }
int ColNull::show(){  cout<<"NULL"; }
int ColZero::show(){  cout<<"ZERO";  }
int ColOne::show(){  cout<<"ONE"; }
int ColInt::show(){    cout<<this->num; }
int ColStr::show(){
    if (this->type == COLUMN_TYPE_UTF8){
        cout<<"(UTF8)";                
        for (int i=0; i<this->n; i++)
            printf("%c", *(this->str + i));
    }else if (this->type == COLUMN_TYPE_UTF16LE){
        cout<<"(UTF16LE)";
    }
    else{
        cout<<"(UTF16BE)";
    }
}
int ColNum::show(){
    real num = this->rnum;
    cout<<(num.sign?"-":"+")<<num.m<<"*10^"<<num.e;
}
ColStr::~ColStr(){
    delete str;
}

void *Colmn::make_Colmn(char typ) {
    if (typ == COLUMN_TYPE_NULL)
        return new ColNull();
    else if (typ == COLUMN_TYPE_ZERO)
        return new ColZero();
    else if (typ == COLUMN_TYPE_ONE)
        return new ColOne();
    else if (typ == COLUMN_TYPE_INT)
        return new ColInt();
    else if (typ == COLUMN_TYPE_NUM)
        return new ColNum();
    else if (typ == COLUMN_TYPE_UTF8)
        return new ColStr(typ);
    else if (typ == COLUMN_TYPE_UTF16LE)
        return new ColStr(typ);
    else if (typ == COLUMN_TYPE_UTF16BE)
        return new ColStr(typ);
    else if (typ == COLUMN_TYPE_BLOB)
        return new ColStr(typ);
    else
        return 0;
}

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
    this->type = COLUMN_TYPE_NUM;
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