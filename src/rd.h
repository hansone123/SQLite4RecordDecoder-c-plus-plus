
#include "datatype.h"
#include "record.h"

class RecordDecoder{
public:
    static int GetColumns(uchar *z, int n, Record &rec);
    static int GetTableID(uchar *z, int n, uint64 &tid);
};
class TypChg{
public:
    static int PutVarint64(uchar *z,uint64 x);        /* Transfer from x(uint64) to z(Varint), size=return */
    static int GetVarint64(uchar *z ,int n ,uint64 &Result); /* Transfer from  z(Varint) to Result(uint64), size=n */
    static int GetReal(uchar *z, int n, real &Result);
    static int GetInt(uchar *z, int n, int64 &Result);
private:    
    static void varintWrite32(uchar *z, unsigned int y);
};
class ErrMsg {
public:
    int set();
    int show();
};