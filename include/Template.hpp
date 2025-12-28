#pragma once
#include "Handler.hpp"

namespace log {

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

template<typename... Args>
void logarithm::logFmt(LOG_LEVEL level, const char* fmt, Args... args) {
    if (level > logLevel) return;

    printf("[%s]: ", toString(level));
    formatImpl(fmt, args...);
    std::fputc('\n', stdout);
}

} // namespace log
