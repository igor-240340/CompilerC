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
        std::string func_name = parse_id(tokens);
        expect(tokens, LexicalAnalyzer::TokenType::left_paren);
        expect(tokens, LexicalAnalyzer::TokenType::void_keyword);
        expect(tokens, LexicalAnalyzer::TokenType::right_paren);
        expect(tokens, LexicalAnalyzer::TokenType::left_brace);
        std::string int_literal = parse_statement(tokens);
        expect(tokens, LexicalAnalyzer::TokenType::right_brace);
    }

    static bool expect(std::list<LexicalAnalyzer::Token>& tokens, LexicalAnalyzer::TokenType token_type) {
        LexicalAnalyzer::Token& next_token = tokens.front();
        if (next_token.type != token_type)
            throw std::runtime_error(std::format("parser: unexpected token \"{}\".", next_token.value));

        tokens.pop_front();
    }

    static std::string parse_id(std::list<LexicalAnalyzer::Token>& tokens) {
        LexicalAnalyzer::Token next_token = tokens.front();
        if (next_token.type != LexicalAnalyzer::TokenType::identifier)
            throw std::runtime_error(std::format("parser: unexpected token \"{}\".", next_token.value));

        tokens.pop_front();

        return next_token.value;
    }

    static std::string parse_statement(std::list<LexicalAnalyzer::Token>& tokens) {
        expect(tokens, LexicalAnalyzer::TokenType::return_keyword);
        std::string int_literal = parse_expression(tokens);
        expect(tokens, LexicalAnalyzer::TokenType::semicolon);
        return int_literal;
    }

    static std::string parse_expression(std::list<LexicalAnalyzer::Token>& tokens) {
        return parse_int(tokens);
    }

    static std::string parse_int(std::list<LexicalAnalyzer::Token>& tokens) {
        LexicalAnalyzer::Token next_token = tokens.front();
        if (next_token.type != LexicalAnalyzer::TokenType::int_literal)
            throw std::runtime_error(std::format("parser: unexpected token \"{}\".", next_token.value));

        tokens.pop_front();

        return next_token.value;
    }
};