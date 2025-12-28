#pragma once
#include "Handler.hpp"

namespace log {

inline logarithm logger;

template<typename... Args>
static inline void info(const char* fmt, Args... args);

template<typename... Args>
static inline void warn(const char* fmt, Args... args);

template<typename... Args>
static inline void error(const char* fmt, Args... args);

template<typename... Args>
static inline void debug(const char* fmt, Args... args);

}
