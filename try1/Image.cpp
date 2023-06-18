//  Copyright [2023] <Arkadia Kowalczyk>
#include <cstdint>  // for specific size integers
#include <fstream>  // for file handling
#include "Image.h"  // my header

#pragma pack(push, 1)
struct BmpHeader {
    char bitmapSignatureBytes[2] = { 'B', 'M' };
    uint32_t sizeOfBitmapFile = { 54 + 786432 };  // total size of bitmap file
    uint32_t reservedBytes = { 0 };
    uint32_t pixelDataOffset = { 54 };
}  bmpHeader;
#pragma pack(pop)

#pragma pack(push, 1)
struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = 40;
    int32_t width = 512;   // in pixels
    int32_t height = 512;  // in pixels
    uint16_t numberOfColorPlanes = 1;  // must be 1
    uint16_t colorDepth = 24;
    uint32_t compressionMethod = 0;
    uint32_t rawBitmapDataSize = 0;       // generally ignored
    int32_t horizontalResolution = 3780;  // in pixel per meter
    int32_t verticalResolution = 3780;    // in pixel per meter
    uint32_t colorTableEntries = 0;
    uint32_t importantColors = 0;
} bmpInfoHeader;
#pragma pack(pop)

#pragma pack(push, 1)
struct Pixel {
    uint8_t blue = 255;
    uint8_t green = 255;
    uint8_t red = 255;
} whitePixel, blkPixel;
#pragma pack(pop)

bool isEqual(Pixel a, Pixel b) {
    if ((a.blue == b.blue) && (a.green == b.green) && (a.red == b.red)) {
        return true;
    }
    return false;
}

Pixel obraz[512][512];
Pixel wzor[25][25];

    int picture::newPicture(std::string nazwaPliku) {
        blkPixel.blue = 0;
        blkPixel.green = 0;
        blkPixel.red = 0;

        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 25; j++) {
                wzor[i][j] = whitePixel;
            }
        }

        for (int i = 0; i < bmpInfoHeader.width; i++) {
            for (int j = 0; j < bmpInfoHeader.height; j++) {
                obraz[i][j] = whitePixel;
            }
        }

        for (int i = 0; i < bmpInfoHeader.width; i++) {
            for (int j = 0; j < bmpInfoHeader.height; j += 20) {
                obraz[i][j] = blkPixel;
            }
        }

        for (int i = 0; i < bmpInfoHeader.width; i+=20) {
            for (int j = 0; j < bmpInfoHeader.height; j ++) {
                obraz[i][j] = blkPixel;
            }
        }
        nazwa = nazwaPliku;
        redraw();

        return 0;
    }

    int picture::fillSquare(int y, int x, int rValue, int gValue, int bValue) {
        if ((x > 23) || (x < 1) || (y > 23) || (y < 1)) return 0;
        if (!(isEqual(wzor[x][y], whitePixel))) return 0;
        Pixel temp = { (uint8_t) bValue, (uint8_t) gValue, (uint8_t) rValue };

        wzor[x][y] = temp;
        x = x * 20;
        y = y * 20;
        for (int i = 1; i < 20; i++) {
            if (i + x >= 500) return 0;
            for (int j = 1; j < 20; j++) {
                if (j + y >= 500) return 0;

                obraz[i + x][j + y] = temp;
            }
        }
        redraw();
        return 0;
    }

    int picture::redraw() {
        std::ofstream fout(nazwa, std::ios::binary);

        fout.write(reinterpret_cast<char*>(&bmpHeader), 14);
        fout.write(reinterpret_cast<char*>(&bmpInfoHeader), 40);

        // writing pixel data
        for (int i = 0; i < bmpInfoHeader.width; i++) {
            for (int j = 0; j < bmpInfoHeader.height; j++)
                fout.write(reinterpret_cast<char*>(&(obraz[i][j])), 3);
                // ^^^kolory zapisywane sa odtylu dlatego podajemy bgr a nie rgb
        }
        fout.close();
        return 0;
    }





