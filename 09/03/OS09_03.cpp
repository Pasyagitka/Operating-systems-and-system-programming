#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <fileapi.h>

BOOL printFileText(LPWSTR fileName);


BOOL insRowFileTxt(LPWSTR fileName, const char *str, DWORD row)	{
	try
	{
		HANDLE hf = CreateFileW(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hf == INVALID_HANDLE_VALUE)
		{
			std::cout << "Open file unsuccessfully\n";
			CloseHandle(hf);
			return false;
		}

		DWORD n = NULL;
		char rbuf[1024];
		BOOL b;
		ZeroMemory(rbuf, sizeof(rbuf));

		if (!ReadFile(hf, &rbuf, sizeof(rbuf), &n, NULL)) {
			std::cout << "Read file unsuccessfully\n";
			CloseHandle(hf);
			return false;
		}
		else {
			std::cout << "Number of bytes read: " << n << "\n";
			std::cout << rbuf << std::endl;
			CloseHandle(hf);
		}

		HANDLE hAppend = CreateFileW(fileName, GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		char wbuf[1024];
		ZeroMemory(wbuf, sizeof(wbuf));

		int line = 1;
		int j = 0;
		int k = 0;
		for (int i = 0; i < n; i++) {
			if (line == row) {
				for (int k = 0; k < strlen(str); k++) {
					wbuf[j++] = str[k];
					if (str[k + 1] == '\0') {
						wbuf[j++] = '\n';
						row = 0;
						break;
					}
				}
				i--;
			}
			else wbuf[j++] = rbuf[i];

			if (rbuf[i] == '\n') line++;
			if (rbuf[i + 1] == '\0' && row == -1) {
				for (int k = 0; k < strlen(str); k++) {
					wbuf[j++] = str[k];
					if (str[k + 1] == '\0') {
						wbuf[j++] = '\n';
						row = 0;
						break;
					}
				}
			}
		}

		if (!WriteFile(hAppend, wbuf, j, &n, NULL)) {
			std::cout << "Write file unsuccessfully\n";
			CloseHandle(hAppend);
			return false;
		}
		else {
			std::cout << "Write file successfully\n";
			std::cout << "Number of writed bytes: " << n << "\n";
			std::cout << wbuf << std::endl;
			CloseHandle(hAppend);
			return true;
		}
	}
	catch (const char *err)
	{
		std::cerr << "Error: " << err << " \n";
		return false;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	LPWSTR fileName = (LPWSTR)(L"C:\\Users\\pasyagitka\\Desktop\\OS09_01.txt");

	insRowFileTxt(fileName, (char *)"0", 1);
	insRowFileTxt(fileName, (char *)"-1", -1);
	insRowFileTxt(fileName, (char *)"5", 5);
	insRowFileTxt(fileName, (char *)"7", 7);

	system("pause");
	return 0;
}



BOOL printFileText(LPWSTR fileName)
{
	try
	{
		HANDLE hf = CreateFileW(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hf == INVALID_HANDLE_VALUE) throw "open file failed";

		DWORD n = NULL;
		char buf[1024];

		ZeroMemory(buf, sizeof(buf));
		if (!ReadFile(hf, &buf, 1024, &n, NULL)) throw "read file failed";
		std::cout << buf << std::endl;
		CloseHandle(hf);
		return true;
	}
	catch (const char *em)
	{
		std::cout << "error:" << em << std::endl;
		return false;
	}
}