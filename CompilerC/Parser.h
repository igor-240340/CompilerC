#pragma once
#include <list>
#include <format>

#include "LexicalAnalyzer.h"

class Parser {
public:
    static void parse(std::list<LexicalAnalyzer::Token>& tokens) {
        parse_program(tokens);
    }

private:
    static void parse_program(std::list<LexicalAnalyzer::Token>& tokens) {
        parse_function_definition(tokens);
    }

    static void parse_function_definition(std::list<LexicalAnalyzer::Token>& tokens) {
        expect(tokens, LexicalAnalyzer::TokenType::int_keyword);
    }

    static bool expect(std::list<LexicalAnalyzer::Token>& tokens, LexicalAnalyzer::TokenType token_type) {
        LexicalAnalyzer::Token& next_token = tokens.front();
        if (next_token.type != token_type)
            throw std::runtime_error(std::format("parser: unexpected token \"{}\".", next_token.value));

        tokens.pop_front();
    }
};
