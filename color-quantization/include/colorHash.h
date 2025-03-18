#ifndef __COLOR_HASH_H
#define __COLOR_HASH_H

#include "color.h"
#include "stddef.h"

class ColorHash {
   public:
    size_t operator()(const Color& c) const {
        size_t h1 = c.r;
        size_t h2 = c.g * 255;
        size_t h3 = c.b * 255 * 255;  //

        return h1 + h2 + h3;
    }
};

#endif