#include "rd.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "ErrMsg.h"
#include "column.h"

using namespace std;
int RecordDecoder::GetColumnsFromValue(uchar *z, int n, Record &result){
    
    uint64 type;        /*Datatype*/
    uint64 subtype;     /*Subtype of TEXT */
    uint64 lenHdr;
    uint64 size;
    uint64 ofst;         /*Offset into the data*/
            
    int sz;
    int startHdr;    
    int endHdr;
    int rc;
    int ofstHdr;        /*Offset into the header*/
    
    //Get header
    if( !z || n==0 ) return 0;
    
    startHdr = TypChg::GetVarint64(z, n, lenHdr);
    endHdr = lenHdr + startHdr;
    
    if (endHdr > n) return 0;  
    
    for (ofstHdr=startHdr,ofst=endHdr; ofstHdr<endHdr; ) {        
        sz = TypChg::GetVarint64(z+ofstHdr, n-ofstHdr, type);
        if (sz == 0) return 0;
        ofstHdr += sz;
        
//        cout<<"type("<<type<<")"<<": ";        
//        cout<<"offset: "<<ofst<<endl;
        Column col;
        
        if( type>=22 ){         /* KEY, STRING, BLOB, and TYPED */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            /* STRING, BLOB, KEY, and TYPED */
            subtype = (type-22)%4;
            if( subtype==2 ){               /* KEY */
                size=0;
            }else{             
                size = (type-22)/4;
              if( subtype==0){                
//                cout<<"STRING";
//                cout<<" SIZE:"<<size<<endl;;
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
//                cout<<"BLOB";
//                cout<<" SIZE:"<<size<<endl;;
                col.setType(COL_BLOB);
                col.set((char*)(z+ofst), size);
              }else if (subtype ==3){
//                cout<<"TYPED";
//                cout<<" SIZE:"<<size;
                  sz = TypChg::GetVarint64(z+ofstHdr, n-ofstHdr, type);
                  if (sz == 0) return 0;
                    ofstHdr += sz;
                col.setType(COL_TYPED);
                col.set((char*)(z+ofst), size);
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
//                cout<<"INT";
//                cout<<" SIZE:"<<size<<endl;
                
                col.setType(COL_INT);
                col.set((char*)(z+ofst), size);
          }else if(type>=11 && type<=21){/* NUM */
                size   = type - 9;
//                cout<<"NUM";
//                cout<<" SIZE:"<<size<<endl;
                
                col.setType(COL_NUM);
                col.set((char*)(z+ofst), size);
          }else{
              return 0;
          }
        ofst += size;
//        col.show();
        result.addCol(col);
    }
    return 1;
}
int RecordDecoder::GetTableID(uchar *z, int n, uint64 &tid){
    if (!z) return ErrRecord;
    TypChg::GetVarint64((uchar *)z, n, tid);
    if (tid<=0) return ErrTableID;
    return 1;
}
int RecordDecoder::GetTaleSchema(Record &input){
    return 1;
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
    if( tmpsize!=n ) return 0;
    
    Result.m = m;
    Result.e = (e >> 2);
    if( e & 0x02 ) Result.e = -1 * Result.e;
    if( e & 0x01 ) Result.sign = 1;
    
    return 1;
}
int TypChg::GetInt(uchar* z, int n, int64 &Result){
    if (!z || n==0)
        return 0;
    Result = ((char*)z)[0];
    for(int iByte=1; iByte<n; iByte++){
        Result = Result*256 + z[iByte];
    }
    return 1;
}
void TypChg::varintWrite32(uchar *z, unsigned int y){
  z[0] = (unsigned char)(y>>24);
  z[1] = (unsigned char)(y>>16);
  z[2] = (unsigned char)(y>>8);
  z[3] = (unsigned char)(y);
}
int TypChg::DecodeNumericKey(
        const uchar *aKey,       /* Input encoding */
        uint64 nKey,                   /* Number of bytes in aKey[] */
        real &pVal              /* Write the result here */
){
  unsigned int i, y;
  unsigned int xorMask = 0;
  short e;
  uint64 m;
  uint64 eBig;
  char aInvertedKey[4];

  pVal.approx = 0;
  pVal.sign = 0;
  if( nKey<1 ) return 0;
  switch( aKey[0] ){
    case 0x06:   /* NaN ascending */
    case 0xf9:   /* NaN descending */
      pVal.m = 0;
      pVal.e = 1000;
      return 1;

    case 0x07:   /* -inf ascending */
    case 0xf8:   /* -inf descending */
      pVal.m = 1;
      pVal.sign = 1;
      pVal.e = 1000;
      return 1;

    case 0x15:   /* zero ascending */
    case 0xea:   /* zero descending */
      pVal.m = 0;
      pVal.e = 0;
      return 1;

    case 0x23:   /* +inf ascending */
    case 0xdc:   /* +inf descending */
      pVal.m = 1;
      pVal.e = 1000;
      return 1;

    case 0x09:
    case 0x0a:
    case 0x0b:
    case 0x0c:
    case 0x0d:
    case 0x0e:
    case 0x0f:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:   /* -medium ascending */
      pVal.sign = 1;
      xorMask = 0xff;
      e = 0x13 - aKey[0];
      i = 1;
      break;

    case 0xf6:
    case 0xf5:
    case 0xf4:
    case 0xf3:
    case 0xf2:
    case 0xf1:
    case 0xf0:
    case 0xef:
    case 0xee:
    case 0xed:
    case 0xec:   /* -medium descending */
      pVal.sign = 1;
      e = aKey[0] - 0xec;
      i = 1;
      break;

    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:   /* +medium ascending */
      e = aKey[0] - 0x17;
      i = 1;
      break;

    case 0xe8:
    case 0xe7:
    case 0xe6:
    case 0xe5:
    case 0xe4:
    case 0xe3:
    case 0xe2:
    case 0xe1:
    case 0xe0:
    case 0xdf:
    case 0xde:   /* +medium descending */
      e = 0xe8 - aKey[0];
      xorMask = 0xff;
      i = 1;
      break;

    case 0x14:   /* -small ascending */
    case 0xe9:   /* +small descending */
      i = 1 + TypChg::GetVarint64((uchar*)(aKey+1), 2, eBig);
      e = (short)-eBig;
      xorMask = 0xff;
      break;

    case 0x16:   /* +small ascending */
    case 0xeb:   /* -small descending */
      aInvertedKey[0] = aKey[1] ^ 0xff;
      aInvertedKey[1] = aKey[2] ^ 0xff;
      i = 1 + TypChg::GetVarint64((uchar*)aInvertedKey, 2, eBig);
      e = (short)-eBig;
      break;

    case 0x08:   /* -large ascending */
    case 0xdd:   /* +large descending */
      aInvertedKey[0] = aKey[1] ^ 0xff;
      aInvertedKey[1] = aKey[2] ^ 0xff;
      i = 1 + TypChg::GetVarint64((uchar*)aInvertedKey, 2, eBig);
      e = (short)eBig;
      xorMask = 0xff;
      break;

    case 0x22:   /* +large ascending */
    case 0xf7:   /* -large descending */
      i = 1 + TypChg::GetVarint64((uchar*)(aKey+1), 2, eBig);
      e = (short)eBig;
      break;

    default:
      return 0;
  }
  m = 0;
  do{
    y = aKey[i++] ^ xorMask;
    m = m*100 + y/2;
    e--;
  }while( y & 1 );
  if( m==0 ) return 0;

  pVal.m = m;
  pVal.e = 2*e;
  return i;
}