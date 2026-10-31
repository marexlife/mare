module;

#include <cstdint>
#include <string_view>
#include <utility>

export module token_kind;

namespace mare::lex {
export enum class TokenKind : std::uint8_t {
    Identifier,
    Assignment,
};

export [[nodiscard]] std::string_view token_kind_to_str(
    TokenKind token_kind) {
    switch (token_kind) {
        case TokenKind::Assignment:
            return "Assignment";
        case TokenKind::Identifier:
            return "Identifier";
    }

    std::unreachable();
}
}  // namespace mare::lex