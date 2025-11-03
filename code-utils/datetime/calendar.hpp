#pragma once

#include <ctime>
#include <string>
#include <sstream>

namespace g_utils {
    namespace datetime {
        class Calendar;

        class Calendar {
        public:
            void loadLocal() {
                std::time_t loadTimeT {std::time(NULL)};
                tm *time_struct {std::localtime(&loadTimeT)};

                this->m_Calendar = *time_struct;

                this->m_Calendar.tm_mon += 1;
                this->m_Calendar.tm_year += 1'900;
            }
            
            void loadUTC() {
                std::time_t loadTimeT {std::time(NULL)};
                tm *time_struct {std::gmtime(&loadTimeT)};

                this->m_Calendar = *time_struct;

                this->m_Calendar.tm_mon += 1;
                this->m_Calendar.tm_year += 1'900;
            }

            std::string toString() {
                std::stringstream date_time;
                
                date_time << this->m_Calendar.tm_mday << "/" << this->m_Calendar.tm_mon << "/" << this->m_Calendar.tm_year
                    << "_" << this->m_Calendar.tm_hour << "-" << this->m_Calendar.tm_min << "-" << this->m_Calendar.tm_sec;

                return date_time.str();
            }

            std::string toStringUSFormat() {
                std::stringstream date_time;
                
                date_time << this->m_Calendar.tm_mon << "/" << this->m_Calendar.tm_mday << "/" << this->m_Calendar.tm_year
                    << "_" << this->m_Calendar.tm_hour << "-" << this->m_Calendar.tm_min << "-" << this->m_Calendar.tm_sec;

                return date_time.str();
            }

            std::string dateToString() {
                std::stringstream date;
                
                date << this->m_Calendar.tm_mday << "/" << this->m_Calendar.tm_mon << "/" << this->m_Calendar.tm_year;

                return date.str();
            }

            std::string dateToStringUSFormat() {
                std::stringstream date;
                
                date << this->m_Calendar.tm_mon << "/" << this->m_Calendar.tm_mday << "/" << this->m_Calendar.tm_year;

                return date.str();
            }

            std::string timeToString() {
                std::stringstream time;
                
                time << this->m_Calendar.tm_hour << "-" << this->m_Calendar.tm_min << "-" << this->m_Calendar.tm_sec;

                return time.str();
            }

            inline std::tm getTm() const { return this->m_Calendar; }

            inline int seconds() const { return this->m_Calendar.tm_sec; }
            
            inline int minutes() const { return this->m_Calendar.tm_min; }
            
            inline int hours() const { return this->m_Calendar.tm_hour; }
            
            inline int weekDay() const { return this->m_Calendar.tm_wday; }
            
            inline int monthDay() const { return this->m_Calendar.tm_mday; }
            
            inline int month() const { return this->m_Calendar.tm_mon; }
            
            inline int yearDay() const { return this->m_Calendar.tm_yday; }
            
            inline int year() const { return this->m_Calendar.tm_year; }

        public:
            Calendar()           = default;
            virtual ~Calendar()  = default;

            Calendar(const Calendar &copy)              = default;
            Calendar & operator=(const Calendar &copy)  = default;

        private:
            std::tm m_Calendar;
        };
    }
}