#pragma once
#include <cstdio>
#include <cstdint>
#include <type_traits>

namespace log {

enum class LOG_LEVEL {
    INFO = 0,
    WARN,
    ERROR,
    DEBUG,
    NONE
};

inline LOG_LEVEL logLevel = LOG_LEVEL::INFO;

inline const char* toString(LOG_LEVEL level);

// im totally misusing the word 'logarithm', but fuck it.
class logarithm {
public:
    inline void logInt(int val);
    inline void logHex(uintptr_t val);
    inline void logCstr(const char* str);

    template<typename T, typename... Args>
    void formatImpl(const char* fmt, T val, Args... args);
    inline void formatImpl(const char* fmt);

    template<typename... Args>
    void logFmt(LOG_LEVEL level, const char* fmt, Args... args);
};

} // namespace log
