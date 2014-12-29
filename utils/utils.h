#ifndef __UTILS_H
#define __UTILS_H

#include "Halide.h"
#include "stdio.h"

#define USE_HALIDE_JIT     1
#define USE_HALIDE_AOT     2 
#define GENERATE_AOT_OBJS  3

// I can't decide if using these macros makes the code more readable or more obscure
#define AS_UINT8(expr)             (Halide::cast<uint8_t>(min(expr, 255)))
#define TO_2D_UINT8_LAMBDA(func)   (lambda(x,y,Halide::cast<uint8_t>(min(func(x,y), 255))))
#define TO_3D_UINT8_LAMBDA(func)   (lambda(x,y,c,Halide::cast<uint8_t>(min(func(x,y,c), 255))))

// TODO: this function assumes printf is used for user i/o
template <typename T>
void dump_test_img(Halide::Image<T> &img) {
    printf("Dumping image: %s\n", img.name().c_str());
    printf("\tdimensions=%d\n", img.dimensions());
    for (int i=img.min(0); i<img.min(0)+img.extent(0); i++) {
        if (img.dimensions()>1) {
            printf("\t%d: ", i);
            for (int j=img.min(1); j<img.min(1)+img.extent(1); j++) {
                printf("%d ", img(i,j));
            }
            printf("\n");
        }
        else
            printf("%d\n", img(i));
    }
}

// TODO: this assumes a 2-dimensional image
template <typename T>
void randomize(Halide::Image<T> &img) {
    srand((unsigned int)time(NULL));
    for (int i=img.min(0); i<img.min(0)+img.extent(0); i++)
        for (int j=img.min(1); j<img.min(1)+img.extent(1); j++)
            img(i, j) = rand() % 100;
}

#include <limits>       // std::numeric_limits
template <typename T>
T verify_max(Halide::Image<T> &img) {
    T max_val = std::numeric_limits<T>::min();
    for (int i=img.min(0); i<img.min(0)+img.extent(0); i++)
        for (int j=img.min(1); j<img.min(1)+img.extent(1); j++)
            max_val = std::max(max_val, img(i,j));
    return max_val;
}

// Returns true if images are binary equals
template <typename T>
bool compare_images(Halide::Image<T> im1, Halide::Image<T> im2) {

    return true;
}

#endif // __UTILS_H