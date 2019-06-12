#include <stdio.h>
#include <windows.h>

void RegDelFunc()
{
	HKEY hkey;
	LONG result;

	result = RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), &hkey);
	if (result != ERROR_SUCCESS)
		printf("ERROR\n");
	if (RegDeleteValue(hkey, "firefox.exe") != ERROR_SUCCESS)
		printf("ERORR\n");

	RegCloseKey(hkey);
}

int main(void)
{
	RegDelFunc();
	return 0;
}