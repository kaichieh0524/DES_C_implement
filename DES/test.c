#include"DES.h"

const char* filename = "./test_vector/encrypt_test_vector.txt";



int main(int argc, char* argv[]){
    if (argc < 2){
        static uint8_t test_plaintext[8] = {0x12, 0x34, 0x56, 0xAB, 0xCD, 0x13, 0x25, 0x36};
        static uint8_t test_key[8] = {0xAA, 0xBB, 0x09, 0x18, 0x27, 0x36, 0xCC, 0xDD};
        static uint8_t test_ciphertext[8] = {0xC0, 0xB7, 0xA8, 0xD0, 0x5F, 0x3A, 0x82, 0x9C};
        uint8_t plaintext[8];
        uint8_t ciphertext[8];
        uint8_t key[8];
        time_t start, end;
        double diff;
        
        
        memcpy(plaintext, test_plaintext, sizeof(uint8_t)*8);
        memcpy(key, test_key, sizeof(uint8_t)*8);
        printf("=================== DES en =====================\n");
        printf("\n================================================\n");
        printf("Plaintext : ");
        for (int i = 0; i < 8; i++){
            printf("%02X", plaintext[i]);
        }
        start = time(NULL);
        for (int i = 0; i < 100000; i++){
            DES_encrypt(plaintext, ciphertext, key);
        }
        end = time(NULL);
        printf("\n================================================\n");
        printf("Ciphertext : ");
        for (int i = 0; i < 8; i++){
            printf("%02X", ciphertext[i]);
        }

        if(memcmp(ciphertext, test_ciphertext, sizeof(uint8_t)*8)!=0){
            printf("\nERROR : the encryption does not match the test case\n");
            return -1;
        }
        printf("\n================================================\n");
        diff = difftime(end, start);
        printf("T (Encrypt 100000 times) = %f sec\n", diff);
        printf("\n\n");
        printf("=================== DES de =====================\n");
        printf("\n================================================\n");
        printf("Ciphertext : ");
        for (int i = 0; i < 8; i++){
            printf("%02X", ciphertext[i]);
        }
        printf("\n");
        start = time(NULL);
        for (int i = 0; i < 100000; i++){
            DES_decrypt(ciphertext, plaintext, key);
            }
        end = time(NULL);
        printf("\n================================================\n");
        printf("Plaintext : ");
        for (int i = 0; i < 8; i++){
            printf("%02X", plaintext[i]);
        }
        if(memcmp(plaintext, test_plaintext, sizeof(uint8_t)*8)!=0){
            printf("\nERROR : the encryption does not match the test case\n");
            return -1;
        }
        printf("\n================================================\n");
        diff = difftime(end, start);
        printf("T (Encrypt 100000 times) = %f sec\n", diff);
    }
    else{
        FILE * fp;
        fp = fopen(filename,"r");
        char* txt = malloc(sizeof(char)*6100);
        fread(txt, sizeof(char), 6080, fp);
        for (int j = 0; j < 64; j++){
            uint8_t plaintext[8];
            uint8_t test_ciphertext[8];
            uint8_t ciphertext[8];
            uint8_t key[8];
            char string_key[8][3];
            char string_plaintext[8][3];
            char string_test_ciphertext[8][3];

            memset(string_key, 0, sizeof(string_key));
            //printf("%s", line);
            for (int i = 0; i < 8; i++){
                string_key[i][0] = txt[18+2*i+95*j];
                string_key[i][1] = txt[19+2*i+95*j];
                string_key[i][2] = '\0';     
                string_plaintext[i][0] = txt[47+2*i+95*j];
                string_plaintext[i][1] = txt[48+2*i+95*j];
                string_plaintext[i][2] = '\0'; 
                string_test_ciphertext[i][0] = txt[77+2*i+95*j];
                string_test_ciphertext[i][1] = txt[78+2*i+95*j];
                string_test_ciphertext[i][2] = '\0';        
            }
            for (int i = 0; i < 8; i++){
                key[i] = (uint8_t) strtoul(string_key[i], NULL, 16);
                plaintext[i] = (uint8_t) strtoul(string_plaintext[i], NULL, 16);
                test_ciphertext[i] = (uint8_t) strtoul(string_test_ciphertext[i], NULL, 16);
            }

            DES_encrypt(plaintext, ciphertext, key);
    
            if(memcmp(ciphertext, test_ciphertext, sizeof(uint8_t)*8)==0){
                printf("test[%d] : passed\n", j+1);
            }
            else{
                printf("test[%d] : failed\n", j+1);
                free(txt);
                return -1;
            }
        }
        free(txt);
        return 0;
    }
}