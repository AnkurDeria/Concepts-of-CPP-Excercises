#include "validator.h"

#include <iostream>

namespace sql
{
	struct CheckIsValid {
		
		bool operator()(state::Valid) const { return true; }
	};

	bool SqlValidator::is_valid() const {
		/// TODO: Implement this
		return std::holds_alternative<state::Valid>(state_);
	}

	bool is_valid_sql_query(std::vector<Token> tokens)
	{
		SqlValidator sql_validator;
		for (const auto& token : tokens)
		{
			sql_validator.handle(token);
		}
		return sql_validator.is_valid();
	}

	struct HandleDifferentTransitions {
		Token& token_;

		HandleDifferentTransitions(Token& token) : token_(token) { }
		State operator()(state::Start) const { return transition(state::Start{},token_); }
		State operator()(state::Invalid) const { return transition(state::Invalid{}, token_); }
		State operator()(state::Valid) const { return transition(state::Valid{}, token_); }
		State operator()(state::SelectStmt) const { return transition(state::SelectStmt{}, token_); }
		State operator()(state::FromClause) const { return transition(state::FromClause{}, token_); }
		State operator()(state::NamedColumn) const { return transition(state::NamedColumn{}, token_); }
		State operator()(state::AllColumns) const { return transition(state::AllColumns{}, token_); }
		State operator()(state::MoreColumns) const { return transition(state::MoreColumns{}, token_); }
		State operator()(state::TableName) const { return transition(state::TableName{}, token_); }
	};
	void SqlValidator::handle(Token token) {
		
		/// TODO: Implement this
		state_ = std::visit(HandleDifferentTransitions(token), state_);
	}

	struct TransitionFromStartVisitor {
		/// Only the `Select` token advances the FSM from the `Start` state
		/// TODO: Correct the behaviour
		State operator()(token::Select) const { return state::SelectStmt{}; }

		/// All the other tokens, put it in the invalid state
		State operator()(token::From) const { return state::Invalid{}; }
		State operator()(token::Comma) const { return state::Invalid{}; }
		State operator()(token::Asterisks) const { return state::Invalid{}; }
		State operator()(token::Semicolon) const { return state::Invalid{}; }
		State operator()(token::Identifier) const { return state::Invalid{}; }
	};

	State transition(state::Start, Token token) {
		return std::visit(TransitionFromStartVisitor{}, token.value());
	}
	struct TransitionFromValid {
		/// Only the `Select` token advances the FSM from the `Start` state
		/// TODO: Correct the behaviour
		State operator()(token::Select) const { return state::Invalid{}; }

		/// All the other tokens, put it in the invalid state
		State operator()(token::From) const { return state::Invalid{}; }
		State operator()(token::Comma) const { return state::Invalid{}; }
		State operator()(token::Asterisks) const { return state::Invalid{}; }
		State operator()(token::Semicolon) const { return state::Valid{}; }
		State operator()(token::Identifier) const { return state::Invalid{}; }
	};
	State transition(state::Valid, Token token)
	{
		// TODO: Implement
		return std::visit(TransitionFromValid{}, token.value());
	}

	State transition(state::Invalid, Token token) {
		// TODO: Implement
		return state::Invalid{};
	}
	struct TransitionFromSelectStmt {
		/// Only the `Select` token advances the FSM from the `Start` state
		/// TODO: Correct the behaviour
		State operator()(token::Select) const { return state::Invalid{}; }

		/// All the other tokens, put it in the invalid state
		State operator()(token::From) const { return state::Invalid{}; }
		State operator()(token::Comma) const { return state::Invalid{}; }
		State operator()(token::Asterisks) const { return state::AllColumns{}; }
		State operator()(token::Semicolon) const { return state::Invalid{}; }
		State operator()(token::Identifier) const { return state::NamedColumn{}; }
	};
	State transition(state::SelectStmt, Token token) {
		// TODO: Implement
		return std::visit(TransitionFromSelectStmt{}, token.value());
	}
	struct TransitionFromAllColumns {
		/// Only the `Select` token advances the FSM from the `Start` state
		/// TODO: Correct the behaviour
		State operator()(token::Select) const { return state::Invalid{}; }

		/// All the other tokens, put it in the invalid state
		State operator()(token::From) const { return state::FromClause{}; }
		State operator()(token::Comma) const { return state::Invalid{}; }
		State operator()(token::Asterisks) const { return state::Invalid{}; }
		State operator()(token::Semicolon) const { return state::Invalid{}; }
		State operator()(token::Identifier) const { return state::Invalid{}; }
	};
	State transition(state::AllColumns, Token token) {
		// TODO: Implement
		return std::visit(TransitionFromAllColumns{}, token.value());
	}
	struct TransitionFromFromClause {
		/// Only the `Select` token advances the FSM from the `Start` state
		/// TODO: Correct the behaviour
		State operator()(token::Select) const { return state::Invalid{}; }

		/// All the other tokens, put it in the invalid state
		State operator()(token::From) const { return state::Invalid{}; }
		State operator()(token::Comma) const { return state::Invalid{}; }
		State operator()(token::Asterisks) const { return state::Invalid{}; }
		State operator()(token::Semicolon) const { return state::Invalid{}; }
		State operator()(token::Identifier) const { return state::TableName{}; }
	};
	State transition(state::FromClause, Token token) {
		// TODO: Implement
		return std::visit(TransitionFromFromClause{}, token.value());
	}
	struct TransitionFromNamedColumn {
		/// Only the `Select` token advances the FSM from the `Start` state
		/// TODO: Correct the behaviour
		State operator()(token::Select) const { return state::Invalid{}; }

		/// All the other tokens, put it in the invalid state
		State operator()(token::From) const { return state::FromClause{}; }
		State operator()(token::Comma) const { return state::MoreColumns{}; }
		State operator()(token::Asterisks) const { return state::Invalid{}; }
		State operator()(token::Semicolon) const { return state::Invalid{}; }
		State operator()(token::Identifier) const { return state::Invalid{}; }
	};
	State transition(state::NamedColumn, Token token) {
		// TODO: Implement
		return std::visit(TransitionFromNamedColumn{}, token.value());
	}
	struct TransitionFromMoreColumns {
		/// Only the `Select` token advances the FSM from the `Start` state
		/// TODO: Correct the behaviour
		State operator()(token::Select) const { return state::Invalid{}; }

		/// All the other tokens, put it in the invalid state
		State operator()(token::From) const { return state::Invalid{}; }
		State operator()(token::Comma) const { return state::Invalid{}; }
		State operator()(token::Asterisks) const { return state::Invalid{}; }
		State operator()(token::Semicolon) const { return state::Invalid{}; }
		State operator()(token::Identifier) const { return state::NamedColumn{}; }
	};
	State transition(state::MoreColumns, Token token) {
		// TODO: Implement
		return std::visit(TransitionFromMoreColumns{}, token.value());
	}
	struct TransitionFromTableName {
		/// Only the `Select` token advances the FSM from the `Start` state
		/// TODO: Correct the behaviour
		State operator()(token::Select) const { return state::Invalid{}; }

		/// All the other tokens, put it in the invalid state
		State operator()(token::From) const { return state::Invalid{}; }
		State operator()(token::Comma) const { return state::Invalid{}; }
		State operator()(token::Asterisks) const { return state::Invalid{}; }
		State operator()(token::Semicolon) const { return state::Valid{}; }
		State operator()(token::Identifier) const { return state::Invalid{}; }
	};
	State transition(state::TableName, Token token) {
		// TODO: Implement
		return std::visit(TransitionFromTableName{}, token.value());
	}

}
// namespace sql
