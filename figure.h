#ifndef D_FIGURE_H
#define D_FIGURE_H

#include <iostream>
#include <memory>
#include <array>
#include <cmath>

#include "sdl.h"
#include "imgui.h"
#include "vertex.h"

struct color {
    color() : r(255), g(255), b(255) {}
    int32_t r, g, b;
    color(int r_, int g_, int b_) :r(r_), g(g_), b(b_) {}
    void set_color(int r_, int g_, int b_) { r = r_, g = g_, b = b_; }
};

struct figure {
    virtual void render(const sdl::renderer& renderer) const = 0;
    virtual void save(std::ostream& os) const = 0;
    virtual bool erase_check(const vertex& v) const = 0;
    virtual ~figure() = default;

    color color_{};
    virtual void set_color(int r, int g, int b) {
        color_.r = r;
        color_.g = g;
        color_.b = b;
    }
};


#endif //D_FIGURE_H