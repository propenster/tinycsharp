/*
 * This file is part of tinycsharp.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2025 Faith (propenster) Olusegun.
 * Contact: https://propenster.github.io
 */

#pragma once

#include <string>
#include <cctype>
#include <algorithm>
#include <string_view>

namespace util
{
    // Convert a string to lowercase
    inline std::string to_lowercase(std::string_view input)
    {
        std::string result;
        result.reserve(input.size());
        for (const auto &c : input)
        {
            result += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        return result;
    }
    inline bool is_non_primitive_member_type(std::string_view type) noexcept
    {
        return to_lowercase(type) == "input" ||
               to_lowercase(type) == "output" ||
               to_lowercase(type) == "runtime" ||
               to_lowercase(type) == "meta";
    }
    inline bool array_contains_char(char chr) noexcept
    {
        const std::array<char, 12> arr = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_', '.'};
        return std::find(arr.begin(), arr.end(), chr) != arr.end();
    }
    inline bool is_reference_type(std::string_view type) noexcept
    {
        return to_lowercase(type) == "array" || to_lowercase(type) == "map" || to_lowercase(type) == "pair";
    }

}