#include "buffer.h"
#include "color.h"

#include <cstdint>
#include <assert.h>
#include <cstdio>
#include <limits>
#include <cmath>

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

void Buffer::ClearColor(ARGB color)
{
    for (int i = 0; i < m_width * m_height; i++)
    {
        m_colorBuffer[i] = color;
    }
}

static float LinearToGamma(float linear)
{
    if (linear > 0)
    {
        return sqrt(linear);
    }

    return 0;
}

void Buffer::SaveToFile(const char* filename)
{
    // TGA format

    unsigned short header[9] = {
        0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
        m_width, m_height,
        0x0820
    };

    // Convert from linear to gamma space
    for (int i = 0; i < m_width * m_height; i++) 
    {
        Color color = Color::FromInt(m_colorBuffer[i]);
        color.r = LinearToGamma(color.r);
        color.g = LinearToGamma(color.g);
        color.b = LinearToGamma(color.b);
        m_colorBuffer[i] = Color::ToInt(color);
    }

    FILE* file = fopen(filename, "wb+");
    assert(file != nullptr);
    fwrite(header, 2, 9, file);
    fwrite(m_colorBuffer, 4, m_width * m_height, file);
    fclose(file);
}

