#include "neural_address.h"
#include <string.h>
static int supported(uint16_t w){ return w==128||w==256||w==512||w==1024; }
int shb_address_init(SHBNeuralAddress* a,uint16_t w){
    if(!a||!supported(w)) return -1;
    a->bit_width=w; memset(a->bytes,0,sizeof(a->bytes)); return 0;
}
int shb_address_set_bit(SHBNeuralAddress* a,uint16_t i,int value){
    if(!a||i>=a->bit_width) return -1;
    size_t byte=i/8; unsigned shift=7u-(unsigned)(i%8);
    if(value) a->bytes[byte]|=(uint8_t)(1u<<shift); else a->bytes[byte]&=(uint8_t)~(1u<<shift);
    return 0;
}
int shb_address_get_bit(const SHBNeuralAddress* a,uint16_t i){
    if(!a||i>=a->bit_width) return -1;
    return (a->bytes[i/8]>>(7u-(unsigned)(i%8)))&1u;
}
int shb_address_equal(const SHBNeuralAddress* a,const SHBNeuralAddress* b){
    if(!a||!b||a->bit_width!=b->bit_width) return 0;
    return memcmp(a->bytes,b->bytes,a->bit_width/8)==0;
}
size_t shb_address_hex(const SHBNeuralAddress* a,char* out,size_t n){
    static const char h[]="0123456789abcdef";
    size_t bytes;
    if(!a) return 0; bytes=a->bit_width/8;
    if(!out||n<bytes*2+1) return bytes*2+1;
    for(size_t i=0;i<bytes;i++){out[i*2]=h[a->bytes[i]>>4];out[i*2+1]=h[a->bytes[i]&15];}
    out[bytes*2]='\0'; return bytes*2;
}