/*
 * TzarRemake
 * Copyright (C) 2018
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

//--------------------------------------------------------------------------

#include <type_traits>
#include <cstdint>

//--------------------------------------------------------------------------

template <uint8_t type = 0>
struct StaticHandler
{
    enum
    {
        TYPE = type,
        INVALID = (1ul << 32) - 1
    };

    StaticHandler() :
        index(INVALID)
    {
    }

    void invalidate()
    {
        index = INVALID;
    }

    bool isValid()
    {
        return index != INVALID;
    }

    inline StaticHandler& operator=(StaticHandler&& rhs) noexcept
    {
        index = rhs.index;
        return *this;
    }

    inline bool operator<(const StaticHandler& rhs) noexcept
    {
        return index < rhs.index;
    }

    inline bool operator>(const StaticHandler& rhs) noexcept
    {
        return index > rhs.index;
    }

    inline bool operator<=(const StaticHandler& rhs) noexcept
    {
        return index <= rhs.index;
    }

    inline bool operator>=(const StaticHandler& rhs) noexcept
    {
        return index >= rhs.index;
    }

    inline bool operator==(StaticHandler&& rhs) noexcept
    {
        return index == rhs.index;
    }

    uint32_t index;
};
