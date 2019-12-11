#ifndef D_LOADER_H
#define D_LOADER_H

#include<vector>
#include<memory>

#include "figure.h"
#include "document.h"

struct loader {
    std::vector<std::shared_ptr<figure>> load(std::ifstream& is) {
        std::string figure_name;
        std::vector<std::shared_ptr<figure>> figures;
        while (is >> figure_name) {
            vertex v;
            if (figure_name == std::string("triangle")) {
                std::array<vertex, 3> vertices;
                for (int32_t i = 0; i < 3; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                figures.emplace_back(std::make_shared<triangle>(vertices));
            }
            if (figure_name == std::string("square")) {
                std::array<vertex, 4> vertices;
                for (int32_t i = 0; i < 4; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                figures.emplace_back(std::make_shared<square>(vertices));
            }
            else if (figure_name == std::string("rectangle")) {
                std::array<vertex, 4> vertices;
                for (int32_t i = 0; i < 4; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                figures.emplace_back(std::make_shared<rectangle>(vertices));
            }
            else if (figure_name == std::string("trapezoid")) {
                std::array<vertex, 4> vertices;
                for (int32_t i = 0; i < 4; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                figures.emplace_back(std::make_shared<trapezoid>(vertices));
            }
        }
        return figures;
    }
    ~loader() = default; // Деструктор (Не нужен, но должен быть)
};

#endif //D_LOADER_H