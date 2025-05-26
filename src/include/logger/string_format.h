#pragma once

#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

namespace sealeo {
namespace format {

enum class ColorCode : char {
    BLACK = '0',
    DARKBLUE = '1',
    DARKGREEN = '2',
    DARKAQUA = '3',
    DARKRED = '4',
    DARKPURPLE = '5',
    GOLD = '6',
    LIGHTGRAY = '7',
    DARKGRAY = '8',
    BLUE = '9',
    LIGHTGREEN = 'a',
    AQUA = 'b',
    RED = 'c',
    LIGHTPURPLE = 'd',
    YELLOW = 'e',
    WHITE = 'f',
    BOLD = 'l',
    UNDERLINE = 'n',
    ITALICS = 'o',
    RESET = 'r'
};

static const std::unordered_map<ColorCode, std::string> color_map = {
    {ColorCode::BLACK,       "\033[30m"}, // black
    {ColorCode::DARKBLUE,    "\033[34m"}, // dark blue
    {ColorCode::DARKGREEN,   "\033[32m"}, // dark green
    {ColorCode::DARKAQUA,    "\033[36m"}, // dark aqua
    {ColorCode::DARKRED,     "\033[31m"}, // dark red
    {ColorCode::DARKPURPLE,  "\033[35m"}, // dark purple
    {ColorCode::GOLD,        "\033[33m"}, // gold
    {ColorCode::LIGHTGRAY,   "\033[37m"}, // light gray
    {ColorCode::DARKGRAY,    "\033[90m"}, // dark gray
    {ColorCode::BLUE,        "\033[94m"}, // blue
    {ColorCode::LIGHTGREEN,  "\033[92m"}, // light green
    {ColorCode::AQUA,        "\033[96m"}, // aqua
    {ColorCode::RED,         "\033[91m"}, // red
    {ColorCode::LIGHTPURPLE, "\033[95m"}, // light purple
    {ColorCode::YELLOW,      "\033[93m"}, // yellow
    {ColorCode::WHITE,       "\033[97m"}, // white
    {ColorCode::BOLD,        "\033[1m" }, // bold
    {ColorCode::UNDERLINE,   "\033[4m" }, // underline
    {ColorCode::ITALICS,     "\033[3m" }, // italicize
    {ColorCode::RESET,       "\033[0m" }  // reset format
};

inline bool
is_color_symbol(char16_t c)
{
    return c == *u"§";
}

// Converts Minecraft formatting codes (e.g. §c§l) into shell codes
std::string colorize_string(std::u16string str);

// Replace a key in a string, i.e. %key%, with val. The match must be exact
// Examples:
//      replace_string("Apples and %fruit%", "fruit", "oranges") -> Apples and oranges
//      replace_string("Apples and fruit", "fruit", "oranges") -> Apples and fruit
//      replace_string("Apples and %%fruit%%", "%fruit%", "oranges") -> Apples and
//      oranges
std::string
replace_string(std::string str, std::vector<std::string> keys, std::string val);

} // namespace format
} // namespace sealeo
