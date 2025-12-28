#include "Handler.hpp"

namespace log {

const char* log::toString(LOG_LEVEL level) {
    switch (level) {
        case LOG_LEVEL::INFO: return "INFO";
        case LOG_LEVEL::WARN: return "WARN";
        case LOG_LEVEL::ERROR: return "ERROR";
        case LOG_LEVEL::DEBUG: return "DEBUG";
        default: return "UNKNOWN"; 
    }
}

void logarithm::logInt(int val) {
    if (val < 0) val = -val;
    long long div = 1000000000LL;
    bool started = false;

    for (int i = 0; i < 10; ++i) {
        int digit = val / div;
        if (digit != 0 || started || div == 1) {
            std::putc('0' + digit, stdout);
            started = true;
        }

        val %= div;
        div /= 10;
    }
}

void logarithm::logHex(uintptr_t val) {
    std::fputs("0x", stdout);
    bool started = false;

    for (int shift = (sizeof(uintptr_t)*8) - 4; shift >= 0; shift -= 4) {
        int nibble = (val >> shift) & 0xF;
        if (nibble != 0 || started || shift == 0) {
            char ch = (nibble < 10) ? ('0' + nibble) : ('a' + (nibble - 10));
            std::fputc(ch, stdout);
            started = true;
        }
    }
}

void logarithm::logCstr(const char* str) {
    while (*str) {
        std::fputc(*str, stdout);
        ++str;
    }
}

template<typename T, typename... Args>
void logarithm::formatImpl(const char* fmt, T val, Args... args) {
    while (*fmt) {
        if (fmt[0] == '{' && fmt[1] == ':' && fmt[3] == '}') {
            char spec = fmt[2];
            switch (spec) {
                case 'd': logInt(static_cast<int>(val)); break;
                case 'x': logHex(static_cast<uintptr_t>(val)); break;
                case 'p': logHex(reinterpret_cast<uintptr_t>(val)); break;
                case 's': logCstr(static_cast<const char*>(val)); break;
                default: std::fputc('?', stdout); break;
            }

            fmt += 4;
            if constexpr(sizeof...(args) > 0)
                formatImpl(fmt, args...);
            return;
        } else {
            std::fputc(*fmt, stdout);
        }
        ++fmt;
    }
}

void logarithm::formatImpl(const char* fmt) {
    while (*fmt) {
        std::fputc(*fmt, stdout);
        ++fmt;
    }   
}

template<typename... Args>
void logarithm::logFmt(LOG_LEVEL level, const char* fmt, Args... args) {
    if (level > logLevel) return;

    printf("[%s]: ", toString(level));
    formatImpl(fmt, args...);
    std::fputc('\n', stdout);
}

// see Api.cpp

} // namespace log
