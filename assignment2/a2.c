#include "a2.h"
#include <math.h>

char* gen_template();

int bitwise_xor(int value){
    int key = (int)(KEY);
    return (key ^ value);
}

char *xor_encrypt(char c){
    char* bin_encrypt = malloc(sizeof(char) * 7);
    
    int ascii_char = (int)(c);
    int ascii_encrypt = bitwise_xor(ascii_char);

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
    char* code = gen_template();
    int msg_len = strlen(msg);
    char* msg_encrypt = malloc(sizeof(char) * (msg_len + 1) * 7); // Length of encrypted message
    char* letter_encrypt;
    char* null_char = xor_encrypt('\0');
    int counter = 0;

    // Generate a string containing the encrypted message
    for (int i = 0; i < msg_len; i++){
        char* letter_encrypt = xor_encrypt(msg[i]);
        for (int j = 0; j < 7; j++){
            msg_encrypt[7*i+j] = letter_encrypt[j];
        }
        free(letter_encrypt);
    }
    // printf("%d\n", strlen(msg_encrypt));

    // Add encrypted null char to the end
    for (int i = 0; i < 7; i++){
        msg_encrypt[msg_len * 7 + i] = null_char[i];
    }
    // printf("msg_encrypt: %s\n", msg_encrypt);

    // Weave msg_encrypt into code (currently the QR code template)
    for (int i = 0; i<256; i++){
        if (code[i] == '2' && counter < strlen(msg_encrypt)){
            code[i] = msg_encrypt[counter];
            counter++;
        } 
        else if (code[i] == '2'){
            code[i] = '0';
        }
    }
    printf("code: %s\n", code);
    free(null_char);
    free(msg_encrypt);
    // free(letter_encrypt);

    return code;
}

char *read_code(char *code){
    char* msg = malloc(180 * sizeof(char)); // 180 is the max # of chars an encoded msg can be
    int counter = 0;

    for (int i = 5; i < 256; i++){
        if (4 < i < 11 || 20 < i < 27 || 36 < i < 43 || 52 < i < 59 || 68 < i < 75 || 
        79 < i < 176 || 180 < i < 192 || 196 < i < 208 || 212 < i < 224 || 228 < i < 240
        || 245 < i < 255){
            msg[counter] = code[i];
        }

    }
    return msg;
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


char* gen_template(){
    char* sc_template = malloc(256 * sizeof(char));
    
    for (int i = 0; i<256; i++){
        // Initialize everything to '2' char, useful for weaving in msg later
        sc_template[i] = '2'; 
    }

    // Set up the template properly
    // Row 1
    sc_template[0] = '1';
    sc_template[1] = '1';
    sc_template[2] = '1';
    sc_template[3] = '1';
    sc_template[4] = '1';

    sc_template[11] = '1';
    sc_template[12] = '1';
    sc_template[13] = '1';
    sc_template[14] = '1';
    sc_template[15] = '1';

    // Row 2
    sc_template[16] = '1';
    sc_template[17] = '0';
    sc_template[18] = '0';
    sc_template[19] = '0';
    sc_template[20] = '1';

    sc_template[27] = '1';
    sc_template[28] = '0';
    sc_template[29] = '0';
    sc_template[30] = '0';
    sc_template[31] = '1';

    // Row 3
    sc_template[32] = '1';
    sc_template[33] = '0';
    sc_template[34] = '1';
    sc_template[35] = '0';
    sc_template[36] = '1';

    sc_template[43] = '1';
    sc_template[44] = '0';
    sc_template[45] = '1';
    sc_template[46] = '0';
    sc_template[47] = '1';

    // Row 4
    sc_template[48] = '1';
    sc_template[49] = '0';
    sc_template[50] = '0';
    sc_template[51] = '0';
    sc_template[52] = '1';

    sc_template[59] = '1';
    sc_template[60] = '0';
    sc_template[61] = '0';
    sc_template[62] = '0';
    sc_template[63] = '1';

    // Row 5
    sc_template[64] = '1';
    sc_template[65] = '1';
    sc_template[66] = '1';
    sc_template[67] = '1';
    sc_template[68] = '1';

    sc_template[75] = '1';
    sc_template[76] = '1';
    sc_template[77] = '1';
    sc_template[78] = '1';
    sc_template[79] = '1';

    // Row 12
    sc_template[176] = '1';
    sc_template[177] = '1';
    sc_template[178] = '1';
    sc_template[179] = '1';
    sc_template[180] = '1';

    // Row 13
    sc_template[192] = '1';
    sc_template[193] = '0';
    sc_template[194] = '0';
    sc_template[195] = '0';
    sc_template[196] = '1';

    // Row 14
    sc_template[208] = '1';
    sc_template[209] = '0';
    sc_template[210] = '1';
    sc_template[211] = '0';
    sc_template[212] = '1';

    // Row 15
    sc_template[224] = '1';
    sc_template[225] = '0';
    sc_template[226] = '0';
    sc_template[227] = '0';
    sc_template[228] = '1';

    // Row 16
    sc_template[240] = '1';
    sc_template[241] = '1';
    sc_template[242] = '1';
    sc_template[243] = '1';
    sc_template[244] = '1';

    sc_template[255] = '1';
    
    return sc_template;
}