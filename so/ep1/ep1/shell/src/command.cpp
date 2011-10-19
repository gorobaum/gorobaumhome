
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#include "command.h"
#include "aux.h"

typedef char* cstr_t;

void Command::exec(string prog_name, vector<string> arg_list) {
    pid_t pid;
    size_t arg_num = arg_list.size()+2;
    cstr_t *args = new cstr_t[arg_num];
    args[0] = copy_string(prog_name.c_str());
    args[arg_num-1] = NULL;
    for (size_t i = 1; i+1 < arg_num; i++)
        args[i] = copy_string(arg_list.at(i-1).c_str());
    shell_->end_curses();
    if ((pid = fork())) {
        wait(NULL);
        puts("\nPress ENTER to continue.\n");
        fflush(stdout);
    } else {
        execvp(prog_name.c_str(), args);
        printf("\nCould not execute program '%s'.\n\n", prog_name.c_str());
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    shell_->init_curses();
    while (getch() != '\n');
    for (size_t i = 0; i+1 < arg_num; i++)
        delete[] args[i];
    delete[] args;
}

void Command::view(string doc_name) {
    vector<string> arg_list;
    arg_list.push_back(doc_name);
    exec("less", arg_list);
}

void Command::edit(string doc_name) {
    vector<string> arg_list;
    arg_list.push_back(doc_name);
    exec("editor", arg_list);
}

