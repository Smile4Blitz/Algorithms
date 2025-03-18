#ifndef __KD_COLOR_QUANTIZER_H
#define __KD_COLOR_QUANTIZER_H

#include <memory>

#include "colorQuantizer.h"
#include "kdTree.h"

class KdColorQuantizer : public ColorQuantizer {
   public:
    void createPalette(std::vector<Color> &img, int numberOfColors);
    std::vector<Color> quantize(std::vector<Color> &img);

    KdTree* tree;
    KdColorQuantizer() : tree(nullptr) {}

    ~KdColorQuantizer() {
        delete tree;
    }	
};

#endif