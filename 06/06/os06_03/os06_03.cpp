#include <Windows.h>
#include <iostream>

#define KB (1024)
#define PG (4 * KB)

int main()
{
    int pg = 256;
    int arraySize = pg * PG / 4;

    LPVOID xmemaddr = NULL;
    if (xmemaddr = VirtualAlloc(NULL, pg * PG, MEM_COMMIT, PAGE_READWRITE)) {
        //start address, size(bytes), protection
        std::cout << "--" << pg << "pages, VirtualAlloc = " << std::hex << xmemaddr << std::dec << "\n\n";
        
        int* m1 = new (xmemaddr) int[arraySize];
        for (int i = 0; i < arraySize; i++) {
            m1[i] = i;
        }
        //З C7 (199dec) - номер страницы
        //и E8
        //н ED
        //смещение E8E (3726dec)
        //адрес 199 * PG + 3726 = 818 830 (C7E8E)
        //00430000 + C7E8E = 4F7E8E
        system("pause");
    }
}
