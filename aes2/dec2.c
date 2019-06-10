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

int aes_decrypt(char list_f[])
{
	FILE *list = fopen(list_f, "r");
	if (list == NULL) {
		printf("file open error errono=%d\n", errno);
		exit(-1);
	}

	while (!feof(list)) {
		char buf[FREAD_COUNT + BLOCK_SIZE];
		unsigned char iv[] = "\x00\x01\x00\x03\x05\x03\x00\x01\x00\x00\x02\x00\x06\x07\x06\x00";
		char enc_fname[_MAX_PATH];
		char decfile[_MAX_PATH];
		char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

		int len = 0;
		int total_size = 0;
		int save_len = 0;
		int w_len = 0;

		fscanf(list, "%s", &enc_fname);
		fgetc(list);

		memset(buf, 0, FREAD_COUNT + BLOCK_SIZE);

		_splitpath(enc_fname, drive, dir, fname, ext);
		sprintf(decfile, "%s%s%s", drive, dir, fname);

		FILE *fp = fopen(enc_fname, "rb");
		if (fp == NULL) {
			printf("file open error errono=%d\n", errno);
			exit(-1);
		}

		FILE *wfp = fopen(decfile, "wb");
		if (wfp == NULL) {
			printf("file open error errono=%d\n", errno);
			exit(-1);
		}

		AES_set_decrypt_key(key, KEY_BIT, &aesKey);

		fseek(fp, 0, SEEK_END);
		total_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		while (len = (int)fread(buf, (size_t)RW_SIZE, (size_t)FREAD_COUNT, fp)) {
			if (FREAD_COUNT == 0) break;
			save_len += len;
			w_len = len;

			AES_cbc_encrypt(buf, buf, len, &aesKey, iv, AES_DECRYPT);

			if (save_len == total_size) {
				w_len = len - buf[len - 1]; //padding = buf[len - 1]
			}
			fwrite(buf, RW_SIZE, w_len, wfp);
		}
		fclose(wfp);
		fclose(fp);
	}

	fclose(list);

	return TRUE;
}

int main()
{
	char *list = "D:\\hanjiwoo\\1_study\\cipher\\data\\list.txt";
	aes_decrypt(list);
}