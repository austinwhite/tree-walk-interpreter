#ifndef CPPLOX_SRC_SCANNER_H
#define CPPLOX_SRC_SCANNER_H

#include <map>
#include <string>
#include <vector>

#include "token.hpp"

class Scanner {
  public:
    Scanner(const std::string &source);
    std::vector<Token> scan_tokens();

  private:
    std::string source;
    std::vector<Token> tokens;
    static const std::map<std::string, TokenType> keywords;
    int start = 0;
    int current = 0;
    int line = 1;

    void scan_token();
    bool is_at_end();
    char advance();
    void add_token(TokenType type);
    void add_token(TokenType type, std::string literal);
    bool match(char expected);
    char peek();
    char peek_next();
    void string();
    void number();
    void identifier();
    bool is_digit(char c);
    bool is_alpha(char c);
    bool is_alphanumeric(char c);
};

#endif // !CPPLOX_SRC_SCANNER_H
