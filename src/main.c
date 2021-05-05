#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "vm.h"
#include "chunk.h"
#include "debug.h"
#include "fileio.h"

internal void repl()
{
    char line[1024];

    loop
    {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin))
        {
            printf("\n");
            break;
        }        

        interpret(line);
    }
}

internal void run_file(const char* path)
{
    char* source = read_file(path);
    InterpretResult result = interpret(source);
    free(source);

    if (result == INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, const char* argv[])
{
    init_vm();

    if (argc == 1)
    {
        repl();
    }
    else if (argc == 2)
    {
        run_file(argv[1]);
    }
    else
    {
        fprintf(stderr, "Usage: necro [path]\n");
    }

    free_vm();

    return 0;
}