#ifndef D_TRIANGLE_H
#define D_TRIANGLE_H

#include "figure.h"

struct triangle : figure {
    triangle(const std::array<vertex, 3>& vertices) : vertices_(vertices) {}

    void render(const sdl::renderer& renderer, const int32_t r, const int32_t g, const int32_t b) const override {
        renderer.set_color(r, g, b);
        for (int32_t i = 0; i < 3; ++i) {
            renderer.draw_line(vertices_[i].x, vertices_[i].y,
                vertices_[(i + 1) % 3].x, vertices_[(i + 1) % 3].y);
        }
    }

    void save(std::ostream& os) const override {
        os << "triangle\n";
        for (int32_t i = 0; i < 3; ++i) {
            os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
        }
    }

private:
    std::array<vertex, 3> vertices_;

};
#endif //D_TRIANGLE_H