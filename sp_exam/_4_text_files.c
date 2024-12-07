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

HANDLE Open(LPCWSTR file_name, DWORD desired_access) {
	return CreateFileW(
		file_name,
		desired_access,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
}

int Read(HANDLE file_handle, LPWSTR buffer, size_t buffer_count) {
	int bytes_read; // ������� ������� ������� ������
	ReadFile(
		file_handle,
		buffer,
		buffer_count * sizeof(WCHAR),
		&bytes_read,
		NULL
	);
	return bytes_read;
}

int Write(HANDLE file_handle, LPWSTR buffer) {
	int bytes_write; // ������� ������� ������� ������
	WriteFile(
		file_handle,
		buffer,
		wcslen(buffer) * sizeof(WCHAR),
		&bytes_write,
		NULL
	);
	return bytes_write;
}

int ChangeFilePosition(HANDLE file_handle, DWORD move_method) {
	return SetFilePointer(
		file_handle,
		NULL,
		NULL,
		move_method
	);
}

int _4_textFiles_Test() {
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
	int buffer_count = 100;
	LPWSTR buffer = calloc(buffer_count, sizeof(WCHAR));
	int bytes_read = Read(input, buffer, buffer_count);
	wprintf(L"%d bytes: %s\n", bytes_read, buffer);

	if (bytes_read == 0) return -1;

	// ���������� �� ������ (��� ���������� ������ ������� �������)
	int output_offset = ChangeFilePosition(output, FILE_END);
	if (output_offset == INVALID_SET_FILE_POINTER) {
		wprintf(L"������ ��������� �������: %d\n", GetLastError());
		return -1;
	}
	
	int bytes_write = Write(output, buffer);
	wprintf(L"%d bytes", bytes_write);
	if (bytes_write == 0) return -1;

	// �������� ������������
	CloseHandle(input);
	CloseHandle(output);
	return 0;
};