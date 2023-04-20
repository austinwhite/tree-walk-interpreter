#include <iostream>

#include "lox.hpp"

int main(int argc, char **argv) {
    Lox lox;

    if (argc > 2) {
        std::cout << "Usage: lox [script]" << std::endl;
        return 64;
    } else if (argc == 2) {
        lox.run_file(argv[1]);
    } else {
        lox.run_prompt();
    }
    return 0;
}
