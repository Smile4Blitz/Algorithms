#include "color.h"

#include <math.h>

Color::Color() {
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(unsigned char _r, unsigned char _g, unsigned char _b)
    : r(_r), g(_g), b(_b) {}

double Color::dist(const Color& color) {
    double el1 = pow(((double)color.r - (double)r), 2.0);
    double el2 = pow(((double)color.g - (double)g), 2.0);
    double el3 = pow(((double)color.b - (double)b), 2.0);

    return pow(el1 + el2 + el3, 0.5);
}

unsigned char Color::getRedChannel(Color const& color) { return color.r; }

unsigned char Color::getGreenChannel(Color const& color) { return color.g; }

unsigned char Color::getBlueChannel(Color const& color) { return color.b; }

char Color::compare(Color const& color, COLOR_DIM dim, unsigned char value) {
    unsigned char colorChannel;
    switch (dim) {
        case RED:
            colorChannel = color.r;
            break;
        case GREEN:
            colorChannel = color.g;
            break;
        case BLUE:
            colorChannel = color.b;
            break;
    }

    if (colorChannel > value) {
        return 1;
    } else if (colorChannel < value) {
        return -1;
    } else {
        return 0;
    }
}

Color Color::getAverage(std::vector<Color> const& colors) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (const Color& color : colors) {
        r += ((double)color.r / colors.size());
        g += ((double)color.g / colors.size());
        b += ((double)color.b / colors.size());
    }

    r = (unsigned char)r;
    g = (unsigned char)g;
    b = (unsigned char)b;

    return Color(r, g, b);
}

bool operator==(const Color& c1, const Color& c2) {
    return (c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b);
};

bool operator<(const Color& c1, const Color& c2) {
    double dist1 = pow(pow((double)c1.r, 2.0) + pow((double)c1.g, 2.0) +
                           pow((double)c1.b, 2.0),
                       0.5);
    double dist2 = pow(pow((double)c2.r, 2.0) + pow((double)c2.g, 2.0) +
                           pow((double)c2.b, 2.0),
                       0.5);

    return dist1 < dist2;
}

Color operator+(const Color& c1, const Color& c2) {
    return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

std::ostream& operator<<(std::ostream& os, const Color& color) {
    os << "Color(" << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << ")";
    return os;
}