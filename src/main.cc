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
#include "../include/leveldb/db.h"

using namespace std;

void showChar(char *z, int n);
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
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        
        char *key = (char *)it->key().data();
        char *val = (char *)it->value().data();
        int keyn = it->key().size();
        int valn = it->value().size();
        cout<<"Key: ";
        showChar(key, keyn);
        cout<<"\nVal: ";
        showChar(val, valn);
        cout<<endl;
        
        uint64 tid;
        uint64 hdrlen;
        RecordDecoder::GetTableID((uchar*)key, keyn, &tid);
        cout<<"table_id: "<<tid<<"\n";
        RecordDecoder::GetHeader((uchar*)val, valn);
        
        
        cout<<endl;
    }
    
    delete db;
    
    return 0;
}

void showChar(char *z, int n){
     for (int i=0; i<n;i++)
        printf("%d,",z[i]);
}