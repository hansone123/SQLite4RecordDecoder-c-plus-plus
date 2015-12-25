
#include "datatype.h"
#include "record.h"

class RecordDecoder{
public:
    static int GetTaleSchema(Record &input);
    static int GetColumnsFromKey(
        char*z,
        uint64 n,
        uint64 iOfst,     /* Offset of value in the key */
        Record &result                /* Write the results here */
);
    static int GetColumnsFromValue(uchar *z, int n, Record &result);
    static int GetTableID(uchar *z, int n, uint64 &tid);
};
class TypChg{
public:
    static int PutVarint64(uchar *z,uint64 x);        /* Transfer from x(uint64) to z(Varint), size=return */
    static int GetVarint64(uchar *z ,int n ,uint64 &Result); /* Transfer from  z(Varint) to Result(uint64), size=n */
    static int GetReal(uchar *z, int n, real &Result);
    static int GetInt(uchar *z, int n, int64 &Result);
    static int DecodeNumericKey(
                    const uchar *aKey,       /* Input encoding */
                    uint64 nKey,            /* Number of bytes in aKey[] */
                    real &pVal              /* Write the result here */
                  );
private:    
    static void varintWrite32(uchar *z, unsigned int y);
};
class ErrMsg {
public:
    int set();
    int show();
};