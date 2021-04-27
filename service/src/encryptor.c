#include <stddef.h>
#include <stdio.h>
#include "xxtea.h"


#define NUM_BLOCKS 4
#define PLAINTEXT_LEN (sizeof(long)*NUM_BLOCKS)
unsigned char plaintext[PLAINTEXT_LEN] = {"HELLO JORDAN!"}; 

long key[4] = { 0x66686235, 0x68726a33, 0x726c643a, 0x6c6e7033 };

int main() {
    btea((long *)plaintext, NUM_BLOCKS, key);

    printf("#include <stddef.h>\n");
    printf("unsigned char encrypted[%d] = { ", PLAINTEXT_LEN);
    for(size_t i = 0; i < PLAINTEXT_LEN; i++) {
        printf("%#02x", plaintext[i]);
        if((i+1)==PLAINTEXT_LEN) {
            printf(" };\n");
        } else {
            printf(", ");
        }
    }
    printf("size_t encrypted_len = %d;\n", NUM_BLOCKS);

    return 0;
}
