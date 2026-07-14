#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <chrono>

class UUIDGenerator {
public:
    static std::string generate() {
        static std::random_device rd;
        static std::mt19937_64 gen(rd() ^ 
            std::chrono::steady_clock::now().time_since_epoch().count());
        static std::uniform_int_distribution<uint64_t> dis;

        uint64_t a = dis(gen);
        uint64_t b = dis(gen);

        // 设置版本号 (version 4) 和变体 (variant 1)
        a = (a & 0xFFFFFFFFFFFF0FFFULL) | 0x0000000000004000ULL;
        b = (b & 0x3FFFFFFFFFFFFFFFULL) | 0x8000000000000000ULL;

        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        ss << std::setw(8) << ((a >> 32) & 0xFFFFFFFF) << "-"
           << std::setw(4) << ((a >> 16) & 0xFFFF) << "-"
           << std::setw(4) << (a & 0xFFFF) << "-"
           << std::setw(4) << ((b >> 48) & 0xFFFF) << "-"
           << std::setw(12) << (b & 0xFFFFFFFFFFFFULL);

        return ss.str();
    }
};