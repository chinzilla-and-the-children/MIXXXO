#include <stdio.h>
#include <string.h>
#include <io.h>
#include <conio.h>

void main()
{
	_finddata_t fd;
	long handle;
	char Path[100] = ".";
	char File_Path[100];
	int result = 1;
	
	sprintf_s(File_Path, "%s\\*.fun", Path);
	handle = _findfirst(File_Path, &fd);  //���� ���� �� ��� ������ ã�´�.

	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}

	while (result != -1)
	{
		printf("File: %s\n", fd.name);
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
}
