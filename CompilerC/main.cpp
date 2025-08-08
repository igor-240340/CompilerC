#include <string>
#include <vector>
#include <iostream>
#include <format>

#include "LexicalAnalyzer.h"

int main() {
    std::string c_program =
        "int main() {"
        "    int a = 2;"
        "    int b = 5;"
        "    int c = a + b;"
        "    return c;"
        "}";

    LexicalAnalyzer lexer{ c_program };
    std::vector<LexicalAnalyzer::Token> tokens = lexer.tokenize();
    for (const LexicalAnalyzer::Token& token : tokens)
        std::cout << token.value << ' ';

    return 0;
}
