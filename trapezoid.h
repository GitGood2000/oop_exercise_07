#ifndef D_TRAPEZOID_H
#define D_TRAPEZOID_H

#include "figure.h"

struct trapezoid : figure {
    trapezoid(const std::array<vertex, 4>& vertices) : vertices_(vertices) {}

    void render(const sdl::renderer& renderer) const override {
        renderer.set_color(color_.r, color_.g, color_.b);
        for (int32_t i = 0; i < 4; ++i) {
            renderer.draw_line(vertices_[i].x, vertices_[i].y,
                vertices_[(i + 1) % 4].x, vertices_[(i + 1) % 4].y);
        }
    }

    void save(std::ostream& os) const override {
        os << "trapezoid\n";
        for (int32_t i = 0; i < 4; ++i) {
            os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
        }
        os << this->color_.r << ' ' << this->color_.g << ' ' << this->color_.b << std::endl;
    }

    bool  erase_check(const vertex& v) const override {
        int32_t j;
        bool count = false;
        for (int32_t i = 0; i < 4; ++i) {
            for (i = 0, j = vertices_.size() - 1; i < vertices_.size(); j = i++) {
                if (((vertices_[i].y > v.y) != (vertices_[j].y > v.y)) && (v.x < (vertices_[j].x - vertices_[i].x) * (v.y - vertices_[i].y) / (vertices_[j].y - vertices_[i].y) + vertices_[i].x)) {
                    count = !count;
                }
            }
        }
        return count;
    }

private:
    std::array<vertex, 4> vertices_;

};
#endif //D_TRAPEZOID_H