#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdio.h>
#include <string>

#ifndef AES_BLOCK_SIZE
#define AES_BLOCK_SIZE 16
#endif


#include <iostream>
#include <openssl/evp.h>

using std::string;

class Encryption {
    public:
        enum encryptType{
            BOTH, 
            ENCRYPT,
            DECRYPT
        };
        Encryption(unsigned char *key_data, unsigned char *salt, encryptType type);
        unsigned char *aes_encrypt(unsigned char *text);
        unsigned char *aes_decrypt(unsigned char *cipherText);
        void aes_encrypt(const string& ptext, string& ctext);
        void aes_decrypt(const string& ctext, string& ptext);
    private:
        unsigned char key[32];
        unsigned char iv[32];
        int nRounds = 14;
        EVP_CIPHER_CTX *en;
        EVP_CIPHER_CTX *de;
        /*
        Init Encryption CTX or Decryption CTX
        */
        void aes_init(unsigned char *key_data, unsigned char *salt, encryptType type);
        void aes_init_encrypt();
        void aes_init_decrypt();

};


unsigned char* encrypt(unsigned char* text);
std::string encrypt(std::string text);
char* decrypt(unsigned char* text);
std::string decrypt(std::string text);