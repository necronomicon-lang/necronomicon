#ifndef necronomicon_chunk_h
#define necronomicon_chunk_h

#include "common.h"

typedef enum
{
    OP_RETURN,
} OpCode;

typedef struct
{
    int count;
    int capacity;
    u8* code;
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, u8 byte);

#endif