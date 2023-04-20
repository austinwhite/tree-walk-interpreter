#ifndef CPPLOX_SRC_LOX_H
#define CPPLOX_SRC_LOX_H

#include <iostream>

class Lox {
  public:
    static int run_file(const char *path);
    static int run_prompt();
    static void error(int line, const std::string &message);
    static void run(const std::string source);

  private:
    static bool had_error;

    static void report(int line, const std::string &where, const std::string &message);
};

#endif // !CPPLOX_SRC_LOX_H
