#ifndef CPPLOX_SRC_TOKEN_H
#define CPPLOX_SRC_TOKEN_H

#include <string>

enum TokenType {
    // Single-character tokens.
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens.
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords.
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,

    END_OF_FILE
};

class Token {
  public:
    TokenType type;
    std::string lexeme;
    std::string literal;
    int line;

    Token(TokenType type, const std::string &lexeme, const std::string &literal,
          int line);

    std::string str() const;
};

#endif // !CPPLOX_SRC_TOKEN_H
