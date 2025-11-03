#pragma once

#include <chrono>

namespace g_utils {
    namespace datetime {
        class Clock {
        public:
            Clock() = default;
            virtual ~Clock() = default;

        public:
            inline double miliToSeconds(double p_miliseconds) {
                return (p_miliseconds * 0.001);
            }

            void resume() {
                if (!this->m_Running) {
                    this->m_Running = true;
                }
            }

            inline double stop() {
                if (this->m_Running) {
                    this->m_Running = false;
                    this->calculateTime();
                }
                return this->m_Time;
            }

            inline double restart() {
                if (this->m_Running) {
                    this->calculateTime();
                }
                else {
                    this->m_Running = true;
                }
                this->m_startTimePoint = std::chrono::steady_clock::now();
                return this->m_Time;
            }

            inline double time() {
                if (this->m_Running) {
                    this->calculateTime();
                }
                return this->m_Time;
            }
        
        protected:
            virtual void calculateTime() {
                auto endTimePoint = std::chrono::steady_clock::now();

                auto start = std::chrono::time_point_cast<std::chrono::microseconds>(this->m_startTimePoint).time_since_epoch().count();
                auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
            
                double duration = static_cast<double>(end - start);
                this->m_Time = duration * 0.001;
            }

        protected:
            std::chrono::time_point<std::chrono::steady_clock> m_startTimePoint {std::chrono::steady_clock::now()};
            double m_Time {0.0};
            bool m_Running {true};
        };

        class ScaledClock final : public Clock {
        public:
            ScaledClock(double p_timescale)
                : m_TimeScale(p_timescale)
                {}

            ScaledClock() = default;

            inline double getTimeScale() const { return this->m_TimeScale; }

            void setTimeScale(double p_timescale) {
                if (p_timescale < 0.0) {
                    p_timescale = 0.0;
                }
                this->m_TimeScale = p_timescale;
            }

            inline double restart(double p_timescale = 1.0) {
                if (this->m_Running) {
                    this->calculateTime();
                }
                else {
                    this->m_Running = true;
                }
                this->m_startTimePoint = std::chrono::steady_clock::now();
                this->setTimeScale(p_timescale);
                return this->m_Time;
            }

        private:
            void calculateTime() override {
                auto endTimePoint = std::chrono::steady_clock::now();

                auto start = std::chrono::time_point_cast<std::chrono::microseconds>(this->m_startTimePoint).time_since_epoch().count();
                auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
            
                double duration = static_cast<double>(end - start);
                this->m_Time = (duration * 0.001) * this->m_TimeScale;
            }
        
        private:
            double m_TimeScale {1.0};
        };
    }
}