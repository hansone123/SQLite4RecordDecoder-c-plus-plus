
typedef unsigned long long int uint64;

class RecordDecoder {
public:
    int sqlite4PutVarint64(unsigned char *z, uint64 x);
    int GetVarint64(const unsigned char *z ,int n ,uint64 *pResult);
    void varintWrite32(unsigned char *z, unsigned int y);
};