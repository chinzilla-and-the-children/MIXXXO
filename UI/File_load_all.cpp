#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <conio.h>
#include <stdlib.h>
void File_load_all(char* Path)
{
	_finddata_t fd;
	long handle;
	//char Path[100] = ".";
	char File_Path[100];
	FILE *fp = NULL;
	int result = 1;

	sprintf_s(File_Path, "%s\\*.fun", Path);
	handle = _findfirst(File_Path, &fd);  //���� ���� �� ��� ������ ã�´�.

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