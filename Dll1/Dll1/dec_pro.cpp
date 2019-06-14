// Dll1.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "aes_dec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <errno.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <io.h>
#include <conio.h>

DllExport int _stdcall aes_decrypt(char *fi)
{
	char buf[FREAD_COUNT + BLOCK_SIZE];
	unsigned char iv[] = "\x00\x01\x00\x03\x05\x03\x00\x01\x00\x00\x02\x00\x06\x07\x06\x00";
	char decfile[_MAX_PATH];
	char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

	int len = 0;
	int total_size = 0;
	int save_len = 0;
	int w_len = 0;

	memset(buf, 0, FREAD_COUNT + BLOCK_SIZE);

	_splitpath(fi, drive, dir, fname, ext);
	sprintf(decfile, "%s%s%s", drive, dir, fname);

	FILE *fp = fopen(fi, "rb");
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

		AES_cbc_encrypt((unsigned char *)buf, (unsigned char *)buf, len, &aesKey, iv, AES_DECRYPT);

		if (save_len == total_size) {
			w_len = len - buf[len - 1]; //padding = buf[len - 1]
		}
		fwrite(buf, RW_SIZE, w_len, wfp);
	}
	fclose(wfp);
	fclose(fp);

	return TRUE;
}

DllExport int _stdcall File_load_all(char *Path)
{
	struct _finddata_t fd;
	intptr_t handle;
	char File_Path[100];
	FILE *fp = NULL;
	int result = 1;

	sprintf(File_Path, "%s\\*.fun", Path);
	handle = _findfirst(File_Path, &fd);

	if (handle == -1) {
		printf("There were no files.\n");
		return 0;
	}

	if ((fp = fopen("./list.txt", "w")) == NULL) {
		printf("file open error!");
		exit(1);
	}

	while (result != -1) {
		fprintf(fp, "%s\\%s\n", Path, fd.name);
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
	return 0;
}

DllExport int _stdcall KillPro(char *program) {

	HANDLE hSnapshot;
	PROCESSENTRY32 ppe;

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	ppe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnapshot, &ppe)) {
		do
		{
			if (strcmp((char *)ppe.szExeFile, program) == 0) {
				HANDLE ppe2 = OpenProcess(PROCESS_TERMINATE, FALSE, ppe.th32ProcessID);
				if (ppe2) {
					TerminateProcess(ppe2, 0);
					CloseHandle(ppe2);
					break;
				}
			}
		} while (Process32Next(hSnapshot, &ppe));
	}
	CloseHandle(hSnapshot);

	return 0;
}

DllExport int _stdcall RegDelFunc()
{
	HKEY hkey;
	LONG result;

	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hkey);
	if (result != ERROR_SUCCESS)
		printf("ERROR\n");

	result = RegDeleteValue(hkey, "firefox.exe");
	if (result != ERROR_SUCCESS) {
		printf("ERROR\n");
		if (result == ERROR_FILE_NOT_FOUND)
			printf("error file not found");
	}

	RegCloseKey(hkey);

	return 0;
}