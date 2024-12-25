
// 24. Отправка и получение данных из именованного канала. Данные содержатся в строковой форме. 
// Перед отправкой следующей строки клиенту необходимо дождаться ответа от сервера

// 1. опредление размера буферов, самих буферов, имя канала

// на стороне сервера
// 2. создание канала с модами работы и типами сообщений
// 3. ожидание подключени клиента
// 4. чтение сообщения
// 5. запись ответа
// 6. вывод промежуточных данных на консоль

// на стороне клиента
// 7. открыть файл по имени канала
// 8. описать мод и установить состояние канала
// 9. если состояние успешно установлено, написать серверу
// 10. принять ответ сервера
// 11. вывод промежуточных данных на консоль

// первым запускать процесс, который начинает писать

#include "tasks.h"
#include <stdio.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#define SIZE_BUFFER 1256

int _24_namedPipe_Test() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	LPCWSTR pipeName = L"//./pipe/MyPipe";

	WCHAR outBuffer[SIZE_BUFFER];
	WCHAR inBuffer[SIZE_BUFFER];
	int messageCounter = 0;

	while (TRUE) {	
		// создание канала
		HANDLE hPipe = CreateNamedPipeW(
		pipeName,
		PIPE_ACCESS_DUPLEX, // режима доступа к каналу: двусторонний
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, //режимы работы канала: передавать сообщения|читать сообщения|ждать
		PIPE_UNLIMITED_INSTANCES, // сколько угодно подключений
		SIZE_BUFFER * sizeof(WCHAR), // буфер на чтение
		SIZE_BUFFER , // буфер на запись
		INFINITE, // макс. время ожидания сообщения
		NULL // структура безопасности
		);

		int read;
		ConnectNamedPipe(hPipe, NULL); // ожидание подключения клиента
		// чтение сообщения клиента
		ReadFile(
			hPipe,
			inBuffer,
			SIZE_BUFFER * sizeof(WCHAR),
			&read,
			NULL
		);
		wprintf(L"(сервер) прочел: %d байт; сообщение: %s;\n", read, inBuffer);
		// ответ клиенту
		swprintf_s(outBuffer, SIZE_BUFFER, L"OK %d", ++messageCounter);
		WriteFile(
			hPipe,
			outBuffer,
			SIZE_BUFFER * sizeof(WCHAR),
			NULL,
			NULL
		);
		wprintf(L"(сервер) ответил: %s;\n", outBuffer);

		CloseHandle(hPipe);
	}

	return 0;
}