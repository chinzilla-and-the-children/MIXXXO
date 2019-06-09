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
static const unsigned char key[] = "\x3a\x82\x2c\x03\x0c\x05\xdb\x77\x08\x09\x0a\x0b\x0c\x0d\x0e\x0d";
extern int errno;

int aes_decrypt(char fi[], int count)
{
	char buf[FREAD_COUNT + BLOCK_SIZE];
	char decdata[FREAD_COUNT + BLOCK_SIZE];
	unsigned char iv[] = "\x00\x01\x00\x03\x05\x03\x00\x01\x00\x00\x02\x00\x06\x07\x06\x00";

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

	/*memset(iv, iv, sizeof(iv));*/
	AES_set_decrypt_key(key, KEY_BIT, &aesKey);

	fseek(fp, 0, SEEK_END);
	total_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	printf("total_size %d\n", total_size);

	while (len = (int)fread(buf, (size_t)RW_SIZE, (size_t)FREAD_COUNT, fp)) {


		if (FREAD_COUNT == 0) break;
		save_len += len;
		w_len = len;

		AES_cbc_encrypt(buf, buf, len, &aesKey, iv, AES_DECRYPT);

		if (save_len == total_size) {
			w_len = len - buf[len - 1];
			printf("dec padding size %d\n", buf[len - 1]);
		}
		fwrite(buf, RW_SIZE, w_len, wfp);
	}
	fclose(wfp);
	fclose(fp);


	return TRUE;
}

int main()
{
	/*char * fi[] = { "jeonghee.txt.fun","ransom.txt.fun" };*/

	FILE *list = fopen("list.txt", "r");
	if (list == NULL) {
		printf("file open error errono=%d\n", errno);
		exit(-1);
	}

	char str[255];
	size_t len = 0;
	size_t read;
	
	while (!feof(list)) {
		fscanf(list, "%[^\n]s", &str);
		aes_decrypt(str, strlen(str));
		fgetc(list);
	}
	fclose(list);
}