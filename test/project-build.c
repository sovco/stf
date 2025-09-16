#include <stdlib.h>

#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);
    Nob_Cmd cmd = { 0 };
    nob_cmd_append(&cmd, "mkdir", "-p", "build");
    if (!nob_cmd_run(&cmd)) return EXIT_FAILURE;
    nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-Wpedantic", "-o", "build/stf-tests", "-Iinclude", "test/stf-tests.c");
    if (!nob_cmd_run(&cmd)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
