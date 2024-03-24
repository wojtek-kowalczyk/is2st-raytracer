#pragma once

float ToCanonicalSpace(int pixelValue, float bufferLimit)
{
    return (pixelValue / (0.5f * bufferLimit)) - 1.0f;
}

int ToPixelSpace(float canonicalValue, int bufferLimit)
{
    return int((canonicalValue + 1) * bufferLimit * 0.5f);
}