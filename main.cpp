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
    sdl::renderer renderer("Editor");
    bool quit = false;
    std::unique_ptr<builder> active_builder = nullptr;
    std::unique_ptr<document> document = nullptr;
    const int32_t file_name_length = 128;
    char file_name[file_name_length] = "";
    int32_t remove_id = 0;
    int32_t red_c = 255;
    int32_t grn_c = 255;
    int32_t blu_c = 255;
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
                        document->add_fgrs(figure);
                        active_builder = nullptr;
                    }
                }
            }
        }

        for (const std::unique_ptr<figure> &figure : document->call_fgrs()) {
            figure->render(renderer, red_c, grn_c, blu_c);
        }

        ImGui::Begin("Menu");
        if (ImGui::Button("New canvas")) {
            (document)->call_fgrs().clear();
        }
        ImGui::InputText("File name", file_name, file_name_length - 1);
        if (ImGui::Button("Save")) {
            std::ofstream os(file_name);
            if (os) {
                for (const std::unique_ptr<figure> &figure : document->call_fgrs()) {
                    figure->save(os);
                }
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Load")) {
            std::ifstream is(file_name);
            if (is) {
                loader loader;
                document->call_fgrs() = loader.load(is);
            }
        }
        ImGui::InputInt("R", &red_c);
        ImGui::InputInt("G", &grn_c);
        ImGui::InputInt("B", &blu_c);
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
        ImGui::InputInt("Remove id", &remove_id);
        if (ImGui::Button("Remove")) {
            //rmv_fgrs(figures.erase(figures.begin() + remove_id);
            document->rmv_fgrs(remove_id);
        }
        
        if (ImGui::Button("Undo")) {
            document->undo();
        }

        ImGui::End();

        renderer.present();
    }
}
