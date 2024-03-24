#include "buffer.h"

#include <cstdint>
#include <assert.h>
#include <cstdio>
#include <limits>

// Ignore visual studio warning
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

Buffer::Buffer(unsigned short width, unsigned short height)
    : m_width(width), m_height(height)
{
    m_colorBuffer = new uint32_t[width * height]{ 0 };
    assert(m_colorBuffer != nullptr);
}

Buffer::~Buffer()
{
    delete[] m_colorBuffer;
    m_colorBuffer = nullptr;
}

void Buffer::ClearColor(uint32_t argb)
{
    for (int i = 0; i < m_width * m_height; i++)
    {
        m_colorBuffer[i] = argb;
    }
}

void Buffer::SaveToFile(const char* filename)
{
    unsigned short header[9] = {
        0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
        m_width, m_height,
        0x0820
    };

    FILE* file = fopen(filename, "wb+");
    assert(file != nullptr);
    fwrite(header, 2, 9, file);
    fwrite(m_colorBuffer, 4, m_width * m_height, file);
    fclose(file);
}

