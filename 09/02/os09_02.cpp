#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <fileapi.h>

BOOL printFileText(LPCSTR FileName);
BOOL delRowFileTxt(LPCSTR FileName, DWORD rowToDelete);

void main() {
	setlocale(LC_ALL, "Russian");
	LPCSTR file = (LPCSTR)("OS09_01.txt");


    std::cout << "----------------------------------------------------------" << std::endl;
    printFileText(file);
	delRowFileTxt(file, 1);
    std::cout << "----------------------------------------------------------" << std::endl;
    printFileText(file);
	delRowFileTxt(file, 3);
    std::cout << "----------------------------------------------------------" << std::endl;
    printFileText(file);
	delRowFileTxt(file, 8);
    std::cout << "----------------------------------------------------------" << std::endl;
    printFileText(file);
	delRowFileTxt(file, 10);
    std::cout << "----------------------------------------------------------" << std::endl;
    printFileText(file);


	system("pause");
}

BOOL delRowFileTxt(LPCSTR FileName, DWORD rowToDelete) {
	try
	{
        printf("fileName: %s\n", FileName);
        printf("Row to delete: %d\n", rowToDelete);

		DWORD n = NULL;
		char rbuf[1024], wbuf[1024];
        ZeroMemory(rbuf, sizeof(rbuf));
        ZeroMemory(wbuf, sizeof(wbuf));

		HANDLE hF = CreateFile(FileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hF == INVALID_HANDLE_VALUE) throw "open file failed hF";

        if (!ReadFile(hF, &rbuf, 512, &n, NULL))  throw "read file failed";
        CloseHandle(hF);

        hF = CreateFile(FileName, GENERIC_WRITE, NULL, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   
		int currentLine = 1;
		for (int i = 0, j = 0; i < n; i++) {
			if (currentLine != rowToDelete) {
            	wbuf[j++] = rbuf[i];
            }
			if (rbuf[i] == '\n') currentLine++;
		}
        if (!WriteFile(hF, wbuf, n, &n, NULL)) throw "Error writing to file\n";
        CloseHandle(hF);

        return true;
	}
	catch (const char* em) {
		return false;
	}
}


BOOL printFileText(LPCSTR FileName) {
    try
    {
        HANDLE hf = CreateFile((LPCSTR)FileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hf == INVALID_HANDLE_VALUE) throw "open file failed";
        std::cout << "Create file or open successful -------------------------------------------" << std::endl;
        DWORD n = NULL;
        char buf[1024];

        ZeroMemory(buf, sizeof(buf));
        BOOL b = ReadFile(hf, &buf, 512, &n, NULL); //файл, буфер, читать байт, записано байт, асинхр) 
        if (!b)  throw "read file failed";
        std::cout << "Read file " << n << " bytes successful: \n" << buf << std::endl;
        CloseHandle(hf);
        return true;
    }
    catch (const char *em)  { return false;  }
}