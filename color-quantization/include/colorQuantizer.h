#ifndef __COLOR_QUANTIZER_H
#define __COLOR_QUANTIZER_H

#include <vector>

#include "color.h"

class ColorQuantizer {
   public:
    virtual void createPalette(std::vector<Color> &img, int numberOfColors) = 0;
    virtual std::vector<Color> quantize(std::vector<Color> &img) = 0;
};

#endif