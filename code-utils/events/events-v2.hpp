#pragma once

#include <functional>
#include <vector>
#include <algorithm>
#include <memory>
#include <mutex>

namespace g_utils {
    namespace events {
        template<typename... ARGS>
        class Event {
        public:
            using callback = std::function<void(ARGS...)>;

            template<typename T>
            void addListener(std::weak_ptr<T> p_object, void (T::*p_method)(ARGS...)) {
                std::lock_guard<std::mutex> lock(this->m_Mutex);
                this->m_Listeners.emplace_back([p_object, p_method](ARGS... args) {
                    if (auto obj = p_object.lock()) {
                        (obj.get()->*p_method)(args...);
                    } 
                });
            }

            void addListener(const callback &p_listener) {
                std::lock_guard<std::mutex> lock(this->m_Mutex);
                this->m_Listeners.push_back(p_listener);
            }

            void removeListener(const callback &p_listener) {
                std::lock_guard<std::mutex> lock(this->m_Mutex);
                auto it = std::find_if(this->m_Listeners.begin(), this->m_Listeners.end(), [&](const callback &p_stored_listener) {
                    return this->compareCallbacks(p_stored_listener, p_listener);
                });
                if (it != this->m_Listeners.end()) {
                    this->m_Listeners.erase(it);
                }
            }

            void invoke(ARGS... args) {
                std::vector<callback> listeners_copy;

                // TO AVOID DEADLOCKS
                {
                    std::lock_guard<std::mutex> lock(this->m_Mutex);
                    listeners_copy = this->m_Listeners;
                }

                for (const auto &listener : listeners_copy) {
                    listener(args...);
                }
            }

        protected:
            mutable std::mutex m_Mutex;
            std::vector<callback> m_Listeners;

            bool compareCallbacks(const callback &a, const callback &b) const {
                return a.target_type() == b.target_type() && *a.template target<void(ARGS...)>() == *b.template target<void(ARGS...)>();
            }
        };
    }
}