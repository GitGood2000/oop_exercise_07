#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "sdl.h"
#include "imgui.h"
#include "figure.h"
#include "triangle.h"
#include "painter.h"
#include "loader.h"
#include "document.h"

int main() {
    document document;
    color fgr_clr{};
    //std::unique_ptr<document> document;
    sdl::renderer renderer("Editor");
    bool quit = false;
    std::unique_ptr<builder> active_builder = nullptr;
    std::unique_ptr<poly_builder> active_poly_builder = nullptr;
    const int32_t file_name_length = 128;
    char file_name[file_name_length] = "";
    int32_t remove_id = 0;
    while (!quit) {
        renderer.set_color(0, 0, 0);
        renderer.clear();

        sdl::event event;

        while (sdl::event::poll(event)) {
            sdl::quit_event quit_event;
            sdl::mouse_button_event mouse_button_event;
            if (event.extract(quit_event)) {
                quit = true;
                break;
            }
            else if (event.extract(mouse_button_event)) {
                if (active_builder && mouse_button_event.button() == sdl::mouse_button_event::left &&
                    mouse_button_event.type() == sdl::mouse_button_event::down) { //Если есть строитель и ЛКМ
                    std::unique_ptr<figure> figure = //если в строителе достаточное количество вершин, будет фигура, иначе nullptr
                        active_builder->add_vertex(vertex{ mouse_button_event.x(), mouse_button_event.y() }); // добавляем вершины
                    if (figure) {
                        //figures.emplace_back(std::move(figure)); //добавить полученный результат в вектор фигур
                        (*figure).set_color(fgr_clr.r, fgr_clr.g, fgr_clr.b);
                        document.add_fgrs(std::move(figure));
                        active_builder = nullptr;
                    }
                }
                else if (active_poly_builder) {
                    std::unique_ptr<figure> p_figure;
                    if (mouse_button_event.button() == sdl::mouse_button_event::left &&
                        mouse_button_event.type() == sdl::mouse_button_event::down) { //Если есть строитель и ЛКМ
                        p_figure = active_poly_builder->add_vertex(vertex{ mouse_button_event.x(), mouse_button_event.y() });  // В этом случае nullptr
                    }
                    else if (mouse_button_event.button() == sdl::mouse_button_event::right &&
                        mouse_button_event.type() == sdl::mouse_button_event::down) { //Если есть строитель и ПКМ
                        p_figure = active_poly_builder->finish_it(vertex{ mouse_button_event.x(), mouse_button_event.y() }); // завершение поли-фигуры
                        if (p_figure) {
                            (*p_figure).set_color(fgr_clr.r, fgr_clr.g, fgr_clr.b);
                            document.add_fgrs(std::move(p_figure));
                            active_poly_builder = nullptr;
                        }
                    }
                }
            }
        }

        //for (const std::unique_ptr<figure>& figure : document->figures) {
            //figure->render(renderer);
        //}

        for (int i = 0; i < document.figures.size(); ++i) {
            if (document.figures[i]) {
                document.figures[i]->render(renderer);
            }
        }

        ImGui::Begin("Menu");
        if (ImGui::Button("New canvas")) {
            document.figures.clear();
        }
        ImGui::InputText("File name", file_name, file_name_length - 1);
        if (ImGui::Button("Save")) {
            std::ofstream os(file_name);
            if (os) {
                for (const std::unique_ptr<figure>& figure : document.figures) {
                    figure->save(os);
                }
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Load")) {
            std::ifstream is(file_name);
            if (is) {
                loader loader;
                document.figures = loader.load(is);
            }
        }
        ImGui::InputInt("R", &fgr_clr.r);
        ImGui::InputInt("G", &fgr_clr.g);
        ImGui::InputInt("B", &fgr_clr.b);
        if (ImGui::Button("Red")) {
            fgr_clr.set_color(255, 0, 0);
        }
        ImGui::SameLine();
        if (ImGui::Button("Green")) {
            fgr_clr.set_color(0, 255, 0);
        }
        ImGui::SameLine();
        if (ImGui::Button("Blue")) {
            fgr_clr.set_color(0, 0, 255);
        }
        if (ImGui::Button("Yellow")) {
            fgr_clr.set_color(255, 255, 0);
        }
        ImGui::SameLine();
        if (ImGui::Button("Cyan")) {
            fgr_clr.set_color(0, 255, 255);
        }
        ImGui::SameLine();
        if (ImGui::Button("Magenta")) {
            fgr_clr.set_color(255, 0, 255);
        }
        if (ImGui::Button("White")) {
            fgr_clr.set_color(255, 255, 255);
        }
        if (ImGui::Button("Triangle")) {
            active_builder = std::make_unique<triangle_builder>();
        }
        if (ImGui::Button("Square")) {
            active_builder = std::make_unique<square_builder>();
        }
        if (ImGui::Button("Rectangle")) {
            active_builder = std::make_unique<rectangle_builder>();
        }
        if (ImGui::Button("Trapezoid")) {
            active_builder = std::make_unique<trapezoid_builder>();
        }
        if (ImGui::Button("Circle")) {
            active_builder = std::make_unique<circle_builder>();
        }
        if (ImGui::Button("Poly-Line")) {
            active_poly_builder = std::make_unique<polyline_builder>();
        }
        if (ImGui::Button("Polygon")) {
            active_poly_builder = std::make_unique<polygon_builder>();
        }
        ImGui::InputInt("Remove id", &remove_id);
        if (ImGui::Button("Remove")) {
            if (remove_id < document.figures.size()) {
                if (document.figures[remove_id]) {
                    document.rmv_fgrs(remove_id);
                }
                //rmv_fgrs(figures.erase(figures.begin() + remove_id);
            }
        }
        if (ImGui::Button("Undo")) {
            document.undo();
        }

        ImGui::End();

        renderer.present();
    }
}
