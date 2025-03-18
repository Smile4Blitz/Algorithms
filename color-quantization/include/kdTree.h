#ifndef __KD_TREE_H
#define __KD_TREE_H

#include <unordered_set>

#include "kdNode.h"

class KdTree {
   public:
    KdNode* root;
    KdTree(int _maxDepth) : maxDepth(_maxDepth), root(nullptr) {}

    void build(std::vector<Color> &colors);
    Color query(Color &color);
    
    ~KdTree() {
        delete root;
    }

   private:
    int maxDepth;
};

#endif