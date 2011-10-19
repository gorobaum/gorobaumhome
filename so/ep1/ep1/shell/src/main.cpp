
#include <cstdlib>
#include <unistd.h>
#include "shell.h"

int main (int argc, char **argv) {

    Shell shell;
    int page_size = 20;

    if (argc >= 2)
        page_size = atoi(argv[1]);

    shell.init(page_size);

    while (shell.update());

    shell.close();

    return EXIT_SUCCESS;
}

