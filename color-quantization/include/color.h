#ifndef __COLOR_H
#define __COLOR_H

#include <vector>
#include <iostream>

#include "colorDimensions.h"

struct Color {
   public:
    Color();
    Color(unsigned char _r, unsigned char _g, unsigned char _b);

    unsigned char r;
    unsigned char g;
    unsigned char b;

    double dist(const Color &color);

    static unsigned char getRedChannel(Color const &color);
    static unsigned char getGreenChannel(Color const &color);
    static unsigned char getBlueChannel(Color const &color);
    static char compare(Color const &color, COLOR_DIM dim, unsigned char value);
    static Color getAverage(std::vector<Color> const &colors);

    friend bool operator==(const Color &c1, const Color &c2);
    friend bool operator<(const Color &c1, const Color &c2);

    friend std::ostream &operator<<(std::ostream &os, const Color &color);
};

#endif