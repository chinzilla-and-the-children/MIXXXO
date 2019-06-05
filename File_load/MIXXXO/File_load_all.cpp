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
	handle = _findfirst(File_Path, &fd);  //현재 폴더 내 모든 파일을 찾는다.

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
