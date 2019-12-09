#ifndef D_FIGURE_H
#define D_FIGURE_H

#include <iostream>
#include <memory>

#include "sdl.h"
#include "imgui.h"
#include "vertex.h"

struct figure {
    virtual void render(const sdl::renderer& renderer, const int32_t r, const int32_t g, const int32_t b) const = 0;
    virtual void save(std::ostream& os) const = 0;
    virtual ~figure() = default;
};

#endif //D_FIGURE_H