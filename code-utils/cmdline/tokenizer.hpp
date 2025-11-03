#pragma once

#include "command.hpp"

#include <string>

namespace g_utils {
    namespace cmdline {
        struct Tokenizer {
            void tokenize(const std::string &p_text, CommandArgs &p_args, char p_delimiter = ' ') {
                this->operator()(p_text, p_args, p_delimiter);
            }

            void operator()(const std::string &p_text, CommandArgs &p_args, char delimiter = ' ') {
                std::size_t break_pos {p_text.find(delimiter, 0)};
                std::size_t last_pos {0};
                std::size_t text_length {p_text.size()};
                
                p_args.clear();
                
                while (break_pos != std::string::npos) {
                    p_args.emplace_back(p_text.substr(last_pos, break_pos - last_pos));
                    last_pos = break_pos + 1;
                    break_pos = p_text.find(delimiter, last_pos);
                }
                if (last_pos < text_length) {
                    p_args.emplace_back(p_text.substr(last_pos));
                }
            }
        };
    }
}