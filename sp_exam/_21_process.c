
// 21. Программа с запуском стороннего процесса. 
// исполняемый файл стороннего процесса подготавливается заранее

// 1. создание файла стороннего процесса
// 2. описани пути, аргументов cmd, стартовой и выходной структур
// 3. создание процесса
// 4. ожидание и опредление кода возврата

#include <stdio.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

int _21_externalProcessLaunch_Test() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	LPCWSTR otherProcessPath = L"..\\x64\\Debug\\other_process.exe";
	LPWSTR cmdArgs = L"2 10.5 7 str 'word'";

	STARTUPINFO* sti = calloc(1, sizeof(STARTUPINFO));// начальная информация для запуска
	sti->cb = sizeof(STARTUPINFO); // контрольный байт
	PROCESS_INFORMATION* pi = calloc(1, sizeof(PROCESS_INFORMATION)); // выходная информация с дескрипторами

	BOOL success = CreateProcess(
		otherProcessPath,
		cmdArgs,
		NULL, // структура безопасности процесса
		NULL, // структура безопасности потока
		TRUE, // наследование дескрипторов
		0, // флаги создания
		NULL, // среда
		NULL, // относительная папка
		sti,
		pi
	);

	if (!success) return GetLastError();
	wprintf(L"процесс успешно создан\n");

	DWORD exitCode;
	WaitForSingleObject(pi->hProcess, INFINITE);
	GetExitCodeProcess(pi->hProcess, &exitCode);
	wprintf(L"код заверешния дочернего процесса: %d\n", exitCode);

	CloseHandle(pi->hProcess);
	CloseHandle(pi->hThread);

	return GetLastError();
}