#include <Windows.h>
#include <iostream>

void sh(HANDLE pheap);

int main() {
    HANDLE pheap = GetProcessHeap();

    sh(pheap);
    {
        int size = 300000;
        int* m = new int[size];
        std::cout << "-- m = " << std::hex << m << ", size = " << std::dec << size << " \n\n";
    }
    sh(pheap);
    system("pause");
}

void sh(HANDLE pheap) {
    PROCESS_HEAP_ENTRY phe;
    phe.lpData = NULL; //A pointer to the data portion of the heap element.
    while (HeapWalk(pheap, &phe)) {
        std::cout << "-- address = " << std::hex << phe.lpData 
            << ", size = " << std::dec << phe.cbData //The size of the data portion of the heap element, in bytes
            << ((phe.wFlags & PROCESS_HEAP_REGION) ? " R" : "")             // начало непрерывной области
            << ((phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " U" : "")  // нераспределенная область
            //The heap element is located in a range of uncommitted memory within the heap region.
            << ((phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? " B" : "")         // распределенная область
            << "\n";
    }
    std::cout << "-----------------------------------\n\n";
}