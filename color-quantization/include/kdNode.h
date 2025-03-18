#ifndef __KD_NODE_H
#define __KD_NODE_H

#include <memory>
#include <unordered_set>
#include <vector>

#include "color.h"
#include "colorDimensions.h"

struct KdNode {
   public:
    KdNode* left;
    KdNode* right;
    
    KdNode() : left(nullptr), right(nullptr) {}

    ~KdNode() {
        delete left;
        delete right;
    }

    // leaf nodes hold a color
    Color color;

    // dimension which is used to split
    COLOR_DIM splitDim;
    // Color value;
    unsigned char value;
};

#endif