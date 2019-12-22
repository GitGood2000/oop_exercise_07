#ifndef D_POLYGON_H
#define D_POLYGON_H

#include "figure.h"

struct  polygon : figure {
    polygon(const std::vector<vertex>& vertices) : vertices_(vertices) {}

    void render(const sdl::renderer& renderer) const override {
        renderer.set_color(color_.r, color_.g, color_.b);
        for (int32_t i = 0; i < vertices_.size() - 1; ++i) {
            renderer.draw_line(vertices_[i].x, vertices_[i].y,
                vertices_[(i + 1)].x, vertices_[(i + 1)].y);
        }
    }

    void save(std::ostream& os) const override {
        os << "polygon" << ' ' << vertices_.size() << std::endl;
        for (int32_t i = 0; i < vertices_.size(); ++i) {
            os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
        }
        os << this->color_.r << ' ' << this->color_.g << ' ' << this->color_.b << std::endl;
    }

    bool  erase_check(const vertex& v) const override {
        int32_t j;
        bool count = false;
        for (int32_t i = 0; i < vertices_.size(); ++i) {
            for (i = 0, j = vertices_.size() - 1; i < vertices_.size(); j = i++) {
                if (((vertices_[i].y > v.y) != (vertices_[j].y > v.y)) && (v.x < (vertices_[j].x - vertices_[i].x) * (v.y - vertices_[i].y) / (vertices_[j].y - vertices_[i].y) + vertices_[i].x)) {
                    count = !count;
                }
            }
        }
        return count;
    }

private:
    std::vector<vertex> vertices_;

};
#endif //D_POLYGON_H