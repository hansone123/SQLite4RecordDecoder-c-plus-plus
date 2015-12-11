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

int show(const char *a, uint64 &n);
/*
 * 
 */
int main(int argc, char** argv) {
    
    Column a(COL_UTF8);
    a.set("123", 3);
    uint64 s = 0;
    const char *b = a.getData(s);
    show(b, s);
//    cout<<a.getType();
//    showColumn(*a);
    for (int i=0; i<10; i++ ){
        Column c;
        c.setType(COL_UTF8);
        c.set("a",1);
    }
    Record rec;
//    rec.addCol(a);
//    rec.addCol(a);
//    rec.addCol(a);
//    uint64 size = rec.getNum();
//    for (int i=0; i<size; i++) {
//    }
//    uint64 num;
//    b.getNum(&num);
//    cout<< num;
    return 0;
}

int show(const char *a, uint64 &n){
    for(int i=0; i<n; i++)
        printf("0x%x ", *(a+i));
    cout<<endl;
}