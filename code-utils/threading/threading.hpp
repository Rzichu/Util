#pragma once

#include <future>

namespace g_utils {
    namespace threading {
        inline const uint32_t getThreadId() {
            return uint32_t(std::hash<std::thread::id>{}(std::this_thread::get_id()));
        }
    }
}