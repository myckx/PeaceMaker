/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 * 
 * COPYRIGHT Bill Demirkapi 2020
 */
#include "common.h"
#include "shared.h"

void* __cdecl operator new(size_t size, POOL_TYPE pool, ULONG tag) {
	PVOID newAddress = ExAllocatePoolWithTag(pool, size, tag);
	//
	// Remove remenants from previous use.
	//
	if (newAddress)
	{
		memset(newAddress, 0, size);
	}
	return newAddress;
}

void __cdecl operator delete(void* p, unsigned __int64) {
	ExFreePool(p);
}

PPEB PsGetProcessPeb(IN PEPROCESS Process)
{
	UNICODE_STRING funcName;
	typedef PPEB(NTAPI* PsGetProcessPeb_t)(PEPROCESS Process);
	static PsGetProcessPeb_t fPsGetProcessPeb = NULL;

	if (fPsGetProcessPeb == NULL)
	{
		RtlInitUnicodeString(&funcName, L"PsGetProcessPeb");
		fPsGetProcessPeb = RCAST<PsGetProcessPeb_t>(MmGetSystemRoutineAddress(&funcName));
	}

	return fPsGetProcessPeb(Process);
}

NTSTATUS NtQueryInformationProcess(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength)
{
	UNICODE_STRING funcName;
	typedef NTSTATUS(NTAPI* NtQueryInformationProcess_t)(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);
	static NtQueryInformationProcess_t fNtQueryInformationProcess = NULL;

	if (fNtQueryInformationProcess == NULL)
	{
		RtlInitUnicodeString(&funcName, L"ZwQueryInformationProcess");
		fNtQueryInformationProcess = RCAST<NtQueryInformationProcess_t>(MmGetSystemRoutineAddress(&funcName));
	}

	return fNtQueryInformationProcess(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);
}

NTSTATUS NtQueryInformationThread(_In_ HANDLE ThreadHandle, _In_ THREADINFOCLASS ThreadInformationClass, _Out_ PVOID ThreadInformation, _In_ ULONG ThreadInformationLength, _Out_ PULONG ReturnLength)
{
	UNICODE_STRING funcName;
	typedef NTSTATUS(NTAPI * NtQueryInformationThread_t)(_In_ HANDLE ThreadHandle, _In_ THREADINFOCLASS ThreadInformationClass, _Out_ PVOID ThreadInformation, _In_ ULONG ThreadInformationLength, _Out_ PULONG ReturnLength);
	static NtQueryInformationThread_t fNtQueryInformationThread = NULL;

	if (fNtQueryInformationThread == NULL)
	{
		RtlInitUnicodeString(&funcName, L"ZwQueryInformationThread");
		fNtQueryInformationThread = RCAST<NtQueryInformationThread_t>(MmGetSystemRoutineAddress(&funcName));
	}

	return fNtQueryInformationThread(ThreadHandle, ThreadInformationClass, ThreadInformation, ThreadInformationLength, ReturnLength);
}
