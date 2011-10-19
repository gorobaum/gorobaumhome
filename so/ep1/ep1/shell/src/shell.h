
#ifndef SHELL_H_
#define SHELL_H_

#include <string>
#include <vector>
#include "dirmanager.h"
#include "command.h"

using std::string;
using std::vector;

class Shell {

  public:

    Shell()
        : screen_height_(0), screen_width_(0),
          page_size_(20), selection_pos_(0),
          command_(this) {}

    void init(size_t page_size);

    void init_curses();

    void end_curses();

    bool update();

    void close();

  private:

    size_t      screen_height_,
                screen_width_;
    size_t      page_size_;
    size_t      selection_pos_;
    DirManager  dir_manager_;
    Command     command_;
    std::string message_;

    void display();

    void display_header();

    void display_line();

    void display_files();

    void display_message();

    void display_file_info(File *file);

    void display_hud();

    bool handle_input();

    void move_selection(int offset);

    void change_dir();

    vector<string> read_args();

};

#endif

