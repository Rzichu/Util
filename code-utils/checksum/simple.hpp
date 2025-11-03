#pragma once

#include <cstdint>
#include <cstddef>
#include <fstream>
#include <vector>

namespace g_utils {
    namespace simpleChecksum {
        uint32_t simpleChecksum(const char* p_data, size_t p_size) {
            uint32_t checksum = 0;
            for (size_t i = 0; i < p_size; ++i) {
                checksum += static_cast<unsigned char>(p_data[i]);
            }
            return checksum;
        }

        bool validateChecksum(const std::string& p_filename) {
            std::ifstream file(p_filename, std::ios::binary);
            if (!file) return false;

            file.seekg(0, std::ios::end);
            size_t fileSize = file.tellg();
            if (fileSize < sizeof(uint32_t)) return false;

            file.seekg(0, std::ios::beg);
            size_t dataSize = fileSize - sizeof(uint32_t);
            std::vector<char> data(dataSize);
            file.read(data.data(), dataSize);

            uint32_t stored_checksum;
            file.read(reinterpret_cast<char*>(&stored_checksum), sizeof(stored_checksum));

            uint32_t calculated_checksum = simpleChecksum(data.data(), dataSize);
            return stored_checksum == calculated_checksum;
        }

        bool validateChecksum(const std::string& p_filename, uint32_t p_valid_checksum) {
            std::ifstream file(p_filename, std::ios::binary);
            if (!file) return false;

            file.seekg(0, std::ios::end);
            size_t fileSize = file.tellg();
            if (fileSize < sizeof(uint32_t)) return false;

            file.seekg(0, std::ios::beg);
            size_t dataSize = fileSize - sizeof(uint32_t);
            std::vector<char> data(dataSize);
            file.read(data.data(), dataSize);

            uint32_t stored_checksum;
            file.read(reinterpret_cast<char*>(&stored_checksum), sizeof(stored_checksum));

            return stored_checksum == p_valid_checksum;
        }
    }
}