#ifndef D_DOCUMENT_H_
#define D_DOCUMENT_H_

#include<string>
#include<vector>
#include<memory>
#include<stack>

#include "figure.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"
#include "trapezoid.h"
#include "polyline.h"
#include "polygon.h"
#include "circle.h"

struct command {
	virtual void undo() = 0;
	virtual ~command() = default; //Деструктор (пока под вопросом)
};

struct document {
	document() {};
	void add_fgrs(std::unique_ptr<figure> fgr);
	void rmv_fgrs(int32_t rmv_id);
	void undo();

	std::vector<std::unique_ptr<figure>> figures;
	std::stack<std::unique_ptr<command>> commands;
};

#endif // D_DOCUMENT_H_ 