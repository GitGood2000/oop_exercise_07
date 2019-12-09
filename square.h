#ifndef D_SQUARE_H
#define D_SQUARE_H

#include "figure.h"

struct square : figure {
    square(const std::array<vertex, 4>& vertices) : vertices_(vertices) {}

    void render(const sdl::renderer& renderer, const int32_t r, const int32_t g, const int32_t b) const override {
        renderer.set_color(r, g, b);
        for (int32_t i = 0; i < 4; ++i) {
            renderer.draw_line(vertices_[i].x, vertices_[i].y,
                vertices_[(i + 1) % 4].x, vertices_[(i + 1) % 4].y);
        }
    }

    void save(std::ostream& os) const override {
        os << "square\n";
        for (int32_t i = 0; i < 4; ++i) {
            os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
        }
    }

private:
    std::array<vertex, 4> vertices_;

};
#endif //D_SQUARE_H