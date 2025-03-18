#ifndef __NAIVE_COLOR_QUANTIZER_H
#define __NAIVE_COLOR_QUANTIZER_H

#include "colorQuantizer.h"

class NaiveColorQuantizer : public ColorQuantizer {
   public:
    NaiveColorQuantizer(int _quantizeStep);

    std::vector<Color> getPalette();
    void createPalette(std::vector<Color> &img, int numberOfColors);
    std::vector<Color> quantize(std::vector<Color> &img);

   private:
    int quantizeStep;
    std::vector<Color> palette;
};

#endif