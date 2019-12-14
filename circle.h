#ifndef D_CIRCLE_H
#define D_CIRCLE_H

#include "figure.h"

struct  circle : figure {
    circle(const std::array<vertex, 2>& vertices) : vertices_(vertices) {}

    void render(const sdl::renderer& renderer) const override {
        renderer.set_color(color_.r, color_.g, color_.b);
        for (int32_t i = 0; i < 360; ++i) {
            int32_t vx = vertices_[1].x - vertices_[0].x;
            int32_t vy = vertices_[1].y - vertices_[0].y;
            double rx1 = vertices_[0].x + sqrt(vx * vx + vy * vy) * cos(i * (M_PI / 180));
            double ry1 = vertices_[0].y + sqrt(vx * vx + vy * vy) * sin(i * (M_PI / 180));
            double rx2 = vertices_[0].x + sqrt(vx * vx + vy * vy) * cos((i + 1) * (M_PI / 180));
            double ry2 = vertices_[0].y + sqrt(vx * vx + vy * vy) * sin((i + 1) * (M_PI / 180));
            //renderer.draw_line(vertices_[0].x, vertices_[0].y, rx1, ry1);
            renderer.draw_line(rx1, ry1, rx2, ry2);
        }
    }

    void save(std::ostream& os) const override {
        os << "circle" << std::endl;
        for (int32_t i = 0; i < 2; ++i) {
            os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
        }

        os << this->color_.r << ' ' << this->color_.g << ' ' << this->color_.b << std::endl;
    }
private:
    std::array<vertex, 2> vertices_;
};

#endif //D_CIRCLE_H