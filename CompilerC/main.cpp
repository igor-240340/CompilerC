#include <string>
#include <list>
#include <iostream>
#include <format>

#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "AsmGen.h"

int main() {
	try {
		std::string c_program =
			"int main(void) {"
			"    return 12;"
			"}";

		std::list<LexicalAnalyzer::Token> tokens = LexicalAnalyzer::tokenize(c_program);
		for (const LexicalAnalyzer::Token& token : tokens)
			std::cout << token.value << ' ';

		std::cout << '\n';

		std::unique_ptr<Parser::Stmt> c_ast_root = Parser::parse(tokens);
		std::unique_ptr<AsmGen::Function> asm_ast_root = AsmGen::generate(*c_ast_root);

		return 0;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
