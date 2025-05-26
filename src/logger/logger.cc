#include <logger/logger.h>

namespace sealeo {

std::string
get_timestamp_string()
{
    time_t timestamp;
    time(&timestamp);
    return std::to_string(timestamp);
}

void
logger::log(LoggerLevel level, std::string msg)
{
    if (level < current_level_)
        return;

    std::string output = format_string_;

    output = format::replace_string(output, {"name", "n"}, sealeo::globals::name);
    output = format::replace_string(
        output, {"level", "lvl", "l"}, level_color_map_.at(level)
    );
    output = format::replace_string(
        output, {"timestamp", "time", "t"}, get_timestamp_string()
    );
    output = format::replace_string(output, {"message", "msg", "m"}, msg);

    std::cout << output << "\n";
}

} // namespace sealeo
