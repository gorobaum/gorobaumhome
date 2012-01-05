
#ifndef DIRMANAGER_H_
#define DIRMANAGER_H_

#include <dirent.h>
#include <vector>

class File;

class DirManager {

  public:

    DirManager () : current_dir_(NULL), current_dir_path_(NULL) {} 

    ~DirManager ();

    bool start ();

    bool change_dir (const char *path);

    const char* get_current_dir_path () { return current_dir_path_; }

    size_t num_files () { return files_.size(); }

    File*& get_file (size_t index) { return files_.at(index); }

    void sort_by_name ();

    bool go_up ();

    bool go_down (size_t index);

  private:

    DIR                 *current_dir_;
    char                *current_dir_path_;
    std::vector<File*>  files_;

    bool do_change_dir (char *path);

    void read_dir ();

    void close ();

};

#endif

