#ifndef MEMPROC_H
#define MEMPROC_H

#include <stdlib.h>
#include <stdio.h>


typedef enum MemoryType {ALLOC_TOKEN_CONTENT, ALLOC_TOKEN_TREE, ALLOC_ENV_HEADER, ALLOC_ENV_ENTRY, ALLOC_VALUE, ALLOC_STRING, ALLOC_STRING_CONTENT, ALLOC_OTHER, ALLOC_TOTAL, MEM_TYPE_LENGTH} MemoryType;

extern int bytesAllocated[MEM_TYPE_LENGTH], bytesFreed[MEM_TYPE_LENGTH], mallocCount[MEM_TYPE_LENGTH], freeCount[MEM_TYPE_LENGTH];
extern char* memTypeName[];

void* Allocate(size_t size, MemoryType type);
void Deallocate(void* ptr, int size, MemoryType type);
void PrintMemory();

#endif
