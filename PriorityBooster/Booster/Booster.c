#include "pch.h"
#include <iostream>
#include <Windows.h>
#include "..\PriorityBooster\PriorityBoosterCommon.h"


int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("[*] Usage: Booster <ThreadId> <Priority>\n");
		return 0;
	}

	HANDLE hDevice = CreateFile(L"\\\\.\\PriorityBooster", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice == INVALID_HANDLE_VALUE) {
		return Error("Failed to open device..\n");
	}
	printf("[+] Successfully opened a handle to the target device..\n");
	
	return 0;

	ThreadData data;
	data.ThreadId = atoi(argv[1]);
	data.Priority = atoi(argv[2]);

	DWORD bytesRet;

	BOOL success = DeviceIoControl(hDevice, IOCTL_PRIORITY_BOOSTER_SET_PRIORITY, &data, sizeof(data), NULL, 0, &bytesRet, NULL);
	if (success) {
		printf("[+] Starting interaction with the driver..\n");
		printf("[+] Successfully changed the priority!\n");
	}
	Error("[-] Failed to change the priority.. exiting\n");

	CloseHandle(hDevice);
}
