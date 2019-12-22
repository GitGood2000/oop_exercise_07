#ifndef D_CIRCLE_H
#define D_CIRCLE_H

#include "figure.h"

struct  circle : figure {
    circle(const vertex& center, const double& radius) : center_(center), radius_(radius) {}

    void render(const sdl::renderer& renderer) const override {
        renderer.set_color(color_.r, color_.g, color_.b);
        for (int32_t i = 0; i < 360; ++i) {
            double rx1 = center_.x + radius_ * cos(i * (M_PI / 180));
            double ry1 = center_.y + radius_ * sin(i * (M_PI / 180));
            double rx2 = center_.x + radius_ * cos((i + 1) * (M_PI / 180));
            double ry2 = center_.y + radius_ * sin((i + 1) * (M_PI / 180));
            //renderer.draw_line(vertices_[0].x, vertices_[0].y, rx1, ry1);
            renderer.draw_line(rx1, ry1, rx2, ry2);
        }
    }

    void save(std::ostream& os) const override {
        os << "circle" << std::endl;
        os << center_.x << ' ' << center_.y << ' ' << radius_ << '\n';

        os << this->color_.r << ' ' << this->color_.g << ' ' << this->color_.b << std::endl;
    }

    bool erase_check(const vertex& v) const override {
        int32_t lx = v.x - center_.x;
        int32_t ly = v.y - center_.y;
        double l = sqrt(lx * lx + ly * ly);
        if (l <= radius_) {
            return true;
        }
        else {
            return false;
        }
    }

private:
    vertex center_;
    double radius_;
};

#endif //D_CIRCLE_H