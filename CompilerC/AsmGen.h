#pragma once

#include<string>

#include "Parser.h"

// Builds an AST for Assembly representation of a C program.
class AsmGen {
public:
	struct Instruction {};
	struct Mov : Instruction {};
	struct Ret : Instruction {};

	struct Function {
		std::string name;
		std::vector<Instruction> instructions;
	};

	static std::unique_ptr<Function> generate(const Parser::Stmt& c_ast_root) {
		return std::make_unique<Function>();
	}
};
