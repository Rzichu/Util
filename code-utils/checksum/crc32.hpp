#pragma once

#include <cstdint>
#include <cstddef>
#include <array>
#include <fstream>
#include <vector>

namespace g_utils {
    namespace checksum {
        namespace internal {
            const std::array<uint32_t, 256> crcTable = []() {
                std::array<uint32_t, 256> table{};
                for (uint32_t i = 0; i < 256; ++i) {
                    uint32_t crc = i;
                    for (uint32_t j = 0; j < 8; ++j) {
                        if (crc & 1) {
                            crc = (crc >> 1) ^ 0xEDB88320; // POLYNOMIAL
                        } else {
                            crc >>= 1;
                        }
                    }
                    table[i] = crc;
                }
                return table;
            }();
        }

        uint32_t crc32Checksum(const char* p_data, size_t p_size) {
            uint32_t crc = 0xFFFFFFFF;
            for (size_t i = 0; i < p_size; ++i) {
                uint8_t byte = static_cast<unsigned char>(p_data[i]);
                crc = (crc >> 8) ^ internal::crcTable[(crc ^ byte) & 0xFF];
            }
            return ~crc;
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

            uint32_t calculated_checksum = crc32Checksum(data.data(), dataSize);
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