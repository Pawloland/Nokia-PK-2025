#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <tuple>

namespace common
{

class ILogger
{
public:
    virtual ~ILogger() = default;

    template <typename ...Value>
    void logError(Value&& ...value);

    template <typename ...Value>
    void logInfo(Value&& ...value);

    template <typename ...Value>
    void logDebug(Value&& ...value);

    using Level = int;
    static constexpr Level DEBUG_LEVEL = 0;
    static constexpr Level INFO_LEVEL = 1;
    static constexpr Level ERROR_LEVEL = 2;
    // user might define more levels, these are just predefined...

    virtual void log(Level level, const std::string& message) = 0;

    // shortcuts machinery
    template <typename ...Value>
    void log(Level level, Value&& ...value);
    void log(Level level, std::string_view);
};

template <typename ...Value>
inline void ILogger::logError(Value&& ...value)
{
    log(ERROR_LEVEL, std::forward<Value>(value)...);
}
template <typename ...Value>
inline void ILogger::logInfo(Value&& ...value)
{
    log(INFO_LEVEL, std::forward<Value>(value)...);
}
template <typename ...Value>
inline void ILogger::logDebug(Value&& ...value)
{
    log(DEBUG_LEVEL, std::forward<Value>(value)...);
}

// shortcuts machinery
template <typename ...Value>
inline void ILogger::log(Level level, Value&& ...value)
{
    std::ostringstream os;
    ((os << std::forward<Value>(value)), ...);
    const std::string message = std::move(os).str();
    log(level, message);
}

inline void ILogger::log(Level level, std::string_view value)
{
    log(level, std::string(value));
}

} // namespace common
