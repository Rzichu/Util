#pragma once

#include <string>

namespace g_utils {
    namespace enums {
        template<typename ENUM_TYPE>
        constexpr auto toUnderlyingType(const ENUM_TYPE value)
            -> typename std::underlying_type<ENUM_TYPE>::type
            {
            return static_cast<typename std::underlying_type<ENUM_TYPE>::type>(value);
        }

        std::string identifierFromString(const std::string &p_enum_string) {
            unsigned long long char_pos = p_enum_string.rfind(':');
            if (char_pos != std::string::npos) {
                return p_enum_string.substr(char_pos + 1ull);
            }
            else {
                return p_enum_string;
            }
        }
    }
}

#define ENUM_TO_STRING_ID(enum_val) g_utils::enums::identifierFromString(#enum_val)
#define ENUM_TO_STRING_FULL(enum_val) #enum_val