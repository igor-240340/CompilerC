#include <string>
#include <list>
#include <iostream>
#include <format>
#include <fstream>

#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "Asm.h"

int main() {
	try {
		std::string c_program =
			"int main(void) {"
			"    return 12;"
			"}";

		std::list<LexicalAnalyzer::Token> tokens = LexicalAnalyzer::tokenize(c_program);

		std::cout << "C program tokens:\n";
		for (const LexicalAnalyzer::Token& token : tokens)
			std::cout << token.value << ' ';

		std::cout << '\n';

		Parser::Function c_ast_root = Parser::parse(tokens);
		std::string asm_program = Asm::generate(c_ast_root);
		std::ofstream asm_file("output.asm");
		asm_file << asm_program;

		std::cout << "\nAssembly:\n";
		std::cout << asm_program << '\n';

		return 0;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
