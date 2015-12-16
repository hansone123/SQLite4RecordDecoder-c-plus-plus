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
#include "../src/rd.h"
#include <iostream>
#include <string.h>
#include "../include/leveldb/db.h"
#include "../src/record.h"

using namespace std;

void show(char *z, int n);
/*
 * 
 */
int main(int argc, char** argv) {
    using namespace std;
    
    //create leveldb
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);
    assert(status.ok());
    
    //Get every kv
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    char *tmp;
    int n;
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        
        char *key = (char *)it->key().data();
        char *val = (char *)it->value().data();
        int keyn = it->key().size();
        int valn = it->value().size();
        
//        cout<<"Key: ";
//        show(key, keyn);
//        cout<<"\nVal: ";
//        show(val, valn);
//        cout<<endl;
        
        uint64 tid;
        uint64 hdrlen;
        if ( RecordDecoder::GetTableID((uchar*)key, keyn, tid) == 0) {
            cout<<"Get Error TableID."<<endl;
            continue;  
        }
        Record r;
        r.setTid(tid);
        
        if ( RecordDecoder::GetColumnsFromValue((uchar*)val, valn, r) == 0){
            cout<<"Get Error Record value."<<endl;
            continue;
        }
        
        
        r.show();
        
        
        cout<<endl;
    }
    
    delete db;
    
    return 0;
}

void show(char *z, int n){
     for (int i=0; i<n;i++)
        printf("%x,",z[i]);
}