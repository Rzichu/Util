#pragma once

#include <string>
#include <vector>
#include <functional>

namespace g_utils {
    namespace cmdline {
        typedef std::vector<std::string> CommandArgs;
        typedef std::function<void(const CommandArgs &)> CommandHandle;

        struct Command {
            CommandHandle action {nullptr};
            std::size_t required_args {0};
            std::string description {"No description available"};
            std::string details {"No details available"};
            bool is_hidden {false};

            Command(CommandHandle p_action, std::size_t p_required_args = 0
                    , const std::string &p_description = "No description available"
                    , const std::string &p_details = "No details available"
                    , bool p_is_hidden = false)
                : action{p_action}
                , required_args{p_required_args}
                , description{p_description}
                , details{p_details}
                , is_hidden{p_is_hidden}
                {}
        };
    }
}