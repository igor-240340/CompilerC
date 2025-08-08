## Compiler C

Very stupid custom C compiler for fun written in C++.

There are no plans to write a fully functional C compiler.
This project is solely for developing a deeper understanding of how everyday high-level programming works under the hood.

## How it works
For now can compile just a simple main function with 3 int variables and one arithmetic operation.

1. Tokenizes source code with regexps.
2. Top-down parser builds an AST.
3. Code generator moves through an AST and generates assembly code compatible with MASM.

To build exe from output assembly file run `x64 Native Tools Command Prompt` (it should be available if you've installed MSVC) and start `build.bat`.