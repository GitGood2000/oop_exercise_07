#ifndef D_DOCUMENT_H_
#define D_DOCUMENT_H_

#include<string>
#include<vector>
#include<memory>
#include<stack>

#include "figure.h"
#include "square.h"
#include "rectangle.h"
#include "trapezoid.h"

struct add_cmd;
struct rmv_cmd;


struct command {
	virtual ~command() = default; //Деструктор (пока под вопросом)

	virtual void undo() = 0;
};

struct document {
	document() {};
	void add_fgrs(std::unique_ptr<figure>& fgr);
	void rmv_fgrs(int32_t rmv_id);
	std::vector<std::unique_ptr<figure>> call_fgrs();
	//void undo();
	
private:
	friend struct add_cmd;
	friend struct rmv_cmd;

	std::vector<std::unique_ptr<figure>> figures;
	std::stack<std::unique_ptr<command>> commands;
};

#endif // D_DOCUMENT_H_ 