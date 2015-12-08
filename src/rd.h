
#include "datatype.h"
class RecordDecoder{
public:
    static int GetHeader(uchar *z, int n);
    static int GetTableID(uchar *z, int n, uint64 *tid);
};
class TypChg{  
public:
    static int PutVarint64(uchar *z,uint64 x);
    static int GetVarint64(uchar *z ,int n ,uint64 *pResult);
private:    
    static void varintWrite32(uchar *z, unsigned int y);
};
class ErrMsg {
public:
    int set();
    int show();
};