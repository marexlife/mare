module;

#include <format>
#include <optional>
#include <string>
#include <utility>

import token_kind;

export module token;

namespace mare::lex {
export struct Token {
    explicit Token(TokenKind token_kind) : token_kind(token_kind) {}

    Token(std::string lexeme, TokenKind token_kind)
        : lexeme(std::move(lexeme)), token_kind(token_kind) {}

    [[nodiscard]] std::string to_string() const {
        auto token_kind_str = token_kind_to_str(token_kind);

        if (not lexeme) {
            return std::string(token_kind_str);
        }

        return std::format("{} with '{}'", token_kind_str, *lexeme);
    }

    std::optional<std::string> lexeme;
    TokenKind token_kind{};
};

}  // namespace mare::lex
