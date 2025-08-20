#pragma once
#include <list>
#include <format>

#include "LexicalAnalyzer.h"

class Parser {
public:
    struct Expr {};
    struct IntLiteral : Expr {
        explicit IntLiteral(std::string value) : value(value) {}
        std::string value;
    };

    struct Stmt {};
    struct Return : Stmt {
        explicit Return(std::unique_ptr<Expr> value) : value(std::move(value)) {}
        std::unique_ptr<Expr> value;
    };
    struct Function : Stmt {
        explicit Function(const std::string& name, std::unique_ptr<Stmt> body) : name(name), body(std::move(body)) {}
        std::string name;
        std::unique_ptr<Stmt> body;
    };

public:
    static std::unique_ptr<Stmt> parse(std::list<LexicalAnalyzer::Token>& tokens) {
        return parse_program(tokens);
    }

private:
    static std::unique_ptr<Stmt> parse_program(std::list<LexicalAnalyzer::Token>& tokens) {
        return parse_function_definition(tokens);
    }

    static std::unique_ptr<Function> parse_function_definition(std::list<LexicalAnalyzer::Token>& tokens) {
        expect(tokens, LexicalAnalyzer::TokenType::int_keyword);
        std::string func_name = parse_id(tokens);
        expect(tokens, LexicalAnalyzer::TokenType::left_paren);
        expect(tokens, LexicalAnalyzer::TokenType::void_keyword);
        expect(tokens, LexicalAnalyzer::TokenType::right_paren);
        expect(tokens, LexicalAnalyzer::TokenType::left_brace);
        std::unique_ptr<Stmt> body = parse_statement(tokens);
        expect(tokens, LexicalAnalyzer::TokenType::right_brace);
        return std::make_unique<Function>(func_name, std::move(body));
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

    static std::unique_ptr<Stmt> parse_statement(std::list<LexicalAnalyzer::Token>& tokens) {
        expect(tokens, LexicalAnalyzer::TokenType::return_keyword);
        std::unique_ptr<Expr> int_literal = parse_expression(tokens);
        expect(tokens, LexicalAnalyzer::TokenType::semicolon);
        return std::make_unique<Return>(std::move(int_literal));
    }

    static std::unique_ptr<Expr> parse_expression(std::list<LexicalAnalyzer::Token>& tokens) {
        return std::make_unique<IntLiteral>(parse_int(tokens));
    }

    static std::string parse_int(std::list<LexicalAnalyzer::Token>& tokens) {
        LexicalAnalyzer::Token next_token = tokens.front();
        if (next_token.type != LexicalAnalyzer::TokenType::int_literal)
            throw std::runtime_error(std::format("parser: unexpected token \"{}\".", next_token.value));

        tokens.pop_front();

        return next_token.value;
    }
};