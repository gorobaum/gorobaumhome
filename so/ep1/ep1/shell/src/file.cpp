
#include <cstdlib>
#include <time.h>
#include "file.h"

File* File::open(std::string path) {
    struct stat info;
    File* file = NULL;
    if (stat(path.c_str(), &info) == 0) {
        file = new File(info);
        file->name_ = path;
    }
    return file;
}

char* File::get_date() {
    struct tm * timeinfo;
    char *buffer = new char[11];
    timeinfo = localtime(&info_.st_mtime);
    strftime(buffer, 11, "%d %b %y", timeinfo);
    return buffer;
}

size_t File::get_size() {
    return info_.st_size;
}

char* File::get_perm() {
    char *buffer = new char[11];
    buffer[0] = (S_ISDIR(info_.st_mode)) ? 'd' : '-';
    buffer[1] = (info_.st_mode & S_IRUSR) ? 'r' : '-';
    buffer[2] = (info_.st_mode & S_IWUSR) ? 'w' : '-';
    buffer[3] = (info_.st_mode & S_IXUSR) ? 'x' : '-';
    buffer[4] = (info_.st_mode & S_IRGRP) ? 'r' : '-';
    buffer[5] = (info_.st_mode & S_IWGRP) ? 'w' : '-';
    buffer[6] = (info_.st_mode & S_IXGRP) ? 'x' : '-';
    buffer[7] = (info_.st_mode & S_IROTH) ? 'r' : '-';
    buffer[8] = (info_.st_mode & S_IWOTH) ? 'w' : '-';
    buffer[9] = (info_.st_mode & S_IXOTH) ? 'x' : '-';
    buffer[10] = '\0';
    return buffer;
}

bool File::is_dir() {
    return S_ISDIR(info_.st_mode);
}


