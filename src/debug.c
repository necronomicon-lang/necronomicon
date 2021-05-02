#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassemble_chunk(Chunk* chunk, const char* name)
{
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;)
    {
        offset = disassemble_instruction(chunk, offset);
    }
}

internal int simple_instruction(const char* name, int offset)
{
    printf("%s\n", name);
    return offset + 1;
}

internal int constant_instruction(const char* name, Chunk* chunk, int offset)
{
    u8 constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    print_value(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

int disassemble_instruction(Chunk* chunk, int offset)
{
    printf("%04d ", offset);

    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
    {
        printf("   | ");
    }
    else
    {
        printf("%4d ", chunk->lines[offset]);
    }

    u8 instruction = chunk->code[offset];
    switch (instruction)
    {
        case OP_CONSTANT:
        {
            return constant_instruction("OP_CONSTANT", chunk, offset);
        } break;

        case OP_RETURN:
        {
            return simple_instruction("OP_RETURN", offset);
        } break;

        default:
        {
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
        } break;
    }
}