#include "memproc.h"


int bytesAllocated[MEM_TYPE_LENGTH], bytesFreed[MEM_TYPE_LENGTH], mallocCount[MEM_TYPE_LENGTH], freeCount[MEM_TYPE_LENGTH];
char* memTypeName[] = {"TokenContent", "TokenTree", "EnvHeader", "EnvEntry", "Value", "String", "StringContent", "Other", "TOTAL"};

void* Allocate(size_t size, MemoryType type)
{
    void* temp = malloc(size);

    if (temp != NULL){
        bytesAllocated[type] += size;
        bytesAllocated[ALLOC_TOTAL] += size;
        mallocCount[type]++;
    }
    
    return temp;
}

void Deallocate(void* ptr, int size, MemoryType type)
{
    bytesFreed[type] += size;
    bytesFreed[ALLOC_TOTAL] += size;
    freeCount[type]++;
    free(ptr);
}

void PrintMemory()
{
    printf("%-15s%8s%8s%8s%8s%8s \n", "Type", "#A", "#F", "A", "F", "L");
    printf("-------------------------------------------------------\n");
    
    int totalCount;
    
    for (int i = 0; i < MEM_TYPE_LENGTH; i++)
        printf("%-15s%8d%8d%8d%8d%8d\n", memTypeName[i], mallocCount[i], freeCount[i], bytesAllocated[i], bytesFreed[i], bytesAllocated[i] - bytesFreed[i]);
    printf("\n");
}
