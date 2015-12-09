/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   testrecord.cc
 * Author: hanson
 *
 * Created on December 9, 2015, 4:05 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../src/record.h"
#include "string.h"

using namespace std;

void showColumn(Column &x);
void testfunc(Column *x);
/*
 * 
 */
int main(int argc, char** argv) {
    
//    test.num = num;
//    test.rnum = rnum;
//    test.text = text;
//    test.size = strlen(text);
    
    Column *a = new Column();
    testfunc(a);
//    showColumn(*a);

    Record b;
    b.addCol(a);
    b.addCol(a);
    uint64 size;
    b.getNum(&size);
    for (int i=0; i<size; i++) {
        Column *tmp = new Column();
        b.getCol(tmp, i);
        showColumn(*tmp);
    }
//    uint64 num;
//    b.getNum(&num);
//    cout<< num;
    return 0;
}
void testfunc(Column *test){
    char *text = new char[100];
    strcpy(text,"Hello");
    int *num = new int;
    *num = 10;
    real *rnum = new real; 
    rnum->e=0;
    rnum->m=123;
    rnum->sign=0;
    
    test->set(text, 5, COLUMN_TYPE_UTF8);
    test->set(*num);
    test->set(*rnum);
    
//    int *tmp = (int*)malloc(sizeof())
//    int *tmp = memcpy();
}
void showColumn(Column &x){
    
    cout<<"--------------Column ---------------\n";
    cout<<"type:   "<<x.type<<endl;
    cout<<"num:    "<<x.num<<endl;
    cout<<"rnum m: "<<x.rnum.m<<endl;
    cout<<"text:   "<<x.text<<endl;
    cout<<"size:   "<<x.size<<endl;
}