#include <Windows.h>
#include <iostream>

void sh(HANDLE pheap);

#define MB (1024*1024)

int main() {
    HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 4 * MB, 4 * 0 * MB);
    //, initial size - committed for the heap, maximum size of the heap, in bytes
    //reserves space in the virtual address space of the process and allocates physical storage for a specified initial portion of this block
    sh(heap);

    int* m = (int*)HeapAlloc(heap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 300000 * sizeof(int));
    //,,number of bytes to be allocated,    the return value is a pointer to the allocated memory block
    std::cout << "-- m = " << std::hex << m << " \n\n";
    sh(heap);

    HeapFree(heap, HEAP_NO_SERIALIZE, m); //A pointer to the memory block to be freed
    //nonzero
    sh(heap);

    HeapDestroy(heap); //nonzero

    system("pause");
}

void sh(HANDLE pheap) {
    PROCESS_HEAP_ENTRY phe;
    phe.lpData = NULL;
    while (HeapWalk(pheap, &phe)) {
        std::cout << "-- address = " << std::hex << phe.lpData
            << ", size = " << std::dec << phe.cbData
            << ((phe.wFlags & PROCESS_HEAP_REGION) ? " R" : "")             // начало непрерывной области
            << ((phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " U" : "")  // нераспределенная область
            << ((phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? " B" : "")         // распределенная область
            << "\n";
    }
    std::cout << "-----------------------------------\n\n";
}