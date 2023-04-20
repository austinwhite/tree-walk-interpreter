#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "lox.hpp"
#include "scanner.hpp"

bool Lox::had_error = false;

void Lox::report(int line, const std::string &where,
                 const std::string &message) {
    std::cout << "[ line" << where << "] Error" << where << ": " << message;
}

void Lox::error(int line, const std::string &message) {
    report(line, "", message);
    had_error = true;
}

void Lox::run(const std::string source) {
    Scanner scanner(source);
    const std::vector<Token> tokens = scanner.scan_tokens();

    for (Token token : tokens) {
        std::cout << token.str() << std::endl;
    }
}

int Lox::run_file(const char *path) {
    const std::ifstream file(path);
    std::stringstream buffer;

    buffer << file.rdbuf();
    run(buffer.str());

    if (had_error) {
        return 65;
    }

    return 0;
}

int Lox::run_prompt() {
    for (;;) {
        std::string line;

        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.empty()) {
            break;
        }

        run(line);
        had_error = false;
    }
    return 0;
}
