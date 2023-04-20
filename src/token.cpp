#include <string>
#include <vector>

#include "token.hpp"

static std::vector<std::string> token_names{
    "LEFT_PAREN",    "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "COMMA",
    "DOT",           "MINUS",       "PLUS",       "SEMICOLON",   "SLASH",
    "STAR",

    "BANG",          "BANG_EQUAL",  "EQUAL",      "EQUAL_EQUAL", "GREATER",
    "GREATER_EQUAL", "LESS",        "LESS_EQUAL",

    "IDENTIFIER",    "STRING",      "NUMBER",

    "AND",           "CLASS",       "ELSE",       "FALSE",       "FUN",
    "LAMBDA",        "FOR",         "IF",         "NIL",         "OR",
    "PRINT",         "RETURN",      "SUPER",      "THIS",        "TRUE",
    "VAR",           "WHILE",       "EOF"};

Token::Token(TokenType type, const std::string &lexeme,
             const std::string &literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}

std::string Token::str() const {
    return token_names[type] + " " + lexeme + " " +
           ((type == NUMBER || type == STRING) ? literal : "");
}
