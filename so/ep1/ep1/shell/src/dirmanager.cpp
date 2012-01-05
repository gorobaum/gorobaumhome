
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <unistd.h>
#include "dirmanager.h"
#include "file.h"
#include "aux.h"

using std::vector;

DirManager::~DirManager () {
    close();
}

bool DirManager::start () {
    char *initial_path = getcwd(NULL, 0);
    if (!initial_path) return false;
    return do_change_dir(initial_path);
}

bool DirManager::change_dir  (const char *path) {
    if (current_dir_) close();
    return do_change_dir(copy_string(path));
}

static bool comp_by_name (File *file1, File *file2) {
    return strcmp(file1->get_name(), file2->get_name()) < 0;
}

void DirManager::sort_by_name () {
    if (current_dir_)
        sort(files_.begin(), files_.end(), comp_by_name);
}

bool DirManager::do_change_dir (char *path) {
    if (chdir(path) == -1) {
        start();
        return false;
    }
    current_dir_path_ = getcwd(NULL, 0);
    if (!current_dir_path_) return false;
    current_dir_ = opendir(current_dir_path_);
    if (!current_dir_) return false;
    read_dir();
    sort_by_name();
    return true;
}

void DirManager::read_dir () {
    struct dirent* dirent;
    while ((dirent = readdir(current_dir_)))
        files_.push_back(File::open(dirent->d_name));
}

void DirManager::close () {
    closedir(current_dir_);
    current_dir_ = NULL;
    free(current_dir_path_);
    current_dir_path_ = NULL;
    for (size_t i = 0; i < files_.size(); i++)
        delete files_.at(i);
    files_.clear();
}


