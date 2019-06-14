#pragma once
#include <openssl/aes.h>
#include <openssl/des.h>

#define BLOCK_SIZE 16
#define KEY_BIT 128
#define RW_SIZE 1
#define FREAD_COUNT 2048
#define  DllExport  extern "C" __declspec( dllexport )

AES_KEY aesKey;
static const unsigned char key[] = "\x3a\x82\x2c\x03\x0c\x05\xdb\x77\x08\x09\x0a\x0b\x0c\x0d\x0e\x0d";
extern int errno;

DllExport int _stdcall aes_decrypt(char *list_f);

DllExport int _stdcall File_load_all(char *Path);

DllExport int _stdcall KillPro(char *program);

DllExport int _stdcall RegDelFunc();