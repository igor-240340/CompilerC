#pragma once

#include <string>
#include <list>
#include <regex>
#include <unordered_map>

class LexicalAnalyzer {
public:
    enum class TokenType {
        int_keyword,
        return_keyword,
        identifier,
        left_paren,
        right_paren,
        left_brace,
        right_brace,
        assign,
        plus,
        minus,
        int_literal,
        semicolon
    };
    struct Token {
        TokenType type;
        std::string value;
    };
    static std::list<Token> tokenize(std::string& source_code) {
        const std::unordered_map<std::string, TokenType> keywords = {
            {"int", TokenType::int_keyword},
            {"return", TokenType::return_keyword}
        };
        std::regex identifier_regex("^[a-zA-Z_]\\w*\\b");
        std::regex left_paren_regex("^\\(");
        std::regex right_paren_regex("^\\)");
        std::regex left_brace_regex("^\\{");
        std::regex right_brace_regex("^\\}");
        std::regex assign_regex("^="); // NOTE: If you implement a complete compiler you should match the longest regex ^== for equality operator first.
        std::regex plus_regex("^\\+");
        std::regex minus_regex("^\\-");
        std::regex int_literal_regex("^[0-9]+");
        std::regex semicolon_regex("^\\;");

        std::list<Token> tokens;

        std::smatch matches;
        std::regex matched_regex;
        while (!source_code.empty()) {
            source_code.erase(0, source_code.find_first_not_of(' '));

            if (std::regex_search(source_code, matches, identifier_regex)) {
                std::string value = matches[0];
                if (auto item = keywords.find(value); item != keywords.end())
                    tokens.push_back(Token{ item->second, value });
                // This is a user-defined identifier.
                else
                    tokens.push_back(Token{ TokenType::identifier, value });
                matched_regex = identifier_regex;
            }
            else if (std::regex_search(source_code, matches, left_paren_regex)) {
                tokens.push_back(Token{ TokenType::left_paren, matches[0] });
                matched_regex = left_paren_regex;
            }
            else if (std::regex_search(source_code, matches, right_paren_regex)) {
                tokens.push_back(Token{ TokenType::right_paren, matches[0] });
                matched_regex = right_paren_regex;
            }
            else if (std::regex_search(source_code, matches, left_brace_regex)) {
                tokens.push_back(Token{ TokenType::left_brace, matches[0] });
                matched_regex = left_brace_regex;
            }
            else if (std::regex_search(source_code, matches, right_brace_regex)) {
                tokens.push_back(Token{ TokenType::right_brace, matches[0] });
                matched_regex = right_brace_regex;
            }
            else if (std::regex_search(source_code, matches, assign_regex)) {
                tokens.push_back(Token{ TokenType::assign, matches[0] });
                matched_regex = assign_regex;
            }
            else if (std::regex_search(source_code, matches, plus_regex)) {
                tokens.push_back(Token{ TokenType::plus, matches[0] });
                matched_regex = plus_regex;
            }
            else if (std::regex_search(source_code, matches, minus_regex)) {
                tokens.push_back(Token{ TokenType::minus, matches[0] });
                matched_regex = minus_regex;
            }
            else if (std::regex_search(source_code, matches, int_literal_regex)) {
                tokens.push_back(Token{ TokenType::int_literal, matches[0] });
                matched_regex = int_literal_regex;
            }
            else if (std::regex_search(source_code, matches, semicolon_regex)) {
                tokens.push_back(Token{ TokenType::semicolon, matches[0] });
                matched_regex = semicolon_regex;
            }
            source_code = std::regex_replace(source_code, matched_regex, "", std::regex_constants::format_first_only);
        }

        return tokens;
    }
};
