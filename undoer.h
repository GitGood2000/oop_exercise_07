#ifndef D_UNDOER_H
#define D_UNDOER_H

#include<string>
#include<vector>
#include<memory>
#include<stack>

#include "figure.h"
#include "square.h"
#include "rectangle.h"
#include "trapezoid.h"

enum Indexes {
    ul_clear,
    ul_add,
    ul_rmv,
    ul_load
};

static std::vector<std::unique_ptr<figure>> figures;

struct undo_list {
    struct ul_element {
        int32_t idx;
        std::unique_ptr<figure> fig;
        ul_element(int32_t _idx, std::unique_ptr<figure> _fig) : idx(_idx), fig(std::move(_fig)) {}
    };
    std::stack<ul_element> ul_stack;
    std::vector<std::unique_ptr<figure>> ul_figures;
    void push(int exp, std::unique_ptr<figure> value) {
        this->ul_stack.push(ul_element(exp, std::move(value)));
    }
    void undo() {
        //ul_stack.top();
        if (ul_stack.size() > 0) {
            if (ul_stack.top().idx == ul_add) {
                figures.pop_back();
            }
            else if (ul_stack.top().idx == ul_rmv) {
                figures.emplace_back(std::move(ul_stack.top().fig));
            }
            else if (ul_stack.top().idx == ul_clear) {
                figures = std::move(ul_figures);
            }
            else if (ul_stack.top().idx == ul_load) {
                figures.clear();
            }
            ul_stack.pop();
        }
    }
};
static undo_list ul;

#endif //D_UNDOER_H