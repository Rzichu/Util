#pragma once

#include <functional>
#include <vector>

// WIP

namespace g_utils {
    namespace eventsystem {
        template <typename R_TYPE, typename... ARGS>
        class Action {
        public:
            Action & operator+(std::function<R_TYPE(ARGS ...)> p_subscriber) {
                this->m_Subscribers.push_back(p_subscriber);
            }

            Action & operator-(std::function<R_TYPE(ARGS ...)> p_subscriber) {
                
            }

        private:
            std::vector<std::function<R_TYPE(ARGS ...)>> m_Subscribers;
        };
    }
}