#include "naiveColorQuantizer.h"

#include <math.h>
#include <stdint.h>

#include <algorithm>
#include <unordered_map>

#include "colorHash.h"

NaiveColorQuantizer::NaiveColorQuantizer(int _quantizeStep)
    : quantizeStep(_quantizeStep) {}

void NaiveColorQuantizer::createPalette(std::vector<Color>& img,
                                        int numberOfColors) {
    // calculate color frequencies
    std::unordered_map<Color, int, ColorHash> colorFreq;

    for (int i = 0; i < img.size(); i++) {
        unsigned char r = (img[i].r / quantizeStep) * quantizeStep;
        unsigned char g = (img[i].g / quantizeStep) * quantizeStep;
        unsigned char b = (img[i].b / quantizeStep) * quantizeStep;

        colorFreq[Color(r, g, b)]++;
    }

    // copy values of the unordered map to a vector
    std::vector<std::pair<Color, int>> colorFreqOrd;

    for (const std::pair<const Color, int>& n : colorFreq) {
        colorFreqOrd.insert(std::end(colorFreqOrd), n);
    }

    // sort the vector up to the number of colors we want in our palette
    std::nth_element(colorFreqOrd.begin(),
                     colorFreqOrd.begin() + numberOfColors, colorFreqOrd.end(),
                     [](std::pair<Color, int> v1, std::pair<Color, int> v2) {
                         return v1.second > v2.second;
                     });

    // remove colors which will not be used
    colorFreqOrd.erase(colorFreqOrd.begin() + numberOfColors,
                       colorFreqOrd.end());

    // save color palette
    for (const std::pair<const Color, int>& n : colorFreqOrd) {
        palette.push_back(n.first);
    }
}

std::vector<Color> NaiveColorQuantizer::quantize(std::vector<Color>& img) {
    std::vector<Color> imgResult;

    for (int i = 0; i < img.size(); i++) {
        Color closest;
        int distMin = 1000;

        for (const Color& paletteColor : palette) {
            double dist = img[i].dist(paletteColor);

            if (dist < distMin) {
                distMin = dist;
                closest = paletteColor;
            }
        }

        imgResult.push_back(closest);
    }

    return imgResult;
}

std::vector<Color> NaiveColorQuantizer::getPalette() { return palette; }