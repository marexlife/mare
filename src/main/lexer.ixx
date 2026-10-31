module;

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

import token_kind;
import token;

export module lexer;

namespace mare::lex {
export class Lexer {
   public:
    explicit Lexer(std::string source_code)
        : source_code_(std::move(source_code)) {}

    [[nodiscard]] std::vector<Token> lex() {
        if (auto current = advance()) {
            lex_iter(*current);
        }

        flush();

        return tokens_;
    }

   private:
    [[nodiscard]] Token translate() {
        if (token_mapping_.contains(current_word_)) {
            return token_mapping_.at(current_word_);
        }

        return Token{std::string(current_word_),
                     TokenKind::Identifier};
    }

    void lex_iter(char current) {
        if (auto token = get_special_token(current)) {
            flush();
            tokens_.emplace_back(*token);

            return;
        }

        switch (current) {
            case ' ':
                flush();
                break;
            default:
                current_word_.push_back(current);
                break;
        }
    }

    void flush() {
        tokens_.emplace_back(translate());
        current_word_.clear();
    }

    [[nodiscard]] std::optional<Token> get_special_token(
        char current) {
        if (current == '=' and peak() == '=') {
            return std::optional(Token{TokenKind::Assignment});
        }

        return std::nullopt;
    }

    [[nodiscard]] std::optional<char> advance() {
        if (source_code_.length() >= index_) [[unlikely]] {
            return std::nullopt;
        }

        return source_code_.at(std::exchange(index_, index_ + 1));
    }

    [[nodiscard]] std::optional<char> peak() const {
        if (source_code_.length() >= index_) [[unlikely]] {
            return std::nullopt;
        }

        return source_code_.at(index_ + 1);
    }

    std::unordered_map<std::string_view, Token> token_mapping_;
    std::vector<Token> tokens_;
    std::string current_word_;
    std::string source_code_;
    std::size_t index_ = 0;
};
}  // namespace mare::lex
