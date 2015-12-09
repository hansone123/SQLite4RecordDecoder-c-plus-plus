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
    Column a;
    testfunc(&a);
    showColumn(a);
    return 0;
}
void testfunc(Column *x){
    char *text = new char[100];
    strcpy(text,"Hello");
    int *num = new int;
    *num = 10;
    real *rnum = new real; 
    rnum->e=0;
    rnum->m=123;
    rnum->sign=0;
    
    Column *test = new Column();
    test->type = 2;
    test->num = *num;
    test->rnum = *rnum;
    test->size = sizeof(text);
    test->text = (char *)malloc(test->size);
    strncpy(test->text, text, test->size);
    delete text;
    delete num;
    delete rnum;
    
    x=test;
    showColumn(*x);
}
void showColumn(Column &x){
    cout<<"Column content:\n";
    cout<<"-----------------------------\n";
    cout<<"type:   "<<x.type<<endl;
    cout<<"num:    "<<x.num<<endl;
    cout<<"rnum m: "<<x.rnum.m<<endl;
    cout<<"text:   "<<x.text<<endl;
    cout<<"size:   "<<x.size<<endl;
}