#pragma once

#ifdef DEBUG

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <array>
#include <sstream>
#include <future>
#include <utility>
#include <chrono>
#include <filesystem>
#include <cstdarg>

namespace g_utils {
    namespace logging {
        enum class LogLevel {
            Debug,
            Info,
            Warning,
            Error,
            FatalError
        };

        class LogSystem {
        public:
            static LogSystem & get() {
                static LogSystem instance;

                return instance;
            }

            void log(LogLevel p_level, const std::string &p_message, const std::string &p_function_name, const std::string &p_sourcefile, int p_sourceline) {
                static std::mutex mtx;
                static LogSystem *instance = new LogSystem();

                std::lock_guard<std::mutex> lock(mtx);

                double seconds {0.0}, minutes {0.0}, hours {0.0};

                seconds = (instance->calculateTime() * 0.001);
                if (seconds > 59.0) {
                    minutes = seconds * 0.6;
                    seconds = seconds - (minutes * 60.0);
                    if (minutes > 59.0) {
                        hours = minutes * 0.6;
                        minutes = minutes - (hours * 60.0);
                    }
                }

                std::ofstream outLog(this->m_DebugFile, std::ios::app);
                if (outLog.good()) {

                    outLog << instance->m_LogLevels[static_cast<std::underlying_type<LogLevel>::type>(p_level)]
                        << " | "
                        << hours << ":" << minutes << ":" << seconds
                        << " | "<< p_sourceline
                        << " | " << p_function_name
                        << " | " << uint32_t(std::hash<std::thread::id>{}(std::this_thread::get_id()))
                        << " | "<< p_sourcefile << "\n"
                        << p_message << "\n\n";

                    outLog.close();
                }
                else {
                    std::cerr << "Could not create or open " << this->m_DebugFile << " destination file.\n";
                }
            }

            std::string construct_msg(std::stringstream &p_msg) {
                return p_msg.str();
            }

            template <typename T, typename... Args>
            std::string construct_msg(std::stringstream &p_msg, T t, Args... p_args) {
                msg << t;
                return construct_msg(p_msg, p_args...);
            }

            template <typename T, typename... Args>
            std::string construct_msg(T p_t, Args... p_args) {
                std::stringstream msg;
                msg << p_t;
                return construct_msg(msg, p_args...);
            }

        public:
            ~LogSystem() = default;
        
        protected:
            LogSystem() {
                std::time_t loadTimeT {std::time(NULL)};
                tm *time_struct {std::localtime(&loadTimeT)};
                std::stringstream date_time;

                time_struct->tm_mon += 1;
                time_struct->tm_year += 1'900;
            
                date_time << time_struct->tm_mon << "-" << time_struct->tm_mday << "-" << time_struct->tm_year
                << "_" << time_struct->tm_hour << "-" << time_struct->tm_min << "-" << time_struct->tm_sec;

                std::string logpath {"logs"};

                static bool called {false};

                if (!called) {
                    try {
                        std::filesystem::create_directory(logpath);
                    } catch (const std::filesystem::filesystem_error &e) {
                        std::cerr << "Error: " << e.what() << '\n';
                    }
                }

                this->m_DebugFile = logpath + "/log_" + date_time.str() + ".txt";

                std::ofstream outLog(this->m_DebugFile);
                if (outLog.good()) {
                    outLog.close();
                }
                else {
                    std::cerr << "Could not create or open " << this->m_DebugFile << " destination file.\n";
                }
            }

            double calculateTime() {
                auto endTimePoint = std::chrono::steady_clock::now();

                auto start = std::chrono::time_point_cast<std::chrono::microseconds>(this->m_startTimePoint).time_since_epoch().count();
                auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
            
                double duration = static_cast<double>(end - start);
                return (duration * 0.001);
            }
        
        private:
            const std::array<std::string, 5> m_LogLevels {
                "Debug",
                "Info",
                "Warning",
                "Error",
                "Fatal Error"
            };

            std::chrono::time_point<std::chrono::steady_clock> m_startTimePoint {std::chrono::steady_clock::now()};

            std::string m_DebugFile {""};
        };
    }
}
#endif

#ifdef DEBUG
#define LOG_CREATE(...)         g_utils::logging::LogSystem::get().construct_msg(__VA_ARGS__)
#define LOG(lvl, msg)           g_utils::logging::LogSystem::get().log(lvl, msg, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define LOG_LEVEL_DEBUG         g_utils::logging::LogLevel::Debug
#define LOG_LEVEL_INFO          g_utils::logging::LogLevel::Info
#define LOG_LEVEL_WARNING       g_utils::logging::LogLevel::Warning
#define LOG_LEVEL_ERROR         g_utils::logging::LogLevel::Error
#define LOG_LEVEL_FATAL_ERROR   g_utils::logging::LogLevel::FatalError
#else
#define LOG_CREATE(...)
#define LOG(lvl, msg)
#define LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR
#define LOG_LEVEL_FATAL_ERROR
#endif