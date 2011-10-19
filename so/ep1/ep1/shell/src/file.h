
#ifndef FILE_H_
#define FILE_H_

#include <sys/stat.h>
#include <sys/types.h>
#include <string>

class File {

  public:

    static File* open(std::string path);

    char* get_date();

    size_t get_size();

    char* get_perm();

    bool is_dir();

    char* get_name() { return (char*)name_.c_str(); }

  private:

    File(struct stat& info) : info_(info) {}

    struct stat info_;
    std::string name_;

};

#endif

