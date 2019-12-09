#ifndef D_FIGURE_H
#define D_FIGURE_H

#include <iostream>
#include <memory>
#include <array>

#include "sdl.h"
#include "imgui.h"
#include "vertex.h"

struct figure {
    virtual void render(const sdl::renderer& renderer, const int32_t r, const int32_t g, const int32_t b) const = 0;
    virtual void save(std::ostream& os) const = 0;
    virtual ~figure() = default;
};

double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow((x1 - x2),2)+ pow((y1 - y2), 2));
}


double distance(vertex a, vertex b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

#endif //D_FIGURE_H