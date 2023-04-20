#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "lox.hpp"
#include "scanner.hpp"
#include "token.hpp"

Scanner::Scanner(const std::string source) : source(source) {}

const std::map<std::string, TokenType> Scanner::keywords = {
    {"and", AND},   {"class", CLASS}, {"else", ELSE},     {"false", FALSE},
    {"for", FOR},   {"fun", FUN},     {"if", IF},         {"nil", NIL},
    {"or", OR},     {"print", PRINT}, {"return", RETURN}, {"super", SUPER},
    {"this", THIS}, {"true", TRUE},   {"var", VAR},       {"while", WHILE},
};

std::vector<Token> Scanner::scan_tokens() {
    while (!is_at_end()) {
        start = current;
        scan_token();
    }

    tokens.push_back(Token(END_OF_FILE, "", "", line));
    return tokens;
}

void Scanner::scan_token() {
    char c = advance();

    switch (c) {
    case '(':
        add_token(LEFT_PAREN);
        break;
    case ')':
        add_token(RIGHT_PAREN);
        break;
    case '{':
        add_token(LEFT_BRACE);
        break;
    case '}':
        add_token(RIGHT_BRACE);
        break;
    case ',':
        add_token(COMMA);
        break;
    case '.':
        add_token(DOT);
        break;
    case '-':
        add_token(MINUS);
        break;
    case '+':
        add_token(PLUS);
        break;
    case ';':
        add_token(SEMICOLON);
        break;
    case '*':
        add_token(STAR);
        break;
    case '!':
        add_token(match('=') ? BANG_EQUAL : BANG);
        break;
    case '=':
        add_token(match('=') ? EQUAL_EQUAL : EQUAL);
        break;
    case '<':
        add_token(match('=') ? LESS_EQUAL : LESS);
        break;
    case '>':
        add_token(match('=') ? GREATER_EQUAL : GREATER);
        break;
    case '/':
        // Comments go to the end of the line
        if (match('/')) {
            while (peek() != '\n' && !is_at_end())
                advance();
        } else {
            add_token(SLASH);
        }
        break;
    case ' ':
    case '\r':
    case '\t':
        // Ignore whitespace
        break;
    case '\n':
        line++;
        break;
    case '"':
        string();
        break;
    case 'o':
        if (match('r')) {
            add_token(OR);
        }
        break;
    default:
        if (is_digit(c)) {
            number();
        } else if (is_alpha(c)) {
            identifier();
        } else {
            Lox::error(line, "Unexpected character.");
        }
        Lox::error(line, "Unexpected Character.");
    }
}

bool Scanner::is_digit(char c) { return c >= '0' && c <= '9'; }

bool Scanner::is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::is_alphanumeric(char c) { return is_alpha(c) || is_digit(c); }

void Scanner::string() {
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n')
            line++;
        advance();
    }

    if (is_at_end()) {
        Lox::error(line, "Unterminated string.");
        return;
    }

    // The closing ".
    advance();

    // Trim the surrounding quotes.
    std::string value = source.substr(start + 1, current - 1);
    add_token(STRING, value);
}

void Scanner::number() {
    while (is_digit(peek()))
        advance();

    // Look for a fractional part.
    if (peek() == '.' && is_digit(peek_next())) {
        // Consume the "."
        advance();

        while (is_digit(peek()))
            advance();
    }

    add_token(NUMBER, source.substr(start, current - start));
}

void Scanner::identifier() {
    while (is_alphanumeric(peek()))
        advance();

    std::string text = source.substr(start, current - start);
    TokenType type = keywords.count(text) ? keywords.at(text) : IDENTIFIER;
    add_token(type);
}

char Scanner::peek() {
    if (is_at_end())
        return '\0';
    return source[current];
}

char Scanner::peek_next() {
    if (current + 1 >= source.length())
        return '\0';
    return source[current + 1];
}

bool Scanner::match(char expected) {
    if (is_at_end())
        return false;
    if (source[current] != expected)
        return false;

    current++;
    return true;
}

char Scanner::advance() { return source[current++]; }

bool Scanner::is_at_end() { return current >= source.length(); }

void Scanner::add_token(TokenType type) { add_token(type, ""); }

void Scanner::add_token(TokenType type, std::string literal) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}
