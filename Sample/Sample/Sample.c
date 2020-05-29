#include <ntddk.h>

// Reference to unloading the driver (See 'DriverObject->DriverUnload = SampleUnload')
void SampleUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);

	KdPrint(("Sample driver Unload called..\n")); // Tracing driver unload
}

// DriverEntry is the equivalent of 'main' function for Windows Drivers
NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	DriverObject->DriverUnload = SampleUnload; // Pointer for properly unloading the driver to avoid leakage

	KdPrint(("Sample driver initialized successfully..\n")); // Tracing driver initialization

	RTL_OSVERSIONINFOW VersionInfo;
	NTSTATUS status = RtlGetVersion(&VersionInfo);

	if (status != STATUS_SUCCESS) {
		KdPrint(("Unable to fingerprint OS version..\n"));
	}
	KdPrint(("The underlying Operating System verion is: %d.%d.%d..\n", VersionInfo.dwMajorVersion, VersionInfo.dwMinorVersion, VersionInfo.dwBuildNumber)); // Tracing Operating System Version

	return STATUS_SUCCESS;
}
