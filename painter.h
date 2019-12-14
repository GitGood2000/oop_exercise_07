#ifndef D_PAINTER_H
#define D_PAINTER_H

#include <array>
#include <fstream>
#include <memory>
#include <vector>
#include <cmath>

#include "sdl.h"
#include "imgui.h"
#include "figure.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"
#include "trapezoid.h"
#include "circle.h"
#include "polyline.h"
#include "polygon.h"
#include "document.h"

struct builder {
    virtual std::unique_ptr<figure> add_vertex(const vertex& v) = 0; // ƒобавление новой вершины в фигуру

    virtual ~builder() = default; // ƒеструктор (Ќе нужен, но должен быть)

};

struct poly_builder {
    virtual std::unique_ptr<figure> add_vertex(const vertex& v) = 0; // ƒобавление новой вершины в поли-фигуру
    virtual std::unique_ptr<figure> finish_it(const vertex& v) = 0; // «авершение построение поли-фигуры

    virtual ~poly_builder() = default; // ƒеструктор (Ќе нужен, но должен быть)

};

struct triangle_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) {
        vertices_[n_] = v;
        n_ += 1;
        if (n_ != 3) {
            return nullptr;
        }
        return std::make_unique<triangle>(vertices_);
    }

private:
    int32_t n_ = 0;
    std::array<vertex, 3> vertices_; // вершины фигуры

};

struct square_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) {
        if (n_ == 2) {
            int32_t vx = vertices_[1].x - vertices_[0].x;
            int32_t vy = vertices_[1].y - vertices_[0].y;
            int32_t D = (v.x - vertices_[0].x) * vy - (v.y - vertices_[0].y) * vx;
            if (D < 0) {
                vertices_[n_] = vertex{ vertices_[1].x - vy, vertices_[1].y + vx };
                n_ += 1;
                vertices_[n_] = vertex{ vertices_[0].x - vy, vertices_[0].y + vx };
                n_ += 1;
            }
            else {
                vertices_[n_] = vertex{ vertices_[1].x + vy, vertices_[1].y - vx };
                n_ += 1;
                vertices_[n_] = vertex{ vertices_[0].x + vy, vertices_[0].y - vx };
                n_ += 1;
            }
        }
        else {
            vertices_[n_] = v;
            n_ += 1;
        }
        if (n_ != 4) {
            return nullptr;
        }
        return std::make_unique<square>(vertices_);
    }

private:
    int32_t n_ = 0;
    std::array<vertex, 4> vertices_; // вершины фигуры

};

struct rectangle_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) {
        if (n_ == 2) {
            int32_t vx1 = vertices_[1].x - vertices_[0].x;
            int32_t vy1 = vertices_[1].y - vertices_[0].y;
            int32_t px = ((vx1 * vy1 * (v.y - vertices_[0].y) + vertices_[0].x * pow(vy1, 2) + v.x * pow(vx1, 2)) / (pow(vy1, 2) + pow(vx1, 2)));
            int32_t py = (vy1 * (px - vertices_[0].x)) / (vx1)+vertices_[0].y;
            int32_t vx2 = v.x - px;
            int32_t vy2 = v.y - py;

            vertices_[n_] = vertex{ vertices_[1].x + vx2, vertices_[1].y + vy2 };
            n_ += 1;
            vertices_[n_] = vertex{ vertices_[0].x + vx2, vertices_[0].y + vy2 };
            n_ += 1;
        }
        else {
            vertices_[n_] = v;
            n_ += 1;
        }
        if (n_ != 4) {
            return nullptr;
        }
        return std::make_unique<rectangle>(vertices_);
    }

private:
    int32_t n_ = 0;
    std::array<vertex, 4> vertices_; // вершины фигуры

};

struct trapezoid_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) {
        if (n_ == 2) {
            int32_t vx1 = vertices_[1].x - vertices_[0].x;
            int32_t vy1 = vertices_[1].y - vertices_[0].y;
            int32_t px = ((vx1 * vy1 * (v.y - vertices_[0].y) + vertices_[0].x * pow(vy1, 2) + v.x * pow(vx1, 2)) / (pow(vy1, 2) + pow(vx1, 2)));
            int32_t py = (vy1 * (px - vertices_[0].x)) / (vx1)+vertices_[0].y;
            int32_t vx2 = v.x - px;
            int32_t vy2 = v.y - py;
            int32_t vx3 = vertices_[1].x - px;
            int32_t vy3 = vertices_[1].y - py;
            int32_t fx = vertices_[0].x + vx2 + vx3;
            int32_t fy = vertices_[0].y + vy2 + vy3;

            vertices_[n_] = vertex{ v.x, v.y };
            n_ += 1;
            vertices_[n_] = vertex{ fx, fy };
            n_ += 1;
        }
        else {
            vertices_[n_] = v;
            n_ += 1;
        }
        if (n_ != 4) {
            return nullptr;
        }
        return std::make_unique<trapezoid>(vertices_);
    }

private:
    int32_t n_ = 0;
    std::array<vertex, 4> vertices_; // вершины фигуры

};

struct  circle_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) {
        vertices_[n_] = v;
        n_ += 1;
        if (n_ != 2) {
            return nullptr;
        }
        return std::make_unique<circle>(vertices_);
    }
private:
    int32_t n_ = 0;
    std::array<vertex, 2> vertices_; // вершины фигуры
};

struct  polyline_builder : poly_builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) {
        vertices_.push_back(v);
        n_ += 1;
        return nullptr;
    }

    std::unique_ptr<figure> finish_it(const vertex& v) {
        vertices_.push_back(v);
        if (n_ < 2) {
            return nullptr;
        }
        return std::make_unique<polyline>(vertices_);
    }

private:
    int32_t n_ = 0;
    std::vector<vertex> vertices_; // вершины фигуры
};

struct  polygon_builder : poly_builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) {
        vertices_.push_back(v);
        n_ += 1;
        return nullptr;
    }

    std::unique_ptr<figure> finish_it(const vertex& v) {
        vertices_.push_back(vertex{ vertices_[0].x, vertices_[0].y });
        if (n_ < 2) {
            return nullptr;
        }
        return std::make_unique<polygon>(vertices_);
    }

private:
    int32_t n_ = 0;
    std::vector<vertex> vertices_; // вершины фигуры
};

#endif //D_PAINTER_H