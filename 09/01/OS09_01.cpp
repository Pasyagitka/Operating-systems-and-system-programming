#include <Windows.h>
#include <iostream>
#include <fileapi.h>

BOOL printFileText(LPCSTR FileName);
BOOL printFileInfo(LPCSTR FileName);

void main() {
    setlocale(LC_ALL, "Russian");

    LPCSTR file = (LPCSTR)("OS09_01.txt");
    printFileInfo(file);
    std::cout << "----------------------------------------------------------" << std::endl;
    printFileText(file);

    system("pause");
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
         //файл, буфер, читать байт, записано байт, асинхр) 
        if (!ReadFile(hf, &buf, 512, &n, NULL))  throw "read file failed";
        std::cout << "Read file " << n << " bytes successful: \n" << buf << std::endl;
        CloseHandle(hf);
        return true;
    }
    catch (const char *em)  { return false;  }
}

BOOL printFileInfo(LPCSTR FileName) {
    try {
        HANDLE hf = CreateFile((LPCSTR)FileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hf == INVALID_HANDLE_VALUE) throw "open file failed";
        std::cout << "Create file or open successful -------------------------------------------" << std::endl;

        printf("Filename: %s\n", FileName);

        DWORD type = GetFileType(hf);
        switch (type)
        {
        case FILE_TYPE_CHAR: 
            printf("FILE_TYPE_CHAR\n");
            break;
        case FILE_TYPE_DISK: 
            printf("FILE_TYPE_DISK\n");
            break;
        case FILE_TYPE_PIPE: 
            printf("FILE_TYPE_PIPE\n");
            break;
        case FILE_TYPE_REMOTE: 
            printf("FILE_TYPE_REMOTE\n");
            break;
        default:
            printf("FILE_TYPE_UNKNOWN\n");
            break;
        }

        printf("Filesize: %d bytes\n", GetFileSize(hf, NULL));
        BY_HANDLE_FILE_INFORMATION info;
        GetFileInformationByHandle(hf, &info);
        SYSTEMTIME time, localtime;
       

        if (!FileTimeToSystemTime(&info.ftCreationTime, &time)) throw "error file creation time";
        SystemTimeToTzSpecificLocalTime(NULL, &time, &localtime);
        printf("Created: %02d/%02d/%d  %02d:%02d:%02d\n", localtime.wDay, localtime.wMonth, localtime.wYear, localtime.wHour, localtime.wMinute, localtime.wSecond);

        if (!FileTimeToSystemTime(&info.ftLastWriteTime, &time)) throw "error file creation time";
        SystemTimeToTzSpecificLocalTime(NULL, &time, &localtime);
        printf("Last modified: %02d/%02d/%d  %02d:%02d:%02d\n", localtime.wDay, localtime.wMonth, localtime.wYear, localtime.wHour, localtime.wMinute, localtime.wSecond);

        CloseHandle(hf);
        return true;
    }
    catch (const char *em)  { return false;  }
}

