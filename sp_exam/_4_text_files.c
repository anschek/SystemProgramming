// 4. ��������� ��� ���������� � ������ ���������� �������� �� ���������� ����� � ����������� ������� ��� � ������ ��������� ����. 
// ��� ������ � ������� ������������ ������� WinAPI.


// 1. ������� ����� ��� ������ � ������. ��� ������ ������������� � ����� ������� (�� �������). 
// � ������� ����� �������� ������. ��������� ������ ������ ���� utf-16 le
// 2. �������� ������� ��������, ��� �������� � ����������� OPEN_EXISTING
// 3. �������� ������� ������
// 4. �������� ������� ������
// 5. �������� ������
// *6. ���� ���������� ������� �� ������� - ����� ��������� �������


#include"tasks.h"
#include<stdio.h>
#include<malloc.h>
#include<Windows.h>
// ��� �������
#include <io.h>
#include <fcntl.h>

HANDLE Open(LPCWSTR fileName, DWORD desiredAccess) {
	return CreateFileW(
		fileName,
		desiredAccess,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
}

int Read(HANDLE fileHandle, LPWSTR buffer, size_t bufferCount) {
	int bytesRead; // ������� ������� ������� ������
	ReadFile(
		fileHandle,
		buffer,
		bufferCount * sizeof(WCHAR),
		&bytesRead,
		NULL
	);
	return bytesRead;
}

int Write(HANDLE hFile, LPWSTR buffer) {
	int bytesWrite; // ������� ������� ������� ������
	WriteFile(
		hFile,
		buffer,
		wcslen(buffer) * sizeof(WCHAR),
		&bytesWrite,
		NULL
	);
	return bytesWrite;
}

int ChangeFilePosition(HANDLE fileHandle, DWORD moveMethod) {
	return SetFilePointer(
		fileHandle,
		NULL,
		NULL,
		moveMethod
	);
}

int _4_text_files_Test() {
	// ������������� ������� �������� ������� �� UTF-16
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	// ��������� �����
	HANDLE input = Open(L"input.txt", GENERIC_READ);
	HANDLE output = Open(L"output.txt", FILE_APPEND_DATA); // ����� ������������ generic_write ��� ������ � ����

	if (input == -1 || output == -1) {
		wprintf(L"������ �������� ������: %d\n", GetLastError());
		return -1;
	}

	// ������ �� �������
	int bufferCount = 100;
	LPWSTR buffer = calloc(bufferCount, sizeof(WCHAR));
	int bytesRead = Read(input, buffer, bufferCount);
	wprintf(L"%d bytes: %s\n", bytesRead, buffer);

	if (bytesRead == 0) return -1;

	// ���������� �� ������ (��� ���������� ������ ������� �������)
	int outputOffset = ChangeFilePosition(output, FILE_END);
	if (outputOffset == INVALID_SET_FILE_POINTER) {
		wprintf(L"������ ��������� �������: %d\n", GetLastError());
		return -1;
	}
	
	int bytesWrite = Write(output, buffer);
	wprintf(L"%d bytes", bytesWrite);
	if (bytesWrite == 0) return -1;

	// �������� ������������
	CloseHandle(input);
	CloseHandle(output);
	return 0;
};