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
    else{
        printf("##################\n### MEMPROC ERROR: ALLOCATE: malloc returned NULL pointer while allocating %s type\n##################\n", memTypeName[type]);
    }
    
    return temp;
}

void Deallocate(void* ptr, int size, MemoryType type)
{
    if (ptr == NULL){
        printf("##################\n### MEMPROC ERROR: DEALLOCATE: Tried to free NULL pointer of type %s\n##################\n", memTypeName[type]);
        return;
    }

    bytesFreed[type] += size;
    bytesFreed[ALLOC_TOTAL] += size;
    freeCount[type]++;

    if (bytesFreed[type] > bytesAllocated[type])
        printf("##################\n### MEMPROC ERROR: DEALLOCATE: Pointer of type %s freed more than allocated (check Deallocation of NULL pointers)\n##################\n", memTypeName[type]);

    free(ptr);
}

void PrintMemory()
{
    printf("%-15s%8s%8s%8s%8s%8s \n", "Type", "#A", "#F", "A", "F", "L");
    printf("-------------------------------------------------------\n");
    
    int totalCount;
    
    for (int i = 0; i < MEM_TYPE_LENGTH; i++){
        printf("%-15s%8d%8d%8d%8d%8d\n", memTypeName[i], mallocCount[i], freeCount[i], bytesAllocated[i], bytesFreed[i], bytesAllocated[i] - bytesFreed[i]);
        if (i == MEM_TYPE_LENGTH - 2)
            printf("-------------------------------------------------------\n");
    }
    printf("\n");
}
