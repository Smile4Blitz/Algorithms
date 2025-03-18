#include <stdint.h>

#include <algorithm>
#include <iostream>

#include "color.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <unistd.h>

#include <memory>

#include "kdColorQuantizer.h"
#include "naiveColorQuantizer.h"
#include "stb_image_write.h"

std::vector<Color> load_image(const char *filename, int &width, int &height,
                              int &channels) {
    std::cout << "Loading " << filename << std::endl;
    unsigned char *rgb_image =
        stbi_load(filename, &width, &height, &channels, 3);

    if (rgb_image == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }

    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "channels: " << channels << std::endl;

    // std::vector<unsigned char> image(rgb_image,
    //                                  rgb_image + width * height * channels);
    std::vector<Color> image;

    for (int i = 0; i < width * height * channels; i = i + 3) {
        unsigned char r = *(rgb_image + i);
        unsigned char g = *(rgb_image + i + 1);
        unsigned char b = *(rgb_image + i + 2);

        image.push_back(Color(r, g, b));
    }

    stbi_image_free(rgb_image);

    return image;
}

void write_image(std::vector<Color> &image, const char *filename, int width,
                 int height, int channels) {
    std::vector<unsigned char> imageResult;

    for (int i = 0; i < image.size(); i++) {
        imageResult.push_back(image[i].r);
        imageResult.push_back(image[i].g);
        imageResult.push_back(image[i].b);
    }

    stbi_write_png(filename, width, height, channels, imageResult.data(),
                   width * channels);
}

void storePalette(std::vector<Color> palette, const char *fileName) {
    std::vector<Color> img;
    const int width = 64;
    const int height = 64;

    for (int h = 0; h < height; h++) {
        for (Color color : palette) {
            for (int w = 0; w < width; w++) {
                img.push_back(color);
            }
        }
    }

    write_image(img, fileName, width * palette.size(), height, 3);
}

int main() {
    int width, height, channels;
    std::string path = "images/";
    std::string fileName = "mandrill_512.png";
    // std::string fileName = "lenna.png";
    // std::string fileName = "peppers.png";

    std::string fileNameNaive =
        fileName.substr(0, fileName.size() - 4) + std::string("_naive.png");
    std::string fileNamePaletteNaive = fileName.substr(0, fileName.size() - 4) +
                                       std::string("_naive_palette.png");
    std::string fileNameKd =
        fileName.substr(0, fileName.size() - 4) + std::string("_kd.png");
    std::string fileNamePaletteKd = fileName.substr(0, fileName.size() - 4) +
                                    std::string("_kd_palette.png");

    std::vector<Color> img =
        load_image((path + fileName).c_str(), width, height, channels);

    // naive
    std::cout << "Creating palette and quantizing with NaiveColorQuantizer" << std::endl;
    NaiveColorQuantizer naiveColorReducer = NaiveColorQuantizer(16);
    naiveColorReducer.createPalette(img, 16);
    storePalette(naiveColorReducer.getPalette(), (path + fileNamePaletteNaive).c_str());
    std::vector<Color> imgRedNaive = naiveColorReducer.quantize(img);
    write_image(imgRedNaive, (path + fileNameNaive).c_str(), width, height,
                channels);

    // K-D
    std::cout << "Implement KdColorQuantizer" << std::endl;
    KdColorQuantizer kdColorReducer = KdColorQuantizer();
    kdColorReducer.createPalette(img, 16);
    // storePalette(kdColorReducer.getPalette(), (path + fileNamePaletteKd).c_str());
    std::vector<Color> imgRedKd = kdColorReducer.quantize(img);
    // write_image(img, (path + fileName).c_str(), width, height, channels);

    return 0;
}