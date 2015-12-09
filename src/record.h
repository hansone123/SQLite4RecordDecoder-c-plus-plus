/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   record.h
 * Author: hanson
 *
 * Created on December 9, 2015, 3:09 PM
 */

#ifndef RECORD_H
#define RECORD_H

#include "datatype.h"
#include "ErrMsg.h"
#include <vector>
#include "column.h"

using namespace std;


class Record{
private:
    vector<Column> colz;      /* Columns */
    uint64 n;          /* Number of Columns */
    
public:
    Record();
    ~Record();
    int addCol(Column *x);
    int getCol(Column *x, uint64 n);
    int getNum(uint64 *n);
};

#endif /* RECORD_H */

