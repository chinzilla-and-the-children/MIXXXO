#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <conio.h>
#include <stdlib.h>
void main()
{
	_finddata_t fd;
	long handle;
	char Path[100] = ".";
	char File_Path[100];
	FILE *fp = NULL;
	int result = 1;

	sprintf_s(File_Path, "%s\\*.fun", Path);
	handle = _findfirst(File_Path, &fd);  //현재 폴더 내 모든 파일을 찾는다.

	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}

	if ((fp = fopen("test2.txt", "w")) == NULL) {
		printf("file open error!");
		exit(1);
	}

	while (result != -1)
	{
		fprintf(fp, "%s\n", fd.name);
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
}

