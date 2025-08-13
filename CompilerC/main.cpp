#include <string>
#include <list>
#include <iostream>
#include <format>

#include "LexicalAnalyzer.h"
#include "Parser.h"

int main() {
    try {
        std::string c_program =
            "int main() {"
            "    int a = 2;"
            "    int b = 5;"
            "    int c = a + b;"
            "    return c;"
            "}";

        std::list<LexicalAnalyzer::Token> tokens = LexicalAnalyzer::tokenize(c_program);
        for (const LexicalAnalyzer::Token& token : tokens)
            std::cout << token.value << ' ';

        std::cout << '\n';

        Parser::parse(tokens);

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
