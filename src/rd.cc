#include "rd.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "ErrMsg.h"
#include "column.h"

using namespace std;
int RecordDecoder::GetColumns(uchar *z, int n, Record &rec){
    
    uint64 type;        /*Datatype*/
    uint64 subtype;     /*Subtype of TEXT */
    uint64 lenHdr;
    uint64 size;
    uint64 ofst;         /*Offset into the data*/
            
    int startHdr;    
    int endHdr;
    int rc;
    int ofstHdr;        /*Offset into the header*/
    
    //Get header
    if( !z ) return NormalOK;
    
    startHdr = TypChg::GetVarint64(z, n, lenHdr);
    endHdr = lenHdr + startHdr;
    
    if (endHdr > n) return ErrHdr;  
    
    for (ofstHdr=startHdr,ofst=endHdr; ofstHdr<endHdr; ) {
        
        ofstHdr += TypChg::GetVarint64(z+ofstHdr, n, type);
        cout<<"type("<<type<<")"<<": ";        
        cout<<"offset: "<<ofst<<endl;
        Column col;
        
        if( type>=22 ){         /* KEY, STRING, BLOB, and TYPED */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            /* STRING, BLOB, KEY, and TYPED */
            subtype = (type-22)%4;
            if( subtype==2 ){               /* KEY */
                size=0;
            }else{             
                size = (type-22)/4;
              if( subtype==0){                
                cout<<"STRING";
                cout<<" SIZE:"<<size<<endl;;
                if (size ==0){
                    col.setType(COL_UTF8);
                }else if( z[ofst]>0x02 ){           /* UTF8 STRING */
                    col.setType(COL_UTF8);
                    col.set((char *)(z+ofst),size);
                }else{
                    if( z[ofst]==0x00 ){            /* UTF8 STRING */
                        col.setType(COL_UTF8);
                        col.set((char*)(z+ofst+1),size-1);
                    
                    }else if( z[ofst] == 0x01 ){    /* UTF16LE STRING */
                        col.setType(COL_UTF16LE);
                        col.set((char*)(z+ofst+1), size-1);
                        
                    }else{                          /* UTF16BE STRING */\
                        col.setType(COL_UTF16BE);
                        col.set((char*)(z+ofst+1), size-1);
                    }
                }
              }else if(subtype ==1){
                cout<<"BLOB";
                cout<<" SIZE:"<<size<<endl;;
                col.setType(COL_BLOB);
                col.set((char*)(z+ofst), size);
              }else if (subtype ==3){
                cout<<"TYPED";
                cout<<" SIZE:"<<size;
              }
            }
          }else if( type<=2 ){  /* NULL, ZERO, and ONE */
            size = 0;
            if(type==0){
                col.setType(COL_NULL);
            }else if(type==1){
                col.setType(COL_ZERO);
            }else if(type==2){
                col.setType(COL_ONE);
            }
          }else if( type<=10 ){ /* INT */
                size = type - 2;
                cout<<"INT";
                cout<<" SIZE:"<<size<<endl;
                
                col.setType(COL_INT);
                col.set((char*)(z+ofst), size);
          }else if(type>=11 && type<=21){/* NUM */
                size   = type - 9;
                cout<<"NUM";
                cout<<" SIZE:"<<size<<endl;
                
                col.setType(COL_NUM);
                col.set((char*)(z+ofst), size);
          }else{
              return ErrHdr;
          }
        ofst += size;
        col.show();
        rec.addCol(col);
    }
    
    return NormalOK;
}
int RecordDecoder::GetTableID(uchar *z, int n, uint64 &tid){
    if (!z) return ErrRecord;
    TypChg::GetVarint64((uchar *)z, n, tid);
    if (tid<=0) return ErrTableID;
    return NormalOK;
}
int TypChg::GetVarint64(uchar *z,int n,uint64 &Result){
  unsigned int x;
  if( n<1 ) return 0;
  if( z[0]<=240 ){
    Result = z[0];
    return 1;
  }
  if( z[0]<=248 ){
    if( n<2 ) return 0;
    Result = (z[0]-241)*256 + z[1] + 240;
    return 2;
  }
  if( n<z[0]-246 ) return 0;
  if( z[0]==249 ){
    Result = 2288 + 256*z[1] + z[2];
    return 3;
  }
  if( z[0]==250 ){
    Result = (z[1]<<16) + (z[2]<<8) + z[3];
    return 4;
  }
  x = (z[1]<<24) + (z[2]<<16) + (z[3]<<8) + z[4];
  if( z[0]==251 ){
    Result = x;
    return 5;
  }
  if( z[0]==252 ){
    Result = (((uint64)x)<<8) + z[5];
    return 6;
  }
  if( z[0]==253 ){
    Result = (((uint64)x)<<16) + (z[5]<<8) + z[6];
    return 7;
  }
  if( z[0]==254 ){
    Result = (((uint64)x)<<24) + (z[5]<<16) + (z[6]<<8) + z[7];
    return 8;
  }
  Result = (((uint64)x)<<32) +
               (0xffffffff & ((z[5]<<24) + (z[6]<<16) + (z[7]<<8) + z[8]));
  return 9;
}
int TypChg::PutVarint64(uchar *z, const uint64 x){
  unsigned int w, y;
  if( x<=240 ){
    z[0] = (unsigned char)x;
    return 1;
  }
  if( x<=2287 ){
    y = (unsigned int)(x - 240);
    z[0] = (unsigned char)(y/256 + 241);
    z[1] = (unsigned char)(y%256);
    return 2;
  }
  if( x<=67823 ){
    y = (unsigned int)(x - 2288);
    z[0] = 249;
    z[1] = (unsigned char)(y/256);
    z[2] = (unsigned char)(y%256);
    return 3;
  }
  y = (unsigned int)x;
  w = (unsigned int)(x>>32);
  if( w==0 ){
    if( y<=16777215 ){
      z[0] = 250;
      z[1] = (unsigned char)(y>>16);
      z[2] = (unsigned char)(y>>8);
      z[3] = (unsigned char)(y);
      return 4;
    }
    z[0] = 251;
    varintWrite32(z+1, y);
    return 5;
  }
  if( w<=255 ){
    z[0] = 252;
    z[1] = (unsigned char)w;
    varintWrite32(z+2, y);
    return 6;
  }
  if( w<=65535 ){
    z[0] = 253;
    z[1] = (unsigned char)(w>>8);
    z[2] = (unsigned char)w;
    varintWrite32(z+3, y);
    return 7;
  }
  if( w<=16777215 ){
    z[0] = 254;
    z[1] = (unsigned char)(w>>16);
    z[2] = (unsigned char)(w>>8);
    z[3] = (unsigned char)w;
    varintWrite32(z+4, y);
    return 8;
  }
  z[0] = 255;
  varintWrite32(z+1, w);
  varintWrite32(z+5, y);
  return 9;
}
int TypChg::GetReal(uchar* z, int n, real& Result){
    
    uint64 m;
    int e;
    int tmpsize;
    tmpsize = TypChg::GetVarint64(z, n, m);
    e = (int)m;
    tmpsize += TypChg::GetVarint64(z+tmpsize, n-tmpsize, m);
    if( tmpsize!=n ) return ErrRecord;

    Result.m = m;
    Result.e = (e >> 2);
    if( e & 0x02 ) Result.e = -1 * Result.e;
    if( e & 0x01 ) Result.sign = 1;
    
    return NormalOK;
}
int TypChg::GetInt(uchar* z, int n, int64 &Result){
    Result = ((char*)z)[0];
    for(int iByte=1; iByte<n; iByte++){
        Result = Result*256 + z[iByte];
    }
    return NormalOK;
}
void TypChg::varintWrite32(uchar *z, unsigned int y){
  z[0] = (unsigned char)(y>>24);
  z[1] = (unsigned char)(y>>16);
  z[2] = (unsigned char)(y>>8);
  z[3] = (unsigned char)(y);
}