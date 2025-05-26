#include <logger/string_format.h>

#include <exception>
#include <iostream>

namespace sealeo {
namespace format {

std::string
colorize_string(std::u16string str)
{
    std::string output = "";

    for (std::size_t index = 0; index < str.size(); index++) {
        char16_t letter = str[index];
        bool is_last_char = index == str.length() - 1;
        if (!is_color_symbol(letter) || is_last_char) {
            output += letter;
            continue;
        }

        const auto raw_color_code = str[index + 1];
        auto color_map_itr = color_map.find(ColorCode(raw_color_code));
        if (color_map_itr == color_map.end()) {
            throw std::runtime_error(
                std::string("Invalid color code used §")
                + static_cast<char>(raw_color_code)
            );
        }

        output += color_map_itr->second;
        index++;
    }

    output += color_map.at(ColorCode::RESET);
    return output;
}

std::string
replace_string(std::string str, std::vector<std::string> keys, std::string val)
{
    for (std::string& key : keys) {
        std::string match = "%" + key + "%";
        std::size_t pos = str.find(match);
        if (pos != std::string::npos) {
            str.replace(pos, match.length(), val);
        }
    }
    return str;
}

} // namespace format
} // namespace sealeo
