#ifndef UNDO_VISITOR_H_
#define UNDO_VISITOR_H_

#include <type_traits>
#include <concepts>
#include <memory>

#include "Location.hpp"

class StateAdd;
class StateRemove;
class StateBase;

class UndoVisitor {
private:
    std::weak_ptr<ILocation> location;
public:
    UndoVisitor(std::weak_ptr<ILocation> _location) : location(_location) {}
    void visit(StateAdd & state);
    void visit(StateRemove & state);
    void visit(StateBase & state);
};


#endif