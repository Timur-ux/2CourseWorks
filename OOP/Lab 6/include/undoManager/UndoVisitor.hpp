#ifndef UNDO_VISITOR_H_
#define UNDO_VISITOR_H_

#include <type_traits>
#include <concepts>
#include <memory>

#include "Location.hpp"

class StateAdd;
class StateMove;
class StateRemove;
class StateBase;

class UndoVisitor {
private:
	std::shared_ptr<ILocation> location;
public:
	UndoVisitor(std::shared_ptr<ILocation> _location) : location(_location) {}
	void visit(StateAdd & state);
	void visit(StateMove & state);
	void visit(StateRemove & state);
	void visit(StateBase & state);
};


#endif