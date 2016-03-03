
// Copyright (c) <2011> Daniel Peterson
// This file is part of Mini3D <www.mini3d.org>
// It is distributed under the MIT Software License <www.mini3d.org/license.php>

#include <cstdlib>
#include <ctime>


unsigned int ClampRand()
{
    unsigned int value = 128 + (int)((double)rand() / RAND_MAX * 128);
    return value;
}

// Creates an RGBA8 texture
unsigned int* CreateTestBitmapRGBA8(unsigned int width, unsigned int height)
{
    unsigned int* pBitmap = new unsigned int[width * height];

    srand((unsigned int)time(0));

    // Create a low res version 
    // This is what gives the pixelated look
    unsigned int widthOver16 = width / 16;
    unsigned int heightOver16 = height / 16;
    
    unsigned int* lowRes = new unsigned int[widthOver16 * heightOver16];

    for (unsigned int x = 0; x < widthOver16; x++)
        for (unsigned int y = 0; y < heightOver16; y++)
            lowRes[x + y * widthOver16] = ClampRand();

    // Blend with the low res version with high resolution noise
    // This creates the small noise
    for (unsigned int x = 0; x < width; x++)
    {
        for (unsigned int y = 0; y < height; y++)
        {
            unsigned int value = (unsigned int)(ClampRand() * 0.3f + lowRes[(x / 16) + (y / 16 * widthOver16)] * 0.7f);
            pBitmap[x + y * width] = value / 4 + (value * 256) + ((value / 4) * 65535);
        }
    }

    delete[] lowRes;

    return pBitmap;
}

