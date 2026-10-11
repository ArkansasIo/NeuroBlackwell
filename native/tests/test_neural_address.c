#include "neural_address.h"
#include <assert.h>
#include <string.h>
int main(void){
    SHBNeuralAddress a,b; char hex[33];
    assert(shb_address_init(&a,128)==0);
    assert(shb_address_init(&b,128)==0);
    assert(shb_address_set_bit(&a,127,1)==0);
    assert(shb_address_get_bit(&a,127)==1);
    assert(shb_address_equal(&a,&b)==0);
    assert(shb_address_hex(&a,hex,sizeof hex)==32);
    assert(strcmp(hex,"00000000000000000000000000000001")==0);
    return 0;
}