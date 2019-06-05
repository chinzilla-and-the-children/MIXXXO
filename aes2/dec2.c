#define _CRT_SECURE_NO_WARNINGS
#include <openssl/aes.h>
#include <openssl/des.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <errno.h>

#define BLOCK_SIZE 16
#define KEY_BIT 128
#define RW_SIZE 1
#define FREAD_COUNT 2048

AES_KEY aesKey;
static unsigned char key[] = "\x3a\x82\x2c\x03\x0c\x05\xdb\x77\x08\x09\x0a\x0b\x0c\x0d\x0e\x0d";
static unsigned char iv[] = "\x00\x01\x00\x03\x05\x03\x00\x01\x00\x00\x02\x00\x06\x07\x06\x00";
extern int errno;

int aes_decrypt(char fi[], int count)
{
	char buf[FREAD_COUNT + BLOCK_SIZE];
	char decdata[FREAD_COUNT + BLOCK_SIZE];

	int len = 0;
	int total_size = 0;
	int save_len = 0;
	int w_len = 0;

	char *efile = (char *)malloc(count - 8);
	memset(efile, 0, sizeof(efile));
	memset(buf, 0, FREAD_COUNT + BLOCK_SIZE);
	memset(decdata, 0, FREAD_COUNT + BLOCK_SIZE);

	strncpy(efile, fi, count - 4);

	FILE *fp = fopen(fi, "rb");
	if (fp == NULL) {
		printf("file open error errono=%d\n", errno);
		exit(-1);
	}

	FILE *wfp = fopen(efile, "wb");
	if (wfp == NULL) {
		printf("file open error errono=%d\n", errno);
		exit(-1);
	}

	AES_set_decrypt_key(key, KEY_BIT, &aesKey);

	fseek(fp, 0, SEEK_END);
	total_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	printf("total_size %d\n", total_size);

	while (len = (int)fread(buf, (size_t)RW_SIZE, (size_t)FREAD_COUNT, fp)) {

		printf("%s", buf);
		if (FREAD_COUNT == 0) break;
		save_len += len;
		w_len = len;

		AES_cbc_encrypt(buf, decdata, len, &aesKey, iv, AES_DECRYPT);

		if (save_len == total_size) {
			w_len = len - decdata[len - 1];
			printf("dec padding size %d\n", decdata[len - 1]);
		}
		fwrite(decdata, RW_SIZE, w_len, wfp);
	}
	fclose(wfp);
	fclose(fp);


	return TRUE;
}

int main()
{
	char * fi[] = { "jeonghee.txt.fun","ransom.txt.fun" };
	int i = 0;
	int file_count = sizeof(fi) / sizeof(fi[0]);
	/*for (i = 0; i < file_count; i++) {
		aes_decrypt(fi[i], (int)strlen(fi[i]));
	}*/
	aes_decrypt(fi[0], (int)strlen(fi[0]));
	aes_decrypt(fi[1], (int)strlen(fi[1]));
}