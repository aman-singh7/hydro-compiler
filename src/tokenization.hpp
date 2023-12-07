#pragma once

#include <string>
#include <vector>
#include <optional>

enum class TokenType
{
    exit,
    int_lit,
    semi
};

struct Token
{
    TokenType type;
    std::optional<std::string> value;
};

class Tokenizer
{
public:
    inline explicit Tokenizer(const std::string &src) : m_src(src)
    {
    }

    inline std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;
        std::string buf{};

        while (peek().has_value())
        {
            if (std::isalpha(peek().value()))
            {
                buf.push_back(consume());
                while (peek().has_value() and std::isalnum(peek().value()))
                {
                    buf.push_back(consume());
                }

                if (buf == "exit")
                {
                    tokens.push_back({.type = TokenType::exit});
                    buf.clear();
                }
                else
                {
                    std::cerr << "You messed up!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if (std::isdigit(peek().value()))
            {
                buf.push_back(consume());
                while (peek().has_value() and std::isdigit(peek().value()))
                {
                    buf.push_back(consume());
                }
                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf.clear();
            }
            else if (peek().value() == ';')
            {
                consume();
                tokens.push_back({.type = TokenType::semi});
            }
            else if (std::isspace(peek().value()))
            {
                consume();
            }
            else
            {
                std::cerr << "You messed up!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        // reset the index
        m_index = 0;

        return tokens;
    }

private:
    [[nodiscard]] inline std::optional<char> peek(int ahead = 1) const
    {
        if (m_index + ahead > m_src.length())
        {
            return {};
        }

        return m_src.at(m_index);
    }

    inline char consume()
    {
        return m_src.at(m_index++);
    }

    const std::string m_src;
    int m_index = 0;
};