#pragma once

#include <cassert>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

enum class TokenType {
    exit,
    int_lit,
    semi,
    open_paren,
    close_paren,
    ident,
    let,
    eq,
    plus,
    star,
    minus,
    fslash,
    open_curly,
    close_curly,
    if_,
    elif_,
    else_,
    while_,
    gt,
    lt,
    gt_eq,
    lt_eq,
    equal_comp,
    diff_comp,
    true_,
    false_
};

inline std::string to_string(const TokenType type)
{
    switch (type) {
    case TokenType::exit:
        return "`exit`";
    case TokenType::int_lit:
        return "int literal";
    case TokenType::semi:
        return "`;`";
    case TokenType::open_paren:
        return "`(`";
    case TokenType::close_paren:
        return "`)`";
    case TokenType::ident:
        return "identifier";
    case TokenType::let:
        return "`let`";
    case TokenType::eq:
        return "`=`";
    case TokenType::plus:
        return "`+`";
    case TokenType::star:
        return "`*`";
    case TokenType::minus:
        return "`-`";
    case TokenType::fslash:
        return "`/`";
    case TokenType::open_curly:
        return "`{`";
    case TokenType::close_curly:
        return "`}`";
    case TokenType::if_:
        return "`if`";
    case TokenType::elif_:
        return "`elif`";
    case TokenType::else_:
        return "`else`";
    case TokenType::while_:
        return "`while`";
    case TokenType::gt:
        return "`>`";
    case TokenType::lt:
        return "`<`";
    case TokenType::gt_eq:
        return "`>=`";
    case TokenType::lt_eq:
        return "`<=`";
    case TokenType::equal_comp:
        return "`==`";
    case TokenType::diff_comp:
        return "`!=`";
    case TokenType::true_:
        return "`true`";
    case TokenType::false_:
        return "`false`";
    }
    assert(false);
}

inline std::optional<int> bin_prec(const TokenType type)
{
    switch (type) {
    case TokenType::minus:
    case TokenType::plus:
        return 0;
    case TokenType::fslash:
    case TokenType::star:
        return 1;
    default:
        return {};
    }
}

struct Token {
    TokenType type;
    int line;
    std::optional<std::string> value {};
};

class Tokenizer {
public:
    explicit Tokenizer(std::string src)
        : m_src(std::move(src))
    {
    }

    std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;
        std::string buf;
        int line_count = 1;
        while (peek().has_value()) {
            if (std::isalpha(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buf.push_back(consume());
                }
                if (buf == "exit") {
                    tokens.push_back({ TokenType::exit, line_count });
                    buf.clear();
                }
                else if (buf == "let") {
                    tokens.push_back({ TokenType::let, line_count });
                    buf.clear();
                }
                else if (buf == "if") {
                    tokens.push_back({ TokenType::if_, line_count });
                    buf.clear();
                }
                else if (buf == "elif") {
                    tokens.push_back({ TokenType::elif_, line_count });
                    buf.clear();
                }
                else if (buf == "else") {
                    tokens.push_back({ TokenType::else_, line_count });
                    buf.clear();
                }
                else if (buf == "while") {
                    tokens.push_back({ TokenType::while_, line_count });
                    buf.clear();
                }
                else if (buf == "true") {
                    tokens.push_back({ TokenType::true_, line_count });
                    buf.clear();
                }
                else if (buf == "false") {
                    tokens.push_back({ TokenType::false_, line_count });
                    buf.clear();
                }
                else {
                    tokens.push_back({ TokenType::ident, line_count, buf });
                    buf.clear();
                }
            }
            else if (std::isdigit(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isdigit(peek().value())) {
                    buf.push_back(consume());
                }
                tokens.push_back({ TokenType::int_lit, line_count, buf });
                buf.clear();
            }
            else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '/') {
                consume();
                consume();
                while (peek().has_value() && peek().value() != '\n') {
                    consume();
                }
            }
            else if (peek().value() == '/' && peek(1).has_value() && peek(1).value() == '*') {
                consume();
                consume();
                while (peek().has_value()) {
                    if (peek().value() == '*' && peek(1).has_value() && peek(1).value() == '/') {
                        break;
                    }
                    consume();
                }
                if (peek().has_value()) {
                    consume();
                }
                if (peek().has_value()) {
                    consume();
                }
            }
            else if (peek().value() == '(') {
                consume();
                tokens.push_back({ TokenType::open_paren, line_count });
            }
            else if (peek().value() == ')') {
                consume();
                tokens.push_back({ TokenType::close_paren, line_count });
            }
            else if (peek().value() == ';') {
                consume();
                tokens.push_back({ TokenType::semi, line_count });
            }
            else if (peek().value() == '=' && peek(1).has_value() && peek(1).value() != '=') {
                consume();
                tokens.push_back({ TokenType::eq, line_count });
            }
            else if (peek().value() == '+') {
                consume();
                tokens.push_back({ TokenType::plus, line_count });
            }
            else if (peek().value() == '*') {
                consume();
                tokens.push_back({ TokenType::star, line_count });
            }
            else if (peek().value() == '-') {
                consume();
                tokens.push_back({ TokenType::minus, line_count });
            }
            else if (peek().value() == '/') {
                consume();
                tokens.push_back({ TokenType::fslash, line_count });
            }
            else if (peek().value() == '>' && peek(1).has_value() && peek(1).value() != '=') {
                consume();
                tokens.push_back({ TokenType::gt, line_count });
            }
            else if (peek().value() == '<' && peek(1).has_value() && peek(1).value() != '=') {
                consume();
                tokens.push_back({ TokenType::lt, line_count });
            }
            else if (peek().value() == '>' && peek(1).has_value() && peek(1).value() == '=') {
                consume();
                consume();
                tokens.push_back({ TokenType::gt_eq, line_count });
            }
            else if (peek().value() == '<' && peek(1).has_value() && peek(1).value() == '=') {
                consume();
                consume();
                tokens.push_back({ TokenType::lt_eq, line_count });
            }
            else if (peek().value() == '=' && peek(1).has_value() && peek(1).value() == '=') {
                consume();
                consume();
                tokens.push_back({ TokenType::equal_comp, line_count });
            }
            else if (peek().value() == '!' && peek(1).has_value() && peek(1).value() == '=') {
                consume();
                consume();
                tokens.push_back({ TokenType::diff_comp, line_count });
            }
            else if (peek().value() == '{') {
                consume();
                tokens.push_back({ TokenType::open_curly, line_count });
            }
            else if (peek().value() == '}') {
                consume();
                tokens.push_back({ TokenType::close_curly, line_count });
            }
            else if (peek().value() == '\n') {
                consume();
                line_count++;
            }
            else if (std::isspace(peek().value())) {
                consume();
            }
            else {
                std::cerr << "Invalid token" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        m_index = 0;
        return tokens;
    }

private:
    [[nodiscard]] std::optional<char> peek(const size_t offset = 0) const
    {
        if (m_index + offset >= m_src.length()) {
            return {};
        }
        return m_src.at(m_index + offset);
    }

    char consume()
    {
        return m_src.at(m_index++);
    }

    const std::string m_src;
    size_t m_index = 0;
};
