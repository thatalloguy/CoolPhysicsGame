#pragma once
#include <vector>
#include "FastNoiseLite.h"
#include <raylib.h>
#include <cmath>
#include <lodepng.h>

void generateIslandAndExportToPNG(int size, const char* fileName)
{
    std::vector<float> heightmap(size * size);
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFrequency(0.025f);
    noise.SetFractalGain(0.5f);
    noise.SetFractalOctaves(1);
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            float nx = (float)x / size * size;
            float ny = (float)y / size * size;
            
            float n = noise.GetNoise(nx, ny);

            float distance_x = fabs(x - size * 0.5f);
            float distance_y = fabs(y - size * 0.5f);
            float distance = sqrt(distance_x * distance_x + distance_y * distance_y); // circular mask

            float max_width = size * 0.5f - 10.0f;
            float delta = distance / max_width;
            float gradient = delta * delta;

            n *= fmax(0.0f, 1.0f - gradient);

            //n = n * n * n * (n * (n * 6 - 15) + 10);
            heightmap[y * size + x] = n;
        }
    }

    std::vector<unsigned char> image(size * size * 4);

    for (int i = 0; i < size * size; i++)
    {
        float h = (heightmap[i] + 1.0) / 2.0;
        image[i * 4 + 0] = (unsigned char)(h * 255.0);
        image[i * 4 + 1] = (unsigned char)(h * 255.0);
        image[i * 4 + 2] = (unsigned char)(h * 255.0);
        image[i * 4 + 3] = 255;
    }

    unsigned error = lodepng::encode(fileName, image, size, size);

    if (error)
    {
        printf("Error %u: %s\n", error, lodepng_error_text(error));
    }
}