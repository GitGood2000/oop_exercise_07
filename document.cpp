#include "document.h"

struct add_cmd : command {
	add_cmd(document* document) : document_(document) {}

	void undo() override {
		document_->figures.pop_back();
	}

private:
	document* document_;
	//int32_t idx_;
	//std::unique_ptr<figure> figure_;
};

struct rmv_cmd : command {
	rmv_cmd(document* document, int32_t idx, std::unique_ptr<figure>&& figure) : document_(document), idx_(idx), figure_(std::move(figure)) {}

	void undo() override {
		document_->figures.emplace(document_->figures.begin() + idx_, std::move(figure_));
		document_->figures.pop_back();
	}

private:
	document* document_;
	std::unique_ptr<figure> figure_;
	int32_t idx_;
};

void document::add_fgrs(std::unique_ptr<figure> fgr) {
	figures.emplace_back(std::move(fgr)); //добавить полученный результат в вектор фигур
	commands.push(std::make_unique<add_cmd>(this));
}

void document::rmv_fgrs(int32_t rmv_id) {
	commands.push(std::make_unique<rmv_cmd>(this, rmv_id, std::move(figures[rmv_id])));
	figures.erase(figures.begin() + rmv_id);
}

void document::undo() {
	if (commands.size()) {
		commands.top()->undo();
		commands.pop();
	}
}