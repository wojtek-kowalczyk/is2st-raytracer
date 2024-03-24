#pragma once

#include <cstdint>

class Buffer
{
public:
    Buffer(unsigned short width, unsigned short height);
    ~Buffer();

    void ClearColor(uint32_t color);
    void SaveToFile(const char* filename); // can be moved to some static helper

    unsigned short GetWidth() const { return m_width; }
    unsigned short GetHeight() const { return m_height; }

    uint32_t& ColorAt(int x, int y) { return m_colorBuffer[y * m_width + x]; }
    uint32_t ColorAt(int x, int y) const { return m_colorBuffer[y * m_width + x]; }

private:
    uint32_t* m_colorBuffer;
    unsigned short m_width;
    unsigned short m_height;
};