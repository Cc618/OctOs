#pragma once

// Algorithms implementation

namespace std
{
    // Maximum of 2 values
    template <typename T>
    inline T max(const T &FIRST, const T &SECOND)
    {
        if (FIRST > SECOND)
            return FIRST;

        return SECOND;
    }

    // Minimum of 2 values
    template <typename T>
    inline T min(const T &FIRST, const T &SECOND)
    {
        if (FIRST < SECOND)
            return FIRST;

        return SECOND;
    }
} // namespace std


