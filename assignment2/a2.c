#include "a2.h"
#include <math.h>

int bitwise_xor(int value){
    int key = (int)(KEY);
    return (key ^ value);
}

char *xor_encrypt(char c){
    char* bin_encrypt = malloc(sizeof(char) * 7);
    
    int ascii_char = (int)(c);
    printf("ascii_char: %d\n", ascii_char);
    int ascii_encrypt = bitwise_xor(ascii_char);
    printf("ascii_encrypt: %d\n", ascii_encrypt);

    for (int i = 6; i >= 0; i--){
        if (ascii_encrypt - pow(2, i) >= 0){
            bin_encrypt[6-i] = '1';
            ascii_encrypt = ascii_encrypt - pow(2, i);
        }
        else{
            bin_encrypt[6-i] = '0';
        }
    }
    return bin_encrypt;
}

char xor_decrypt(char *s){
    char decrypted;
    int ascii_char = 0;

    // Convert binary string representation into an ASCII value
    for (int i = 0; i < 7; i++){
        if (s[i] == '1'){
            ascii_char = ascii_char + pow(2, 6-i);
        }
    }

    int ascii_decrypt = bitwise_xor(ascii_char);
    decrypted = (char)(ascii_decrypt);
    return decrypted;
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