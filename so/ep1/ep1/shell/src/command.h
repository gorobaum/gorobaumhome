
#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class Shell;

class Command {

  public:

    Command(Shell *shell) : shell_(shell) {}
    
    void exec(string prog_name, vector<string> arg_list);

    void view(string doc_name);

    void edit(string doc_name);

  private:

    Shell *shell_;

};

#endif

