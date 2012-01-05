
#include <cstring>
#include "aux.h"

char* copy_string(const char* src) {
    char *copy = new char[strlen(src)+1];
    return strcpy(copy, src);
}

