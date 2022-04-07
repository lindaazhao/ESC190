#include "a2.h"

int bitwise_xor(int value){
    int key = (int)(KEY);
    return (key ^ value);
}

char *xor_encrypt(char c){
    char* bin_encrypt[7];
    
    int ascii_char = (int)(c);
    int ascii_encrypt = bitwise_xor(ascii_char);

    for (int i = 6; i >= 0; i--){
        if (ascii_encrypt - pow(2, i) >= 0){
            bin_encrypt[6 - i] = 1;
            ascii_encrypt = ascii_encrypt - pow(2, i);
        }
    }
    return bin_encrypt;
}

char xor_decrypt(char *s){
    //add code here
}

char *gen_code(char *msg){
    //add code here;
}

char *read_code(char *code){
    //add code here
}

char *compress(char *code){
    //add code here
}

char *decompress(char *code){
    //add code here
}

int calc_ld(char *sandy, char *cima){
    //add code here
}