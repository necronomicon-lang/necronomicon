#include <stdio.h>
#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

void init_vm()
{
    
}

void free_vm()
{

}

internal InterpretResult run()
{
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;)
    {
        #ifdef DEBUG_TRACE_EXECUTION
            disassemble_instruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
        #endif

        u8 instruction;
        switch (instruction == READ_BYTE())
        {
            case OP_CONSTANT:
            {
                Value constant = READ_CONSTANT();
                print_value(constant);
                printf("\n");
            } break;

            case OP_RETURN:
            {
                return INTERPRET_OK;
            } break;
        }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}