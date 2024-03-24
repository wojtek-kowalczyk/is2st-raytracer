#pragma once

#include <cstdint>

typedef uint32_t ARGB;

class Buffer
{
public:
    Buffer(unsigned short width, unsigned short height);
    ~Buffer();

    void ClearColor(ARGB color);
    void SaveToFile(const char* filename); // can be moved to some static helper

    unsigned short GetWidth() const { return m_width; }
    unsigned short GetHeight() const { return m_height; }

    ARGB& ColorAt(int x, int y) { return m_colorBuffer[y * m_width + x]; }
    ARGB ColorAt(int x, int y) const { return m_colorBuffer[y * m_width + x]; }

private:
    ARGB* m_colorBuffer;
    unsigned short m_width;
    unsigned short m_height;
};