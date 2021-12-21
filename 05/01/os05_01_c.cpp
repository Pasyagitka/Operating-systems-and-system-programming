#include <Windows.h>
#include <iostream>
#include <bitset>

using namespace std;

void printProcessPriority(HANDLE h)
{
	// Идентификатор текущего процесса
	cout << "\nCurrent PID = " << GetCurrentProcessId() << endl;
	
	// Приоритет (приоритетный класс) текущего процесса
	DWORD priority = GetPriorityClass(h);
	
	switch(priority)
	{
		case IDLE_PRIORITY_CLASS: cout << "Priority = IDLE_PRIORITY_CLASS" << endl; break;
		case BELOW_NORMAL_PRIORITY_CLASS: cout << "Priority = BELOW_NORMAL_PRIORITY_CLASS" << endl; break;
		case NORMAL_PRIORITY_CLASS: cout << "Priority = NORMAL_PRIORITY_CLASS" << endl; break;
		case ABOVE_NORMAL_PRIORITY_CLASS: cout << "Priority = ABOVE_NORMAL_PRIORITY_CLASS" << endl; break;
		case HIGH_PRIORITY_CLASS: cout << "Priority = HIGH_PRIORITY_CLASS" << endl; break;
		case REALTIME_PRIORITY_CLASS: cout << "Priority = REALTIME_PRIORITY_CLASS" << endl; break;
		default: cout << "Priority = ?" << endl; break;
	}
}

void printThreadPriority(HANDLE h)
{
	// Идентификатор текущего (main) потока
	cout << "\nCurrent thread ID = " << GetCurrentThreadId() << endl;
	
	// Приоритет текущего потока
	DWORD priority = GetThreadPriority(h);
	
	switch(priority)
	{
		case THREAD_PRIORITY_LOWEST: cout << "Priority = THERAD_PRIORITY_LOWEST" << endl; break;
		case THREAD_PRIORITY_BELOW_NORMAL: cout << "Priority = THERAD_PRIORITY_BELOW_NORMAL" << endl; break;
		case THREAD_PRIORITY_NORMAL: cout << "Priority = THERAD_PRIORITY_NORMAL" << endl; break;
		case THREAD_PRIORITY_ABOVE_NORMAL: cout << "Priority = THERAD_PRIORITY_ABOVE_NORMAL" << endl; break;
		case THREAD_PRIORITY_HIGHEST: cout << "Priority = THERAD_PRIORITY_HIGHEST" << endl; break;
		case THREAD_PRIORITY_IDLE: cout << "Priority = THERAD_PRIORITY_IDLE" << endl; break;
		case THREAD_PRIORITY_TIME_CRITICAL: cout << "Priority = THREAD_PRIORITY_TIME_CRITICAL" << endl; break;
		default: cout << "Priority = ?" << endl; break;
	}	
}

void printAffinityMask(HANDLE h)
{
	
	DWORD processAffinityMask = NULL, threadAffinityMask = NULL;
		
	// Структура SYSTEM_INFO содержит информацию о текущей компьютерной системе, 
	// учитывая архитектуру и тип процессора, количество процессоров в системе, 
	// размер страницы, и другую похожую информацию.
	SYSTEM_INFO sys_info;
	
	
	// Функция GetProcessAffinityMask извлекает маску родственного процесса 
	// для заданного процесса и системную маску родственности для системы.
	if (!GetProcessAffinityMask(h,						// [in] Дескриптор процесса, маска родственности которого требуется
								&processAffinityMask,	// [out] Указатель на переменную, которая получает маску родственности для заданного процесса.
								&threadAffinityMask))	// [out] Указатель на переменную, которая получает маску родственности для системы.
	{
		throw "GetProcessAffinityMask";
	}
	
	// Если функция завершается успешно, величина возвращаемого значения - не ноль. Завершается ошибкой - 0.
	
	// bitset — это специальный класс-контейнер, который предназначен 
	// для хранения битовых значений (элементы этого контейнера могут
	// иметь значения: 0 и/или 1, истина или ложь).
	bitset<8> mask(processAffinityMask);
	
	// Маска родственного процесса - это битовый вектор, в котором каждый бит обозначает процессоры, на которых разрешается запуск процесса. Системная маска родственности - это битовый вектор, в котором каждый бит обозначает процессоры, которые конфигурированы в систему.
	cout << "\nProcess affinity mask: " << mask << endl;
	
	GetSystemInfo(&sys_info); // Адрес структуры SYSTEM_INFO, которая заполняется этой функцией.
	// Эта функция ничего не возвращает.
	
	cout << "Max count processors: " << sys_info.dwNumberOfProcessors << endl << endl;
	
}

void printIdealProcessor(HANDLE h)
{
	DWORD idealProcessor = -1;
	
	// Функция SetThreadIdealProcessor устанавливает предпочитаемый процессор для потока.
	idealProcessor = SetThreadIdealProcessor(h, // дескриптор процесса
						   MAXIMUM_PROCESSORS); // номер идеального процесса
						   // Значение MAXIMUM_PROCESSORS сообщает системе, 
						   // что поток не имеет привилегированного процессора.
	
	cout << "Thread ideal processor: " << dec << idealProcessor << endl;
}

int main()
{	
	HANDLE hp = GetCurrentProcess();
	HANDLE ht = GetCurrentThread();
	
	printProcessPriority(hp);
	printThreadPriority(ht);
	printAffinityMask(hp);
	printIdealProcessor(ht);
	
	return 0;
}