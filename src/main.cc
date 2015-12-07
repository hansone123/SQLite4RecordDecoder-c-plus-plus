/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cc
 * Author: hanson
 *
 * Created on December 7, 2015, 3:50 PM
 */

#include <cstdlib>
#include <stdio.h>
#include "rd.h"
#include <iostream>
#include <string.h>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    using namespace std;
    
    
    cout<<"Start Varint Test!!"<<endl;
    unsigned char buf[9];
    memset(buf, 0, 9);
    RecordDecoder a;
    int n = a.MakeVarint64(buf, 102400);
    cout<<n;
    for (int i=0; i<n;i++){
        printf("%d,",buf[i]);
    }
    uint64 *num = new uint64();
    int n2;
    n2 = a.GetVarint64(buf, n, num);
    
    cout<<n2<<endl;
    cout<<*num;
    return 0;
}

