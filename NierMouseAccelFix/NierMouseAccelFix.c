#include <Windows.h>

#define DLLAPI __declspec(dllexport)

INT OldMouseParameters[3];
INT NewMouseParameters[3] = {0, 0, 0};
INT OldMouseSpeed;
INT NewMouseSpeed;

VOID SetSpecialMouseSettings(
	IN	BOOL	bFocus)
{
	static INT OldMouseParameters[3] = {0};

	if (bFocus) {
		SystemParametersInfoA(SPI_GETMOUSE, 0, OldMouseParameters, 0);
		SystemParametersInfoA(SPI_GETMOUSESPEED, 0, &OldMouseSpeed, 0);
		SystemParametersInfoA(SPI_SETMOUSE, 0, NewMouseParameters, SPIF_SENDCHANGE);
		SystemParametersInfoA(SPI_SETMOUSESPEED, 0, (PVOID) NewMouseSpeed, SPIF_SENDCHANGE);
	} else {
		SystemParametersInfoA(SPI_SETMOUSE, 0, OldMouseParameters, SPIF_SENDCHANGE);
		SystemParametersInfoA(SPI_SETMOUSESPEED, 0, (PVOID) OldMouseSpeed, SPIF_SENDCHANGE);
	}
}

LRESULT CALLBACK CallWndProc(
	IN	INT		iCode,
	IN	WPARAM	wParam,
	IN	LPARAM	lParam)
{
	LPCWPSTRUCT lpCwp = (LPCWPSTRUCT) lParam;

	if (lpCwp->message == WM_SETFOCUS || lpCwp->message == WM_KILLFOCUS) {
		SetSpecialMouseSettings((lpCwp->message == WM_SETFOCUS) ? TRUE : FALSE);
	}

	return CallNextHookEx(NULL, iCode, wParam, lParam);
}

DLLAPI BOOL WINAPI DllMain(
	IN	HINSTANCE hInst,
	IN	DWORD dwReason,
	IN	LPVOID lpReserved)
{
	static HHOOK hHook = NULL;

	if (dwReason == DLL_PROCESS_ATTACH) {
		if ((hHook = SetWindowsHookExA(WH_CALLWNDPROC, CallWndProc, hInst, GetCurrentThreadId())) == NULL) {
			MessageBoxA(NULL, "Failed to set hook procedure", "NierMouseAccelFix", MB_ICONEXCLAMATION | MB_OK);
		} else {
			NewMouseSpeed = GetPrivateProfileIntA("MouseAccelFix", "Sensitivity", 10, ".\\MouseAccelFix.ini");
		}
	} else if (dwReason == DLL_PROCESS_DETACH) {
		SetSpecialMouseSettings(FALSE);
		UnhookWindowsHookEx(hHook);
	}

	return TRUE;
}

#pragma comment(linker, "/export:CheckETWTLS=dxg2.CheckETWTLS")
#pragma comment(linker, "/export:CompatString=dxg2.CompatString")
#pragma comment(linker, "/export:CompatValue=dxg2.CompatValue")
#pragma comment(linker, "/export:CreateDXGIFactory=dxg2.CreateDXGIFactory")
#pragma comment(linker, "/export:CreateDXGIFactory1=dxg2.CreateDXGIFactory1")
#pragma comment(linker, "/export:D3DKMTCloseAdapter=dxg2.D3DKMTCloseAdapter")
#pragma comment(linker, "/export:D3DKMTCreateAllocation=dxg2.D3DKMTCreateAllocation")
#pragma comment(linker, "/export:D3DKMTCreateContext=dxg2.D3DKMTCreateContext")
#pragma comment(linker, "/export:D3DKMTCreateDevice=dxg2.D3DKMTCreateDevice")
#pragma comment(linker, "/export:D3DKMTCreateSynchronizationObject=dxg2.D3DKMTCreateSynchronizationObject")
#pragma comment(linker, "/export:D3DKMTDestroyAllocation=dxg2.D3DKMTDestroyAllocation")
#pragma comment(linker, "/export:D3DKMTDestroyContext=dxg2.D3DKMTDestroyContext")
#pragma comment(linker, "/export:D3DKMTDestroyDevice=dxg2.D3DKMTDestroyDevice")
#pragma comment(linker, "/export:D3DKMTDestroySynchronizationObject=dxg2.D3DKMTDestroySynchronizationObject")
#pragma comment(linker, "/export:D3DKMTEscape=dxg2.D3DKMTEscape")
#pragma comment(linker, "/export:D3DKMTGetContextSchedulingPriority=dxg2.D3DKMTGetContextSchedulingPriority")
#pragma comment(linker, "/export:D3DKMTGetDeviceState=dxg2.D3DKMTGetDeviceState")
#pragma comment(linker, "/export:D3DKMTGetDisplayModeList=dxg2.D3DKMTGetDisplayModeList")
#pragma comment(linker, "/export:D3DKMTGetMultisampleMethodList=dxg2.D3DKMTGetMultisampleMethodList")
#pragma comment(linker, "/export:D3DKMTGetRuntimeData=dxg2.D3DKMTGetRuntimeData")
#pragma comment(linker, "/export:D3DKMTGetSharedPrimaryHandle=dxg2.D3DKMTGetSharedPrimaryHandle")
#pragma comment(linker, "/export:D3DKMTLock=dxg2.D3DKMTLock")
#pragma comment(linker, "/export:D3DKMTOpenAdapterFromHdc=dxg2.D3DKMTOpenAdapterFromHdc")
#pragma comment(linker, "/export:D3DKMTOpenResource=dxg2.D3DKMTOpenResource")
#pragma comment(linker, "/export:D3DKMTPresent=dxg2.D3DKMTPresent")
#pragma comment(linker, "/export:D3DKMTQueryAdapterInfo=dxg2.D3DKMTQueryAdapterInfo")
#pragma comment(linker, "/export:D3DKMTQueryAllocationResidency=dxg2.D3DKMTQueryAllocationResidency")
#pragma comment(linker, "/export:D3DKMTQueryResourceInfo=dxg2.D3DKMTQueryResourceInfo")
#pragma comment(linker, "/export:D3DKMTRender=dxg2.D3DKMTRender")
#pragma comment(linker, "/export:D3DKMTSetAllocationPriority=dxg2.D3DKMTSetAllocationPriority")
#pragma comment(linker, "/export:D3DKMTSetContextSchedulingPriority=dxg2.D3DKMTSetContextSchedulingPriority")
#pragma comment(linker, "/export:D3DKMTSetDisplayMode=dxg2.D3DKMTSetDisplayMode")
#pragma comment(linker, "/export:D3DKMTSetDisplayPrivateDriverFormat=dxg2.D3DKMTSetDisplayPrivateDriverFormat")
#pragma comment(linker, "/export:D3DKMTSetGammaRamp=dxg2.D3DKMTSetGammaRamp")
#pragma comment(linker, "/export:D3DKMTSetVidPnSourceOwner=dxg2.D3DKMTSetVidPnSourceOwner")
#pragma comment(linker, "/export:D3DKMTSignalSynchronizationObject=dxg2.D3DKMTSignalSynchronizationObject")
#pragma comment(linker, "/export:D3DKMTUnlock=dxg2.D3DKMTUnlock")
#pragma comment(linker, "/export:D3DKMTWaitForSynchronizationObject=dxg2.D3DKMTWaitForSynchronizationObject")
#pragma comment(linker, "/export:D3DKMTWaitForVerticalBlankEvent=dxg2.D3DKMTWaitForVerticalBlankEvent")
#pragma comment(linker, "/export:DXGID3D10CreateDevice=dxg2.DXGID3D10CreateDevice")
#pragma comment(linker, "/export:DXGID3D10CreateLayeredDevice=dxg2.DXGID3D10CreateLayeredDevice")
#pragma comment(linker, "/export:DXGID3D10ETWRundown=dxg2.DXGID3D10ETWRundown")
#pragma comment(linker, "/export:DXGID3D10GetLayeredDeviceSize=dxg2.DXGID3D10GetLayeredDeviceSize")
#pragma comment(linker, "/export:DXGID3D10RegisterLayers=dxg2.DXGID3D10RegisterLayers")
#pragma comment(linker, "/export:DXGIDumpJournal=dxg2.DXGIDumpJournal")
#pragma comment(linker, "/export:DXGIReportAdapterConfiguration=dxg2.DXGIReportAdapterConfiguration")
#pragma comment(linker, "/export:DXGIRevertToSxS=dxg2.DXGIRevertToSxS")
#pragma comment(linker, "/export:OpenAdapter10=dxg2.OpenAdapter10")
#pragma comment(linker, "/export:OpenAdapter10_2=dxg2.OpenAdapter10_2")
#pragma comment(linker, "/export:SetAppCompatStringPointer=dxg2.SetAppCompatStringPointer")
