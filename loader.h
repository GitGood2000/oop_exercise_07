#ifndef D_LOADER_H
#define D_LOADER_H

#include<vector>
#include<memory>

#include "figure.h"
#include "document.h"

struct loader {
    std::vector<std::unique_ptr<figure>> load(std::ifstream& is) {
        std::string figure_name;
        std::vector<std::unique_ptr<figure>> figures;
        while (is >> figure_name) {
            vertex v;
            if (figure_name == std::string("triangle")) {
                std::array<vertex, 3> vertices;
                for (int32_t i = 0; i < 3; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                struct color load_clr {};
                is >> load_clr.r >> load_clr.g >> load_clr.b;
                figures.emplace_back(std::make_unique<triangle>(vertices));
                (*figures[figures.size() - 1]).set_color(load_clr.r, load_clr.g, load_clr.b);

            }
            if (figure_name == std::string("square")) {
                std::array<vertex, 4> vertices;
                for (int32_t i = 0; i < 4; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                struct color load_clr {};
                is >> load_clr.r >> load_clr.g >> load_clr.b;
                figures.emplace_back(std::make_unique<square>(vertices));
                (*figures[figures.size() - 1]).set_color(load_clr.r, load_clr.g, load_clr.b);
            }
            else if (figure_name == std::string("rectangle")) {
                std::array<vertex, 4> vertices;
                for (int32_t i = 0; i < 4; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                struct color load_clr {};
                is >> load_clr.r >> load_clr.g >> load_clr.b;
                figures.emplace_back(std::make_unique<rectangle>(vertices));
                (*figures[figures.size() - 1]).set_color(load_clr.r, load_clr.g, load_clr.b);
            }
            else if (figure_name == std::string("trapezoid")) {
                std::array<vertex, 4> vertices;
                for (int32_t i = 0; i < 4; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                struct color load_clr {};
                is >> load_clr.r >> load_clr.g >> load_clr.b;
                figures.emplace_back(std::make_unique<trapezoid>(vertices));
                (*figures[figures.size() - 1]).set_color(load_clr.r, load_clr.g, load_clr.b);
            }
            else if (figure_name == std::string("circle")) {
                vertex center;
                double radius;
                is >> v.x >> v.y >> radius;
                    center = v;
                struct color load_clr {};
                is >> load_clr.r >> load_clr.g >> load_clr.b;
                figures.emplace_back(std::make_unique<circle>(center, radius));
                (*figures[figures.size() - 1]).set_color(load_clr.r, load_clr.g, load_clr.b);
            }
            else if (figure_name == std::string("polyline")) {
                std::vector<vertex> vertices;
                int count_v;
                is >> count_v;
                for (int i = 0; i < count_v; ++i) {
                    is >> v.x >> v.y;
                    vertices.push_back(v);
                }
                struct color load_clr {};
                is >> load_clr.r >> load_clr.g >> load_clr.b;
                figures.emplace_back(std::make_unique<polyline>(vertices));
                (*figures[figures.size() - 1]).set_color(load_clr.r, load_clr.g, load_clr.b);
            }
            else if (figure_name == std::string("polygon")) {
                std::vector<vertex> vertices;
                int count_v;
                is >> count_v;
                for (int i = 0; i < count_v; ++i) {
                    is >> v.x >> v.y;
                    vertices.push_back(v);
                }
                struct color load_clr {};
                is >> load_clr.r >> load_clr.g >> load_clr.b;
                figures.emplace_back(std::make_unique<polygon>(vertices));
                (*figures[figures.size() - 1]).set_color(load_clr.r, load_clr.g, load_clr.b);
            }
        }
        return figures;
    }
    ~loader() = default; // Деструктор (Не нужен, но должен быть)
};

#endif //D_LOADER_H