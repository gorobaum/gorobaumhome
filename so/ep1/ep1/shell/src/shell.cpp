
#include <ncurses.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#include "file.h"
#include "aux.h"

using std::string;
using std::vector;

void Shell::init(size_t page_size) {
    page_size_ = page_size;
    init_curses();
    dir_manager_.start();
}

bool Shell::update() {
    display();
    return handle_input();
}

void Shell::close() {
    end_curses();
}

void Shell::init_curses() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    getmaxyx(stdscr, screen_height_, screen_width_);
}

void Shell::end_curses() {
    endwin();
}

void Shell::display() {
    erase();
    display_header();
    display_files();
    display_hud();
    display_message();
    refresh();
}

void Shell::display_line() {
    for (size_t i = 0; i < screen_width_; i++)
        addch(ACS_HLINE);
}

void Shell::display_header() {
    string header = "Current directory: ";
    header = header + dir_manager_.get_current_dir_path() + "\n";
    display_line();
    printw(header.c_str());
    display_line();
}

void Shell::display_files() {
    size_t current_page = selection_pos_ / page_size_,
           page_begin = current_page * page_size_,
           page_end = std::min(page_begin + page_size_,
                               dir_manager_.num_files());
    for (size_t i = page_begin; i < page_end; i++) {
        if (i == selection_pos_) attron(A_STANDOUT);
        display_file_info(dir_manager_.get_file(i));
        if (i == selection_pos_) attroff(A_STANDOUT);
    }
}

void Shell::display_file_info(File *file) {
    char *perms = file->get_perm(),
         *date = file->get_date();
    printw(perms);
    addch(' ');
    printw("%20d", file->get_size());
    addch(' ');
    printw("%10s", date);
    addch(' ');
    printw(file->get_name());
    addch(10);
    free(perms);
    free(date);
}

void Shell::display_hud() {
    display_line();
    string hud =
        "(V)iew, (E)dit, (R)un, (C)hange directory, (U)p, (D)own, (Q)uit\n";
    printw(hud.c_str());
}

void Shell::display_message() {
    display_line();
    printw(message_.c_str());
    message_.clear();
}

bool Shell::handle_input() {
    File *file = dir_manager_.get_file(selection_pos_);
    char *name = file->get_name();
    int input;
    switch ((input = getch())) {
        case KEY_UP:
            move_selection(-1);
            break;
        case KEY_DOWN:
            move_selection(1);
            break;
        case KEY_PPAGE:
        case KEY_LEFT:
            move_selection(-page_size_);
            break;
        case KEY_NPAGE:
        case KEY_RIGHT:
            move_selection(page_size_);
            break;
        case 'c':
            change_dir();
            break;
        case 'v':
            if (access(name, R_OK) == 0)
                command_.view(name);
            else
                message_ = "Error: Permission denied. No read access";
            break;
        case 'e':
            if (access(name, R_OK | W_OK) == 0)
                command_.edit(name);
            else
                message_ = "Error: Permission denied. No read or write access";
            break;
        case 'r':
            if (file->is_dir())
                message_ = "Error: Permission denied. Cannot execute a directory.";
            else if (access(name, R_OK | X_OK) == 0)
                command_.exec("./" + string(name), read_args());
            else
                message_ = "Error: Permission denied. No read or execute access.";
            break;
        case 'q':
            return false;
        default:
            break;
    }
    return true;
}

void Shell::move_selection(int offset) {
    if (offset < 0) {
        selection_pos_ = selection_pos_ > size_t(abs(offset))
            ? selection_pos_ + offset
            : 0;
    }
    else if (offset > 0) {
        selection_pos_ = std::min(selection_pos_ + offset,
                                  dir_manager_.num_files() - 1);
    }
}

void Shell::change_dir() {
    const char *dir_name = dir_manager_.get_file(selection_pos_)->get_name();
    if (!dir_manager_.change_dir(dir_name))
        message_ = "Could not change directory."; // do something!
    else selection_pos_ = 0;
}

vector<string> Shell::read_args() {
    vector<string>  arg_list;
    string          arg_string;
    int             input;
    echo();
    nocbreak();
    printw("Program arguments: ");
    while ((input = getch()) != '\n')
        if (input != ' ')
            arg_string.push_back(input);
        else if (!arg_string.empty()) {
            arg_list.push_back(arg_string);
            arg_string.clear();
        }
    if (!arg_string.empty())
        arg_list.push_back(arg_string);
    cbreak();
    noecho();
    return arg_list;
}


