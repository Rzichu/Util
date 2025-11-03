#pragma once

#include "command.hpp"

#include <stdexcept>
#include <unordered_map>
#include <string>
#include <sstream>

namespace g_utils {
    namespace cmdline {
        enum class CommandResult {
            Success = 0
            , InvalidCommand
            , InvalidArgs
            , MissingArgs
            , CommandsDisabled
        };

        // BASE CLASS
        class CommandLine {
        public:
            virtual std::stringstream cmd_Help(const std::string& p_cmd = std::string()) {
                std::stringstream buffer;

                if (p_cmd.empty()) {
                    for (auto &cmd : this->m_Commands) {
                        if (!cmd.second.is_hidden) {
                            buffer << cmd.first << "\t" << cmd.second.description << "\n";
                        }
                    }
                }
                else if (this->m_Commands.count(p_cmd)) {
                    buffer << p_cmd << "\t" << this->m_Commands.at(p_cmd).description << "\n\t" << this->m_Commands.at(p_cmd).details << "\n";
                }
                else {
                    buffer << "This command does not exist: " << p_cmd << "\n";
                }

                return buffer;
            }
        
        public:
            virtual bool addCommand(const std::string &p_cmd_name, const Command &p_cmd) {
                if (p_cmd.action != nullptr) {
                    if (this->m_Commands.count(p_cmd_name)) {
                        return false;
                    }
                    this->m_Commands.emplace(p_cmd_name, p_cmd);
                    return true;
                }
                return false;
            }

            virtual void removeCommand(const std::string &p_cmd_name) {
                this->m_Commands.erase(p_cmd_name);
            }

            virtual CommandResult invoke(const std::string &p_name, const CommandArgs &p_args) {
                if (this->m_Enabled) {
            
                    if (!this->m_Commands.count(p_name)) {
                        return CommandResult::InvalidCommand;
                    }
                    if (p_args.size() < this->m_Commands.at(p_name).required_args) {
                        return CommandResult::MissingArgs;
                    }
                    try {
                        this->m_Commands.at(p_name).action(p_args);
                    }
                    catch (...) {
                        return CommandResult::InvalidArgs;
                    }
                    return CommandResult::Success;
                }
                
                return CommandResult::CommandsDisabled;
            }

            inline virtual const std::unordered_map<std::string, Command> & getCommands() const {
                return this->m_Commands;
            }

            inline virtual std::unordered_map<std::string, Command> & getCommands() {
                return this->m_Commands;
            }

            inline virtual void enable(bool p_state) {
                this->m_Enabled = p_state;
            }

            inline virtual bool isEnabled() const {
                return this->m_Enabled;
            }

        public:
            virtual ~CommandLine()  = default;

        protected:
            std::unordered_map<std::string, Command> m_Commands;
            bool m_Enabled {false};
        };
    }
}