#pragma once

#include <globals.h>
#include <logger/string_format.h>

#include <concepts>
#include <ctime>

#include <format>
#include <iostream>
#include <sstream>

namespace sealeo {

// concepts
template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept StringLike = std::same_as<std::decay_t<T>, std::u16string>
                     || std::same_as<std::decay_t<T>, std::string>
                     || std::same_as<std::decay_t<T>, const char*>
                     || std::same_as<std::decay_t<T>, char*>;

template <typename T>
concept OStreamable = requires(std::ostream& os, T a) {
    { os << a } -> std::same_as<std::ostream&>;
};

template <typename T>
concept Loggable = Arithmetic<T> || StringLike<T> || OStreamable<T>;

// enum class for message type
enum class LoggerLevel { DEBUG = 0, INFO, WARN, ERROR, MESSAGE };

// Singleton logger class
class logger {
private:
    // Map levels to colorized strings
    const std::unordered_map<LoggerLevel, std::string> level_color_map_ = {
        {LoggerLevel::DEBUG,   sealeo::format::colorize_string(u"§9§lDEBUG§r")  },
        {LoggerLevel::INFO,    sealeo::format::colorize_string(u"§b§lINFO§r")   },
        {LoggerLevel::WARN,    sealeo::format::colorize_string(u"§e§lWARN§r")   },
        {LoggerLevel::ERROR,   sealeo::format::colorize_string(u"§c§lERROR§r")  },
        {LoggerLevel::MESSAGE, sealeo::format::colorize_string(u"§f§lMESSAGE§r")},
    };

    // Format string uses Minecraft color code formatters
    // Supports
    //      %name%: program name
    //      %level%: logger level (special -- uses the above map)
    //      %time%: timestamp
    //      %message%: message
    std::string format_string_ = sealeo::format::colorize_string(
        u"[%name%/%level%] (§f%time%§rZ) §r%message%§r"
    );

    // Current level: anything less won't be printed
    LoggerLevel current_level_;

    // Abstract log function. Rejects messages below current_level_ and applies
    // formatting
    void log(LoggerLevel level, std::string msg);

    // Convert message to a string

    template <OStreamable T>
    inline std::string
    convert_msg_to_string(T msg)
    {
        std::ostringstream oss;
        oss << msg;
        return oss.str();
    }

    template <StringLike T>
    requires(!OStreamable<T>)
    inline std::string
    convert_msg_to_string(T msg)
    {
        return std::string(msg);
    }

    template <Arithmetic T>
    requires(!OStreamable<T> && !StringLike<T>)
    inline std::string
    convert_msg_to_string(T msg)
    {
        return std::to_string(msg);
    }

public:
    // Constructor and make singleton class
    logger(LoggerLevel level) : current_level_(level) {}

    logger(LoggerLevel level, std::u16string raw_format_string) :
        current_level_(level),
        format_string_(sealeo::format::colorize_string(raw_format_string))
    {}

    static logger&
    instance(LoggerLevel level)
    {
        static logger logger_instance(LoggerLevel::MESSAGE);
        logger_instance.set_level(level);
        return logger_instance;
    }

    // Set the format string to something new using § to encode colors and formatting
    inline void
    set_format_string(std::u16string raw_format_string)
    {
        format_string_ = sealeo::format::colorize_string(raw_format_string);
    }

    // Set log level: anything lower will not be printed
    inline void
    set_level(LoggerLevel new_level)
    {
        current_level_ = new_level;
    }

    // Loggers
    template <Loggable message_t>
    inline void
    debug(const message_t& msg)
    {
        log(LoggerLevel::DEBUG, convert_msg_to_string(msg));
    }

    template <Loggable message_t>
    inline void
    info(const message_t& msg)
    {
        log(LoggerLevel::INFO, convert_msg_to_string(msg));
    }

    template <Loggable message_t>
    inline void
    warn(const message_t& msg)
    {
        log(LoggerLevel::WARN, convert_msg_to_string(msg));
    }

    template <Loggable message_t>
    inline void
    error(const message_t& msg)
    {
        log(LoggerLevel::ERROR, convert_msg_to_string(msg));
    }

    template <Loggable message_t>
    inline void
    msg(const message_t& msg)
    {
        log(LoggerLevel::MESSAGE, convert_msg_to_string(msg));
    }
};

} // namespace sealeo
