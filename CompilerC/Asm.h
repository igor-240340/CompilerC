#pragma once

#include <string>
#include <format>

#include "Parser.h"

// Produces MASM compatible Assembly source code.
class Asm {
public:
	struct Emitter { virtual std::string emit() const = 0; };
	struct Operand : Emitter {};
	struct ImmConst : Operand {
		explicit ImmConst(std::string value) : value(value) {}
		std::string emit() const override { return value; }
		std::string value;
	};
	struct Register : Operand {
		std::string emit() const override { return "eax"; }
	};

	struct Instruction : Emitter {};
	struct Mov : Instruction {
		explicit Mov(std::unique_ptr<Operand>&& src, std::unique_ptr<Operand>&& dst)
			: src(std::move(src)), dst(std::move(dst)) {
		}

		std::string emit() const override {
			return std::format("mov {}, {}", dst->emit(), src->emit());
		}

		std::unique_ptr<Operand> src;
		std::unique_ptr<Operand> dst;
	};
	struct Ret : Instruction {
		std::string emit() const override { return "ret"; }
	};

	struct Function : Emitter {
		explicit Function(std::string name, std::vector<std::unique_ptr<Instruction>>&& instructions)
			: name(name), instructions(std::move(instructions)) {
		}

		std::string emit() const override {
			std::string proc_label = name;
			std::string res = std::format("{}\tPROC\n", proc_label);
			for (const auto& inst : instructions) {
				res += std::format("\t{}\n", inst->emit());
			}
			res += std::format("{}\tENDP\n", proc_label);
			return res;
		}

		std::string name;
		std::vector<std::unique_ptr<Instruction>> instructions;
	};

	// It expects C function 'main' and converts it into Assembly function 'main' as a root.
	// Then produces Assembly source code.
	static std::string generate(const Parser::Function& c_ast_root) {
		Asm::Function asm_ast_root{ c_ast_root.name, convert_statement(*(c_ast_root.body)) };

		std::string res = "\t.code\n\n";
		res += asm_ast_root.emit();
		res += "\n\tEND\n";
		return res;
	}

private:
	static std::vector<std::unique_ptr<Instruction>> convert_statement(const Parser::Stmt& stmt) {
		// For now we absolutely sure that it's a return statement.
		const Parser::Return& return_stmt = static_cast<const Parser::Return&>(stmt);

		std::unique_ptr<Operand> return_value = convert_expr(*return_stmt.value);
		std::unique_ptr<Operand> reg = std::make_unique<Register>();

		std::vector<std::unique_ptr<Instruction>> instructions;
		instructions.emplace_back(std::make_unique<Mov>(std::move(return_value), std::move(reg)));
		instructions.emplace_back(std::make_unique<Ret>());

		return instructions;
	}

	static std::unique_ptr<ImmConst> convert_expr(const Parser::Expr& expr) {
		// For now we absolutely sure that it's an integer literal.
		const Parser::IntLiteral& int_literal = static_cast<const Parser::IntLiteral&>(expr);

		return std::make_unique<ImmConst>(int_literal.value);
	}
};
